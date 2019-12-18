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
struct wpas_dbus_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_dbus_ctrl_iface_deinit (struct wpas_dbus_priv*) ; 
 int /*<<< orphan*/  wpas_dbus_deinit_common (struct wpas_dbus_priv*) ; 

void wpas_dbus_deinit(struct wpas_dbus_priv *priv)
{
	if (priv == NULL)
		return;

#ifdef CONFIG_CTRL_IFACE_DBUS_NEW
	wpas_dbus_ctrl_iface_deinit(priv);
#endif /* CONFIG_CTRL_IFACE_DBUS_NEW */

	wpas_dbus_deinit_common(priv);
}