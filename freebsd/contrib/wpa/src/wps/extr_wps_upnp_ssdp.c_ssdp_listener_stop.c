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
struct upnp_wps_device_sm {int ssdp_sd; scalar_t__ ssdp_sd_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOOP_ALL_CTX ; 
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct upnp_wps_device_sm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_unregister_sock (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msearchreply_state_machine_handler ; 

void ssdp_listener_stop(struct upnp_wps_device_sm *sm)
{
	if (sm->ssdp_sd_registered) {
		eloop_unregister_sock(sm->ssdp_sd, EVENT_TYPE_READ);
		sm->ssdp_sd_registered = 0;
	}

	if (sm->ssdp_sd != -1) {
		close(sm->ssdp_sd);
		sm->ssdp_sd = -1;
	}

	eloop_cancel_timeout(msearchreply_state_machine_handler, sm,
			     ELOOP_ALL_CTX);
}