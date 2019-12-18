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
struct wpa_supplicant {TYPE_1__* conf; int /*<<< orphan*/  confname; } ;
struct TYPE_2__ {int /*<<< orphan*/  update_config; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int wpa_config_write (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 

DBusMessage * wpas_dbus_handler_save_config(DBusMessage *message,
					    struct wpa_supplicant *wpa_s)
{
	int ret;

	if (!wpa_s->conf->update_config) {
		return wpas_dbus_error_unknown_error(
			message,
			"Not allowed to update configuration (update_config=0)");
	}

	ret = wpa_config_write(wpa_s->confname, wpa_s->conf);
	if (ret)
		return wpas_dbus_error_unknown_error(
			message, "Failed to update configuration");
	return NULL;
}