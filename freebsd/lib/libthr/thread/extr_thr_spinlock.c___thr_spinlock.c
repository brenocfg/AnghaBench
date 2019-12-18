#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct spinlock_extra {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct spinlock_extra* thr_extra; } ;
typedef  TYPE_1__ spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC (char*) ; 
 int /*<<< orphan*/  THR_UMUTEX_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _get_curthread () ; 
 int /*<<< orphan*/  _thr_isthreaded () ; 
 int /*<<< orphan*/  init_spinlock (TYPE_1__*) ; 
 int /*<<< orphan*/  initialized ; 

void
__thr_spinlock(spinlock_t *lck)
{
	struct spinlock_extra *_extra;

	if (!_thr_isthreaded())
		PANIC("Spinlock called when not threaded.");
	if (!initialized)
		PANIC("Spinlocks not initialized.");
	if (lck->thr_extra == NULL)
		init_spinlock(lck);
	_extra = lck->thr_extra;
	THR_UMUTEX_LOCK(_get_curthread(), &_extra->lock);
}