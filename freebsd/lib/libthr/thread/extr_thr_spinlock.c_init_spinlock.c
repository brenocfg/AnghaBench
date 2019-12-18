#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pthread {int dummy; } ;
struct TYPE_4__ {TYPE_3__* thr_extra; } ;
typedef  TYPE_1__ spinlock_t ;
struct TYPE_5__ {TYPE_1__* owner; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t MAX_SPINLOCKS ; 
 int /*<<< orphan*/  PANIC (char*) ; 
 int /*<<< orphan*/  THR_UMUTEX_LOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_UMUTEX_UNLOCK (struct pthread*,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 TYPE_3__* extra ; 
 size_t spinlock_count ; 
 int /*<<< orphan*/  spinlock_static_lock ; 

__attribute__((used)) static void
init_spinlock(spinlock_t *lck)
{
	struct pthread *curthread = _get_curthread();

	THR_UMUTEX_LOCK(curthread, &spinlock_static_lock);
	if ((lck->thr_extra == NULL) && (spinlock_count < MAX_SPINLOCKS)) {
		lck->thr_extra = &extra[spinlock_count];
		_thr_umutex_init(&extra[spinlock_count].lock);
		extra[spinlock_count].owner = lck;
		spinlock_count++;
	}
	THR_UMUTEX_UNLOCK(curthread, &spinlock_static_lock);
	if (lck->thr_extra == NULL)
		PANIC("Warning: exceeded max spinlocks");
}