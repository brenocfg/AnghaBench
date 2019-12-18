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
struct wpa_supplicant {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/ * wpas_dbus_error_unknown_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ wpas_wps_cancel (struct wpa_supplicant*) ; 

DBusMessage * wpas_dbus_handler_wps_cancel(DBusMessage *message,
					   struct wpa_supplicant *wpa_s)
{
	if (wpas_wps_cancel(wpa_s))
		return wpas_dbus_error_unknown_error(message,
						     "WPS cancel failed");

	return NULL;
}