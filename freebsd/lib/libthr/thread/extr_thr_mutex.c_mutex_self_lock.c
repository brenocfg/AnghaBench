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
struct timespec {int tv_sec; int tv_nsec; } ;
struct pthread_mutex {int /*<<< orphan*/  m_count; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EAGAIN ; 
 int EDEADLK ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int PMUTEX_TYPE (int /*<<< orphan*/ ) ; 
#define  PTHREAD_MUTEX_ADAPTIVE_NP 131 
#define  PTHREAD_MUTEX_ERRORCHECK 130 
#define  PTHREAD_MUTEX_NORMAL 129 
#define  PTHREAD_MUTEX_RECURSIVE 128 
 int /*<<< orphan*/  TIMESPEC_SUB (struct timespec*,struct timespec const*,struct timespec*) ; 
 int /*<<< orphan*/  __sys_nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static int
mutex_self_lock(struct pthread_mutex *m, const struct timespec *abstime)
{
	struct timespec	ts1, ts2;
	int ret;

	switch (PMUTEX_TYPE(m->m_flags)) {
	case PTHREAD_MUTEX_ERRORCHECK:
	case PTHREAD_MUTEX_ADAPTIVE_NP:
		if (abstime) {
			if (abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
			    abstime->tv_nsec >= 1000000000) {
				ret = EINVAL;
			} else {
				clock_gettime(CLOCK_REALTIME, &ts1);
				TIMESPEC_SUB(&ts2, abstime, &ts1);
				__sys_nanosleep(&ts2, NULL);
				ret = ETIMEDOUT;
			}
		} else {
			/*
			 * POSIX specifies that mutexes should return
			 * EDEADLK if a recursive lock is detected.
			 */
			ret = EDEADLK; 
		}
		break;

	case PTHREAD_MUTEX_NORMAL:
		/*
		 * What SS2 define as a 'normal' mutex.  Intentionally
		 * deadlock on attempts to get a lock you already own.
		 */
		ret = 0;
		if (abstime) {
			if (abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
			    abstime->tv_nsec >= 1000000000) {
				ret = EINVAL;
			} else {
				clock_gettime(CLOCK_REALTIME, &ts1);
				TIMESPEC_SUB(&ts2, abstime, &ts1);
				__sys_nanosleep(&ts2, NULL);
				ret = ETIMEDOUT;
			}
		} else {
			ts1.tv_sec = 30;
			ts1.tv_nsec = 0;
			for (;;)
				__sys_nanosleep(&ts1, NULL);
		}
		break;

	case PTHREAD_MUTEX_RECURSIVE:
		/* Increment the lock count: */
		if (m->m_count + 1 > 0) {
			m->m_count++;
			ret = 0;
		} else
			ret = EAGAIN;
		break;

	default:
		/* Trap invalid mutex types; */
		ret = EINVAL;
	}

	return (ret);
}