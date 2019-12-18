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
struct pthread_mutex {int /*<<< orphan*/  m_lock; } ;
struct pthread {uintptr_t inact_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC (char*) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  is_robust_mutex (struct pthread_mutex*) ; 
 int /*<<< orphan*/  mutex_init_robust (struct pthread*) ; 

int
_mutex_enter_robust(struct pthread *curthread, struct pthread_mutex *m)
{

#if defined(_PTHREADS_INVARIANTS)
	if (__predict_false(curthread->inact_mtx != 0))
		PANIC("inact_mtx enter");
#endif
	if (!is_robust_mutex(m))
		return (0);

	mutex_init_robust(curthread);
	curthread->inact_mtx = (uintptr_t)&m->m_lock;
	return (1);
}