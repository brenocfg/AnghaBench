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
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ *) ; 
 int WAIT_OBJECT_0 ; 
 int WAIT_TIMEOUT ; 
 int WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/ * timer_event ; 
 int /*<<< orphan*/ * timer_thread ; 

__attribute__((used)) static void stop_timer_thread(void)
{
	if (timer_event)
		SetEvent(timer_event);	/* tell thread to terminate */
	if (timer_thread) {
		int rc = WaitForSingleObject(timer_thread, 10000);
		if (rc == WAIT_TIMEOUT)
			error("timer thread did not terminate timely");
		else if (rc != WAIT_OBJECT_0)
			error("waiting for timer thread failed: %lu",
			      GetLastError());
		CloseHandle(timer_thread);
	}
	if (timer_event)
		CloseHandle(timer_event);
	timer_event = NULL;
	timer_thread = NULL;
}