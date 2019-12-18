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
 int MAX_EVENTS ; 
 int event_queue_head ; 
 int event_queue_tail ; 
 int /*<<< orphan*/ * hpt_event_queue ; 

__attribute__((used)) static int
event_queue_add(PHPT_EVENT pEvent)
{
	int p;
	p = (event_queue_tail + 1) % MAX_EVENTS;
	if (p==event_queue_head)
	{
		return -1;
	}
	hpt_event_queue[event_queue_tail] = *pEvent;
	event_queue_tail = p;
	return 0;
}