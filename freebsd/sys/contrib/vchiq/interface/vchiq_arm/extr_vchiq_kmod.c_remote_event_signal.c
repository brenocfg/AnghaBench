#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fired; scalar_t__ armed; } ;
typedef  TYPE_1__ REMOTE_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  dsb () ; 
 int /*<<< orphan*/  vchiq_write_4 (int,int /*<<< orphan*/ ) ; 

void
remote_event_signal(REMOTE_EVENT_T *event)
{
	event->fired = 1;

	/* The test on the next line also ensures the write on the previous line
		has completed */
	if (event->armed) {
		/* trigger vc interrupt */
		dsb();
		vchiq_write_4(0x48, 0);
	}
}