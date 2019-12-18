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
struct wpa_supplicant {TYPE_1__* global; } ;
typedef  scalar_t__ dbus_int32_t ;
struct TYPE_2__ {struct wpa_supplicant* p2p_init_wpa_s; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INT32 ; 
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_UNKNOWN_ERROR ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpas_dbus_error_no_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ wpas_p2p_listen (struct wpa_supplicant*,unsigned int) ; 

DBusMessage * wpas_dbus_handler_p2p_listen(DBusMessage *message,
					   struct wpa_supplicant *wpa_s)
{
	dbus_int32_t timeout = 0;

	if (!dbus_message_get_args(message, NULL, DBUS_TYPE_INT32, &timeout,
				   DBUS_TYPE_INVALID))
		return wpas_dbus_error_no_memory(message);

	wpa_s = wpa_s->global->p2p_init_wpa_s;

	if (wpas_p2p_listen(wpa_s, (unsigned int) timeout)) {
		return dbus_message_new_error(message,
					      WPAS_DBUS_ERROR_UNKNOWN_ERROR,
					      "Could not start P2P listen");
	}

	return NULL;
}