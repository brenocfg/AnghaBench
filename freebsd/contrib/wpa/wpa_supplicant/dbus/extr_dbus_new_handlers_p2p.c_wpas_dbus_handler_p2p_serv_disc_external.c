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
struct wpa_supplicant {int p2p_sd_over_ctrl_iface; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DBusMessage * wpas_dbus_handler_p2p_serv_disc_external(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	DBusMessageIter iter;
	int ext = 0;

	dbus_message_iter_init(message, &iter);
	dbus_message_iter_get_basic(&iter, &ext);

	wpa_s->p2p_sd_over_ctrl_iface = ext;

	return NULL;

}