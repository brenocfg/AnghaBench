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
struct timespec {scalar_t__ tv_sec; int tv_nsec; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
typedef  int /*<<< orphan*/  pthread_cond_t ;

/* Variables and functions */
 int EINVAL ; 
 int cond_wait_common (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int /*<<< orphan*/ ) ; 

int
_thr_cond_timedwait(pthread_cond_t * __restrict cond,
    pthread_mutex_t * __restrict mutex,
    const struct timespec * __restrict abstime)
{

	if (abstime == NULL || abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
	    abstime->tv_nsec >= 1000000000)
		return (EINVAL);

	return (cond_wait_common(cond, mutex, abstime, 0));
}