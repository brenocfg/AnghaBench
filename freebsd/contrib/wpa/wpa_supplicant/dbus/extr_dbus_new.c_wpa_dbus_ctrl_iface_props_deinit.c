#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpas_dbus_priv {int globals_start; TYPE_1__* all_interface_properties; } ;
struct TYPE_2__ {scalar_t__ dbus_property; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 

__attribute__((used)) static void wpa_dbus_ctrl_iface_props_deinit(struct wpas_dbus_priv *priv)
{
	int idx = priv->globals_start;

	/* Free all allocated property values */
	while (priv->all_interface_properties[idx].dbus_property)
		os_free((char *)
			priv->all_interface_properties[idx++].dbus_property);
	os_free((char *) priv->all_interface_properties);
}