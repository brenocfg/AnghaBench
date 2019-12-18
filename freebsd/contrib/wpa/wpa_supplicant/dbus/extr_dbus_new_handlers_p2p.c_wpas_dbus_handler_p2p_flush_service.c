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
 int /*<<< orphan*/  wpas_p2p_service_flush (struct wpa_supplicant*) ; 

DBusMessage * wpas_dbus_handler_p2p_flush_service(DBusMessage *message,
						  struct wpa_supplicant *wpa_s)
{
	wpas_p2p_service_flush(wpa_s);
	return NULL;
}