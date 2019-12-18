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
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  alarm (scalar_t__) ; 
 scalar_t__ alarm_fired ; 
 int /*<<< orphan*/  alarm_handler ; 
 scalar_t__ alarm_timeout ; 
 int /*<<< orphan*/  assert (int) ; 
 int clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_start ; 

__attribute__((used)) static void
benchmark_start(void)
{
	int error;

	alarm_fired = 0;
	if (alarm_timeout) {
		signal(SIGALRM, alarm_handler);
		alarm(alarm_timeout);
	}
	error = clock_gettime(CLOCK_REALTIME, &ts_start);
	assert(error == 0);
}