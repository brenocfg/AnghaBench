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
typedef  int /*<<< orphan*/  dbus_uint32_t ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  dbus_message_get_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_bss_flush (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_bss_flush_by_age (struct wpa_supplicant*,int /*<<< orphan*/ ) ; 

DBusMessage * wpas_dbus_handler_flush_bss(DBusMessage *message,
					  struct wpa_supplicant *wpa_s)
{
	dbus_uint32_t age;

	dbus_message_get_args(message, NULL, DBUS_TYPE_UINT32, &age,
			      DBUS_TYPE_INVALID);

	if (age == 0)
		wpa_bss_flush(wpa_s);
	else
		wpa_bss_flush_by_age(wpa_s, age);

	return NULL;
}