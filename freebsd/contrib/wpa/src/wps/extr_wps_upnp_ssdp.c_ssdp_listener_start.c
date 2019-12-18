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
struct upnp_wps_device_sm {int ssdp_sd_registered; int /*<<< orphan*/  ssdp_sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ eloop_register_sock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  ssdp_listener_handler ; 
 int /*<<< orphan*/  ssdp_listener_open () ; 
 int /*<<< orphan*/  ssdp_listener_stop (struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int ssdp_listener_start(struct upnp_wps_device_sm *sm)
{
	sm->ssdp_sd = ssdp_listener_open();

	if (eloop_register_sock(sm->ssdp_sd, EVENT_TYPE_READ,
				ssdp_listener_handler, NULL, sm))
		goto fail;
	sm->ssdp_sd_registered = 1;
	return 0;

fail:
	/* Error */
	wpa_printf(MSG_ERROR, "WPS UPnP: ssdp_listener_start failed");
	ssdp_listener_stop(sm);
	return -1;
}