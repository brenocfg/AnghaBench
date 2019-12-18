#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
typedef  TYPE_1__* pthread_barrier_t ;
struct TYPE_8__ {int b_destroying; scalar_t__ b_waiters; scalar_t__ b_refcount; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  b_cv; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__* THR_PSHARED_PTR ; 
 int /*<<< orphan*/  THR_UMUTEX_LOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_UMUTEX_UNLOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __thr_pshared_destroy (TYPE_1__**) ; 
 TYPE_1__* __thr_pshared_offpage (TYPE_1__**,int /*<<< orphan*/ ) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_ucond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
_pthread_barrier_destroy(pthread_barrier_t *barrier)
{
	pthread_barrier_t bar;
	struct pthread *curthread;
	int pshared;

	if (barrier == NULL || *barrier == NULL)
		return (EINVAL);

	if (*barrier == THR_PSHARED_PTR) {
		bar = __thr_pshared_offpage(barrier, 0);
		if (bar == NULL) {
			*barrier = NULL;
			return (0);
		}
		pshared = 1;
	} else {
		bar = *barrier;
		pshared = 0;
	}
	curthread = _get_curthread();
	THR_UMUTEX_LOCK(curthread, &bar->b_lock);
	if (bar->b_destroying) {
		THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
		return (EBUSY);
	}
	bar->b_destroying = 1;
	do {
		if (bar->b_waiters > 0) {
			bar->b_destroying = 0;
			THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
			return (EBUSY);
		}
		if (bar->b_refcount != 0) {
			_thr_ucond_wait(&bar->b_cv, &bar->b_lock, NULL, 0);
			THR_UMUTEX_LOCK(curthread, &bar->b_lock);
		} else
			break;
	} while (1);
	bar->b_destroying = 0;
	THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);

	*barrier = NULL;
	if (pshared)
		__thr_pshared_destroy(barrier);
	else
		free(bar);
	return (0);
}