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
struct TYPE_2__ {scalar_t__ dbus_ctrl_interface; } ;
struct wpa_global {int /*<<< orphan*/  binder; int /*<<< orphan*/ * dbus; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpas_binder_init (struct wpa_global*) ; 
 int /*<<< orphan*/ * wpas_dbus_init (struct wpa_global*) ; 

int wpas_notify_supplicant_initialized(struct wpa_global *global)
{
#ifdef CONFIG_CTRL_IFACE_DBUS_NEW
	if (global->params.dbus_ctrl_interface) {
		global->dbus = wpas_dbus_init(global);
		if (global->dbus == NULL)
			return -1;
	}
#endif /* CONFIG_CTRL_IFACE_DBUS_NEW */

#ifdef CONFIG_BINDER
	global->binder = wpas_binder_init(global);
	if (!global->binder)
		return -1;
#endif /* CONFIG_BINDER */

	return 0;
}