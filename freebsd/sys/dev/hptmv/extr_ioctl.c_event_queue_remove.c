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
typedef  int /*<<< orphan*/ * PHPT_EVENT ;

/* Variables and functions */
 size_t MAX_EVENTS ; 
 size_t event_queue_head ; 
 size_t event_queue_tail ; 
 int /*<<< orphan*/ * hpt_event_queue ; 

__attribute__((used)) static int
event_queue_remove(PHPT_EVENT pEvent)
{
	if (event_queue_head != event_queue_tail)
	{
		*pEvent = hpt_event_queue[event_queue_head];
		event_queue_head++;
		event_queue_head %= MAX_EVENTS;
		return 0;
	}
	return -1;
}