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
struct upnp_wps_device_sm {int event_send_all_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DELAY_MSEC ; 
 int /*<<< orphan*/  EVENT_DELAY_SECONDS ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  event_send_all_later_handler ; 

void event_send_all_later(struct upnp_wps_device_sm *sm)
{
	/*
	 * The exact time in the future isn't too important. Waiting a bit
	 * might let us do several together.
	 */
	if (sm->event_send_all_queued)
		return;
	sm->event_send_all_queued = 1;
	eloop_register_timeout(EVENT_DELAY_SECONDS, EVENT_DELAY_MSEC,
			       event_send_all_later_handler, NULL, sm);
}