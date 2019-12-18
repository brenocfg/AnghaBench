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
struct user_evtchn {int enabled; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evtchn_dev ; 
 int /*<<< orphan*/  evtchn_mask_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evtchn_filter(void *arg)
{
	struct user_evtchn *evtchn;

	evtchn = arg;

	if (!evtchn->enabled && bootverbose) {
		device_printf(evtchn_dev,
		    "Received upcall for disabled event channel %d\n",
		    evtchn->port);
	}

	evtchn_mask_port(evtchn->port);
	evtchn->enabled = false;

	return (FILTER_SCHEDULE_THREAD);
}