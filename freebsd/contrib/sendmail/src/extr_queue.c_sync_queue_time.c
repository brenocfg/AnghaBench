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

/* Variables and functions */
 scalar_t__ CurrentPid ; 
 scalar_t__ LastQueuePid ; 
 scalar_t__ LastQueueTime ; 
 scalar_t__ MD_CHECKCONFIG ; 
 scalar_t__ MD_TEST ; 
 scalar_t__ MD_VERIFY ; 
 scalar_t__ OpMode ; 
 scalar_t__ curtime () ; 
 int /*<<< orphan*/  sleep (int) ; 

void
sync_queue_time()
{
#if FAST_PID_RECYCLE
	if (OpMode != MD_TEST &&
	    OpMode != MD_CHECKCONFIG &&
	    OpMode != MD_VERIFY &&
	    LastQueueTime > 0 &&
	    LastQueuePid == CurrentPid &&
	    curtime() == LastQueueTime)
		(void) sleep(1);
#endif /* FAST_PID_RECYCLE */
}