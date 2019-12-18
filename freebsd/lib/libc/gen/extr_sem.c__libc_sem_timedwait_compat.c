#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timespec {int tv_nsec; } ;
typedef  TYPE_1__* sem_t ;
struct TYPE_5__ {scalar_t__ syssem; int count; int /*<<< orphan*/  nwaiters; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  _pthread_cancel_enter (int) ; 
 int /*<<< orphan*/  _pthread_cancel_leave (int) ; 
 int /*<<< orphan*/  _pthread_testcancel () ; 
 int _umtx_wait_uint (int*,int /*<<< orphan*/ ,struct timespec const*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_cmpset_acq_int (int*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int ksem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  sem_cancel_handler ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 

int
_libc_sem_timedwait_compat(sem_t * __restrict sem,
	const struct timespec * __restrict abstime)
{
	int val, retval;

	if (sem_check_validity(sem) != 0)
		return (-1);

	if ((*sem)->syssem != 0) {
		_pthread_cancel_enter(1);
		retval = ksem_wait((*sem)->semid); /* XXX no timeout */
		_pthread_cancel_leave(retval == -1);
		return (retval);
	}

	retval = 0;
	_pthread_testcancel();
	for (;;) {
		while ((val = (*sem)->count) > 0) {
			if (atomic_cmpset_acq_int(&(*sem)->count, val, val - 1))
				return (0);
		}
		if (retval) {
			_pthread_testcancel();
			break;
		}
		if (abstime) {
			if (abstime->tv_nsec >= 1000000000 || abstime->tv_nsec < 0) {
				errno = EINVAL;
				return (-1);
			}
		}
		atomic_add_int(&(*sem)->nwaiters, 1);
		pthread_cleanup_push(sem_cancel_handler, sem);
		_pthread_cancel_enter(1);
		retval = _umtx_wait_uint(&(*sem)->count, 0, abstime);
		_pthread_cancel_leave(0);
		pthread_cleanup_pop(0);
		atomic_add_int(&(*sem)->nwaiters, -1);
	}
	return (retval);
}