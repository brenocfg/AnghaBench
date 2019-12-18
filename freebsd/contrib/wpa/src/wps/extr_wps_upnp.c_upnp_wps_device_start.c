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
struct upnp_wps_device_sm {int started; int multicast_sd; int ssdp_sd; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ip_addr_text; int /*<<< orphan*/  ip_addr; scalar_t__ advertise_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ add_ssdp_network (char*) ; 
 scalar_t__ advertisement_state_machine_start (struct upnp_wps_device_sm*) ; 
 scalar_t__ get_netif_info (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ssdp_listener_start (struct upnp_wps_device_sm*) ; 
 scalar_t__ ssdp_open_multicast (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  upnp_wps_device_stop (struct upnp_wps_device_sm*) ; 
 scalar_t__ web_listener_start (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int upnp_wps_device_start(struct upnp_wps_device_sm *sm, char *net_if)
{
	if (!sm || !net_if)
		return -1;

	if (sm->started)
		upnp_wps_device_stop(sm);

	sm->multicast_sd = -1;
	sm->ssdp_sd = -1;
	sm->started = 1;
	sm->advertise_count = 0;

	/* Fix up linux multicast handling */
	if (add_ssdp_network(net_if))
		goto fail;

	/* Determine which IP and mac address we're using */
	if (get_netif_info(net_if, &sm->ip_addr, &sm->ip_addr_text,
			   sm->mac_addr)) {
		wpa_printf(MSG_INFO, "WPS UPnP: Could not get IP/MAC address "
			   "for %s. Does it have IP address?", net_if);
		goto fail;
	}

	/* Listen for incoming TCP connections so that others
	 * can fetch our "xml files" from us.
	 */
	if (web_listener_start(sm))
		goto fail;

	/* Set up for receiving discovery (UDP) packets */
	if (ssdp_listener_start(sm))
		goto fail;

	/* Set up for sending multicast */
	if (ssdp_open_multicast(sm) < 0)
		goto fail;

	/*
	 * Broadcast NOTIFY messages to let the world know we exist.
	 * This is done via a state machine since the messages should not be
	 * all sent out at once.
	 */
	if (advertisement_state_machine_start(sm))
		goto fail;

	return 0;

fail:
	upnp_wps_device_stop(sm);
	return -1;
}