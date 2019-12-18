#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wpas_dbus_priv {struct wpa_global* global; } ;
struct wpa_global {int dummy; } ;

/* Variables and functions */
 struct wpas_dbus_priv* os_zalloc (int) ; 
 scalar_t__ wpas_dbus_ctrl_iface_init (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  wpas_dbus_deinit (struct wpas_dbus_priv*) ; 
 scalar_t__ wpas_dbus_init_common (struct wpas_dbus_priv*) ; 
 scalar_t__ wpas_dbus_init_common_finish (struct wpas_dbus_priv*) ; 

struct wpas_dbus_priv * wpas_dbus_init(struct wpa_global *global)
{
	struct wpas_dbus_priv *priv;

	priv = os_zalloc(sizeof(*priv));
	if (priv == NULL)
		return NULL;
	priv->global = global;

	if (wpas_dbus_init_common(priv) < 0 ||
#ifdef CONFIG_CTRL_IFACE_DBUS_NEW
	    wpas_dbus_ctrl_iface_init(priv) < 0 ||
#endif /* CONFIG_CTRL_IFACE_DBUS_NEW */
	    wpas_dbus_init_common_finish(priv) < 0) {
		wpas_dbus_deinit(priv);
		return NULL;
	}

	return priv;
}