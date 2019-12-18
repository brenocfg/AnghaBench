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
struct cpu_usage_timer {int /*<<< orphan*/  timeBegin; int /*<<< orphan*/  ticksBegin; int /*<<< orphan*/  kerneltimeBegin; int /*<<< orphan*/  usertimeBegin; int /*<<< orphan*/  thread; } ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentThread () ; 
 int GetThreadTimes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock () ; 
 int /*<<< orphan*/  evutil_gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
start_cpu_usage_timer(struct cpu_usage_timer *timer)
{
#ifdef _WIN32
	int r;
	FILETIME createtime, exittime;
	timer->thread = GetCurrentThread();
	r = GetThreadTimes(timer->thread, &createtime, &exittime,
	    &timer->usertimeBegin, &timer->kerneltimeBegin);
	if (r==0) printf("GetThreadTimes failed.");
#else
	timer->ticksBegin = clock();
#endif

	evutil_gettimeofday(&timer->timeBegin, NULL);
}