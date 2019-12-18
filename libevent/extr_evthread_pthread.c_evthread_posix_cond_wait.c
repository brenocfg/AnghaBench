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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timeradd (struct timeval*,struct timeval const*,struct timeval*) ; 
 int pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evthread_posix_cond_wait(void *cond_, void *lock_, const struct timeval *tv)
{
	int r;
	pthread_cond_t *cond = cond_;
	pthread_mutex_t *lock = lock_;

	if (tv) {
		struct timeval now, abstime;
		struct timespec ts;
		evutil_gettimeofday(&now, NULL);
		evutil_timeradd(&now, tv, &abstime);
		ts.tv_sec = abstime.tv_sec;
		ts.tv_nsec = abstime.tv_usec*1000;
		r = pthread_cond_timedwait(cond, lock, &ts);
		if (r == ETIMEDOUT)
			return 1;
		else if (r)
			return -1;
		else
			return 0;
	} else {
		r = pthread_cond_wait(cond, lock);
		return r ? -1 : 0;
	}
}