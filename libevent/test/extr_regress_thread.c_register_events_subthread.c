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
struct timeval {int tv_usec; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  THREAD_FN ;

/* Variables and functions */
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  SLEEP_MS (int) ; 
 int /*<<< orphan*/  THREAD_RETURN () ; 
 int /*<<< orphan*/  event_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/ * time_events ; 

__attribute__((used)) static THREAD_FN
register_events_subthread(void *arg)
{
	struct timeval tv = {0,0};
	SLEEP_MS(100);
	event_active(&time_events[0], EV_TIMEOUT, 1);
	SLEEP_MS(100);
	event_active(&time_events[1], EV_TIMEOUT, 1);
	SLEEP_MS(100);
	tv.tv_usec = 100*1000;
	event_add(&time_events[2], &tv);
	tv.tv_usec = 150*1000;
	event_add(&time_events[3], &tv);
	SLEEP_MS(200);
	event_active(&time_events[4], EV_TIMEOUT, 1);

	THREAD_RETURN();
}