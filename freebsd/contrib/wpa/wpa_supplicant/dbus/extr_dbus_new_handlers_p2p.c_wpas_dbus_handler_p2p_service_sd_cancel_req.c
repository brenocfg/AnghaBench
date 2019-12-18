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
typedef  scalar_t__ u64 ;
struct wpa_supplicant {int dummy; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpas_dbus_error_invalid_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wpas_p2p_sd_cancel_request (struct wpa_supplicant*,scalar_t__) ; 

DBusMessage * wpas_dbus_handler_p2p_service_sd_cancel_req(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter;
	u64 req = 0;

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &req);

	if (req == 0)
		goto error;

	if (wpas_p2p_sd_cancel_request(wpa_s, req) < 0)
		goto error;

	return NULL;
error:
	return wpas_dbus_error_invalid_args(message, NULL);
}