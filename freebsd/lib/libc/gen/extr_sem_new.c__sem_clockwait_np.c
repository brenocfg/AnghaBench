#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_nsec; } ;
struct TYPE_6__ {int _count; } ;
struct TYPE_5__ {TYPE_2__ _kern; } ;
typedef  TYPE_1__ sem_t ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ USEM_COUNT (int) ; 
 int /*<<< orphan*/  _pthread_cancel_enter (int) ; 
 int /*<<< orphan*/  _pthread_cancel_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_testcancel () ; 
 scalar_t__ atomic_cmpset_acq_int (int*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sem_check_validity (TYPE_1__*) ; 
 int usem_wait (TYPE_2__*,int /*<<< orphan*/ ,int,struct timespec const*,struct timespec*) ; 

int
_sem_clockwait_np(sem_t * __restrict sem, clockid_t clock_id, int flags,
	const struct timespec *rqtp, struct timespec *rmtp)
{
	int val, retval;

	if (sem_check_validity(sem) != 0)
		return (-1);

	retval = 0;
	_pthread_testcancel();
	for (;;) {
		while (USEM_COUNT(val = sem->_kern._count) > 0) {
			if (atomic_cmpset_acq_int(&sem->_kern._count, val,
			    val - 1))
				return (0);
		}

		if (retval) {
			_pthread_testcancel();
			break;
		}

		/*
		 * The timeout argument is only supposed to
		 * be checked if the thread would have blocked.
		 */
		if (rqtp != NULL) {
			if (rqtp->tv_nsec >= 1000000000 || rqtp->tv_nsec < 0) {
				errno = EINVAL;
				return (-1);
			}
		}
		_pthread_cancel_enter(1);
		retval = usem_wait(&sem->_kern, clock_id, flags, rqtp, rmtp);
		_pthread_cancel_leave(0);
	}
	return (retval);
}