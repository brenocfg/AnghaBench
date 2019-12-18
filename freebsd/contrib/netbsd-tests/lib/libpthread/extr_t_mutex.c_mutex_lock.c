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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int pthread_mutex_timedlock (int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  timespecadd (struct timespec*,struct timespec const*,struct timespec*) ; 

__attribute__((used)) static int
mutex_lock(pthread_mutex_t *m, const struct timespec *ts)
{
	struct timespec ts_wait;
	ATF_REQUIRE(clock_gettime(CLOCK_REALTIME, &ts_wait) != -1);
	timespecadd(&ts_wait, ts, &ts_wait);

	return pthread_mutex_timedlock(m, &ts_wait);
}