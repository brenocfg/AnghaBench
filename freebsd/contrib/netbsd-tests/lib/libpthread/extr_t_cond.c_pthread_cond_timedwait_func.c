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
struct timespec {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  memset (struct timespec*,int /*<<< orphan*/ ,int) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_cond ; 
 int /*<<< orphan*/  static_mutex ; 

__attribute__((used)) static void *
pthread_cond_timedwait_func(void *arg)
{
	struct timespec ts;
	size_t i = 0;
	int rv;

	for (;;) {

		if (i++ >= 10000)
			pthread_exit(NULL);

		(void)memset(&ts, 0, sizeof(struct timespec));

		ATF_REQUIRE(clock_gettime(CLOCK_REALTIME, &ts) == 0);

		/*
		 * Set to one second in the past:
		 * pthread_cond_timedwait(3) should
		 * return ETIMEDOUT immediately.
		 */
		ts.tv_sec = ts.tv_sec - 1;

		PTHREAD_REQUIRE(pthread_mutex_lock(&static_mutex));
		rv = pthread_cond_timedwait(&static_cond, &static_mutex, &ts);

		/*
		 * Sometimes we catch ESRCH.
		 * This should never happen.
		 */
		ATF_REQUIRE(rv == ETIMEDOUT);
		PTHREAD_REQUIRE(pthread_mutex_unlock(&static_mutex));
	}
}