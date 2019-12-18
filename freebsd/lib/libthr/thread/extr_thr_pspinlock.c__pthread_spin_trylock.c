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
 int EINVAL ; 
 struct pthread_spinlock* THR_PSHARED_PTR ; 
 int THR_UMUTEX_TRYLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pthread_spinlock* __thr_pshared_offpage (struct pthread_spinlock**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_curthread () ; 

int
_pthread_spin_trylock(pthread_spinlock_t *lock)
{
	struct pthread_spinlock	*lck;

	if (lock == NULL || *lock == NULL)
		return (EINVAL);
	lck = *lock == THR_PSHARED_PTR ? __thr_pshared_offpage(lock, 0) : *lock;
	if (lck == NULL)
		return (EINVAL);
	return (THR_UMUTEX_TRYLOCK(_get_curthread(), &lck->s_lock));
}