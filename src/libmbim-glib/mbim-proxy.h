/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libmbim-glib -- GLib/GIO based library to control MBIM devices
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 * Copyright (C) 2014 Aleksander Morgado <aleksander@lanedo.com>
 * Copyright (C) 2014 Smith Micro Software, Inc.
 */

#ifndef MBIM_PROXY_H
#define MBIM_PROXY_H

#if !defined (__LIBMBIM_GLIB_H_INSIDE__) && !defined (LIBMBIM_GLIB_COMPILATION)
#error "Only <libmbim-glib.h> can be included directly."
#endif

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

/**
 * SECTION:mbim-proxy
 * @title: MbimProxy
 * @short_description: MBIM proxy handling routines
 *
 * The #MbimProxy will setup an abstract socket listening on a predefined
 * address, and will take care of synchronizing the access to a set of shared
 * MBIM ports.
 *
 * Multiple #MbimDevice objects may be connected to the #MbimProxy at any given
 * time. The #MbimProxy acts as a stateful proxy (all remote #MbimDevice objects
 * will need to share the same message sequence).
 */

#define MBIM_TYPE_PROXY            (mbim_proxy_get_type ())
#define MBIM_PROXY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MBIM_TYPE_PROXY, MbimProxy))
#define MBIM_PROXY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), MBIM_TYPE_PROXY, MbimProxyClass))
#define MBIM_IS_PROXY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MBIM_TYPE_PROXY))
#define MBIM_IS_PROXY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), MBIM_TYPE_PROXY))
#define MBIM_PROXY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MBIM_TYPE_PROXY, MbimProxyClass))

typedef struct _MbimProxy MbimProxy;
typedef struct _MbimProxyClass MbimProxyClass;
typedef struct _MbimProxyPrivate MbimProxyPrivate;

#define MBIM_PROXY_SOCKET_PATH "mbim-proxy"

#define MBIM_PROXY_N_CLIENTS   "mbim-proxy-n-clients"
#define MBIM_PROXY_N_DEVICES   "mbim-proxy-n-devices"

struct _MbimProxy {
    GObject parent;
    MbimProxyPrivate *priv;
};

struct _MbimProxyClass {
    GObjectClass parent;
};

GType mbim_proxy_get_type (void);
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MbimProxy, g_object_unref)

/**
 * mbim_proxy_new:
 * @error: Return location for error or %NULL.
 *
 * Creates a #MbimProxy object.
 *
 * Returns: (transfer full): a newly created #MbimProxy, or #NULL if @error is set.
 */
MbimProxy *mbim_proxy_new (GError **error);

/**
 * mbim_proxy_get_n_clients:
 * @self: a #MbimProxy.
 *
 * Get the number of clients currently connected to the proxy.
 *
 * Returns: a #guint.
 */
guint mbim_proxy_get_n_clients (MbimProxy *self);

/**
 * mbim_proxy_get_n_devices:
 * @self: a #MbimProxy.
 *
 * Get the number of devices currently connected to the proxy.
 *
 * Returns: a #guint.
 */
guint mbim_proxy_get_n_devices (MbimProxy *self);

G_END_DECLS

#endif /* MBIM_PROXY_H */
