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
struct pthread_spinlock {int /*<<< orphan*/  s_lock; } ;
typedef  struct pthread_spinlock* pthread_spinlock_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int PTHREAD_PROCESS_PRIVATE ; 
 int PTHREAD_PROCESS_SHARED ; 
 struct pthread_spinlock* THR_PSHARED_PTR ; 
 struct pthread_spinlock* __thr_pshared_offpage (struct pthread_spinlock**,int) ; 
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 struct pthread_spinlock* malloc (int) ; 

int
_pthread_spin_init(pthread_spinlock_t *lock, int pshared)
{
	struct pthread_spinlock	*lck;

	if (lock == NULL)
		return (EINVAL);
	if (pshared == PTHREAD_PROCESS_PRIVATE) {
		lck = malloc(sizeof(struct pthread_spinlock));
		if (lck == NULL)
			return (ENOMEM);
		*lock = lck;
	} else if (pshared == PTHREAD_PROCESS_SHARED) {
		lck = __thr_pshared_offpage(lock, 1);
		if (lck == NULL)
			return (EFAULT);
		*lock = THR_PSHARED_PTR;
	} else {
		return (EINVAL);
	}
	_thr_umutex_init(&lck->s_lock);
	return (0);
}