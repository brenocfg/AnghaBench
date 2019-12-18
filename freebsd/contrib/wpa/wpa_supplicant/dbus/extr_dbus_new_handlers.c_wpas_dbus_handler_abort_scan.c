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
 int /*<<< orphan*/  WPAS_DBUS_ERROR_IFACE_SCAN_ERROR ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpas_abort_ongoing_scan (struct wpa_supplicant*) ; 

DBusMessage * wpas_dbus_handler_abort_scan(DBusMessage *message,
					   struct wpa_supplicant *wpa_s)
{
	if (wpas_abort_ongoing_scan(wpa_s) < 0)
		return dbus_message_new_error(
			message, WPAS_DBUS_ERROR_IFACE_SCAN_ERROR,
			"Abort failed or no scan in progress");

	return NULL;
}