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
struct upnp_wps_device_sm {int multicast_sd; scalar_t__ started; int /*<<< orphan*/ * ip_addr_text; int /*<<< orphan*/ * wlanevent; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  msearch_replies; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  advertisement_state_machine_stop (struct upnp_wps_device_sm*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  event_send_stop_all (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssdp_listener_stop (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  upnp_wps_free_msearchreply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upnp_wps_free_subscriptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  web_listener_stop (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void upnp_wps_device_stop(struct upnp_wps_device_sm *sm)
{
	if (!sm || !sm->started)
		return;

	wpa_printf(MSG_DEBUG, "WPS UPnP: Stop device");
	web_listener_stop(sm);
	ssdp_listener_stop(sm);
	upnp_wps_free_msearchreply(&sm->msearch_replies);
	upnp_wps_free_subscriptions(&sm->subscriptions, NULL);

	advertisement_state_machine_stop(sm, 1);

	event_send_stop_all(sm);
	os_free(sm->wlanevent);
	sm->wlanevent = NULL;
	os_free(sm->ip_addr_text);
	sm->ip_addr_text = NULL;
	if (sm->multicast_sd >= 0)
		close(sm->multicast_sd);
	sm->multicast_sd = -1;

	sm->started = 0;
}