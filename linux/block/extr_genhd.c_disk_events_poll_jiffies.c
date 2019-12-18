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
struct gendisk {int event_flags; struct disk_events* ev; } ;
struct disk_events {long poll_msecs; } ;

/* Variables and functions */
 int DISK_EVENT_FLAG_POLL ; 
 long disk_events_dfl_poll_msecs ; 
 unsigned long msecs_to_jiffies (long) ; 

__attribute__((used)) static unsigned long disk_events_poll_jiffies(struct gendisk *disk)
{
	struct disk_events *ev = disk->ev;
	long intv_msecs = 0;

	/*
	 * If device-specific poll interval is set, always use it.  If
	 * the default is being used, poll if the POLL flag is set.
	 */
	if (ev->poll_msecs >= 0)
		intv_msecs = ev->poll_msecs;
	else if (disk->event_flags & DISK_EVENT_FLAG_POLL)
		intv_msecs = disk_events_dfl_poll_msecs;

	return msecs_to_jiffies(intv_msecs);
}