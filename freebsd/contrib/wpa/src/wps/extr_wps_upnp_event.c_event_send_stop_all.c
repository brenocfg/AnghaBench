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
struct upnp_wps_device_sm {scalar_t__ event_send_all_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct upnp_wps_device_sm*) ; 
 int /*<<< orphan*/  event_send_all_later_handler ; 

void event_send_stop_all(struct upnp_wps_device_sm *sm)
{
	if (sm->event_send_all_queued)
		eloop_cancel_timeout(event_send_all_later_handler, NULL, sm);
	sm->event_send_all_queued = 0;
}