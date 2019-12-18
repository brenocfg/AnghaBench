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
struct hostapd_iface {int ready_to_start_in_sync; scalar_t__ state; scalar_t__ need_to_start_in_sync; struct hostapd_data** bss; struct hapd_interfaces* interfaces; } ;
struct hostapd_data {TYPE_1__* conf; int /*<<< orphan*/  msg_ctx; } ;
struct hapd_interfaces {unsigned int count; struct hostapd_iface** iface; scalar_t__ terminate_on_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_EVENT_DISABLED ; 
 scalar_t__ HAPD_IFACE_DFS ; 
 int /*<<< orphan*/  HAPD_IFACE_DISABLED ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  eloop_terminate () ; 
 int /*<<< orphan*/  hostapd_set_state (struct hostapd_iface*,int /*<<< orphan*/ ) ; 
 int hostapd_setup_interface_complete_sync (struct hostapd_iface*,int) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int hostapd_setup_interface_complete(struct hostapd_iface *iface, int err)
{
	struct hapd_interfaces *interfaces = iface->interfaces;
	struct hostapd_data *hapd = iface->bss[0];
	unsigned int i;
	int not_ready_in_sync_ifaces = 0;

	if (!iface->need_to_start_in_sync)
		return hostapd_setup_interface_complete_sync(iface, err);

	if (err) {
		wpa_printf(MSG_ERROR, "Interface initialization failed");
		hostapd_set_state(iface, HAPD_IFACE_DISABLED);
		iface->need_to_start_in_sync = 0;
		wpa_msg(hapd->msg_ctx, MSG_INFO, AP_EVENT_DISABLED);
		if (interfaces && interfaces->terminate_on_error)
			eloop_terminate();
		return -1;
	}

	if (iface->ready_to_start_in_sync) {
		/* Already in ready and waiting. should never happpen */
		return 0;
	}

	for (i = 0; i < interfaces->count; i++) {
		if (interfaces->iface[i]->need_to_start_in_sync &&
		    !interfaces->iface[i]->ready_to_start_in_sync)
			not_ready_in_sync_ifaces++;
	}

	/*
	 * Check if this is the last interface, if yes then start all the other
	 * waiting interfaces. If not, add this interface to the waiting list.
	 */
	if (not_ready_in_sync_ifaces > 1 && iface->state == HAPD_IFACE_DFS) {
		/*
		 * If this interface went through CAC, do not synchronize, just
		 * start immediately.
		 */
		iface->need_to_start_in_sync = 0;
		wpa_printf(MSG_INFO,
			   "%s: Finished CAC - bypass sync and start interface",
			   iface->bss[0]->conf->iface);
		return hostapd_setup_interface_complete_sync(iface, err);
	}

	if (not_ready_in_sync_ifaces > 1) {
		/* need to wait as there are other interfaces still coming up */
		iface->ready_to_start_in_sync = 1;
		wpa_printf(MSG_INFO,
			   "%s: Interface waiting to sync with other interfaces",
			   iface->bss[0]->conf->iface);
		return 0;
	}

	wpa_printf(MSG_INFO,
		   "%s: Last interface to sync - starting all interfaces",
		   iface->bss[0]->conf->iface);
	iface->need_to_start_in_sync = 0;
	hostapd_setup_interface_complete_sync(iface, err);
	for (i = 0; i < interfaces->count; i++) {
		if (interfaces->iface[i]->need_to_start_in_sync &&
		    interfaces->iface[i]->ready_to_start_in_sync) {
			hostapd_setup_interface_complete_sync(
				interfaces->iface[i], 0);
			/* Only once the interfaces are sync started */
			interfaces->iface[i]->need_to_start_in_sync = 0;
		}
	}

	return 0;
}