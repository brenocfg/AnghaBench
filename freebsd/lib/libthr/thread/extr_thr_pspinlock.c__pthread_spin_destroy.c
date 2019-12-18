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
typedef  int /*<<< orphan*/ * pthread_spinlock_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * THR_PSHARED_PTR ; 
 int /*<<< orphan*/  __thr_pshared_destroy (void*) ; 
 void* __thr_pshared_offpage (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
_pthread_spin_destroy(pthread_spinlock_t *lock)
{
	void *l;
	int ret;

	if (lock == NULL || *lock == NULL) {
		ret = EINVAL;
	} else if (*lock == THR_PSHARED_PTR) {
		l = __thr_pshared_offpage(lock, 0);
		if (l != NULL)
			__thr_pshared_destroy(l);
		ret = 0;
	} else {
		free(*lock);
		*lock = NULL;
		ret = 0;
	}
	return (ret);
}