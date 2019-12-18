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
struct wpa_supplicant {int /*<<< orphan*/  conf; scalar_t__ sched_scanning; } ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  remove_network ; 
 int /*<<< orphan*/  wpa_config_foreach_network (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_cancel_sched_scan (struct wpa_supplicant*) ; 

DBusMessage * wpas_dbus_handler_remove_all_networks(
	DBusMessage *message, struct wpa_supplicant *wpa_s)
{
	if (wpa_s->sched_scanning)
		wpa_supplicant_cancel_sched_scan(wpa_s);

	/* NB: could check for failure and return an error */
	wpa_config_foreach_network(wpa_s->conf, remove_network, wpa_s);
	return NULL;
}