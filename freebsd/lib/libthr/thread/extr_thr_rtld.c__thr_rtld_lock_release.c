#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rw_state; } ;
struct rtld_lock {TYPE_1__ lock; } ;
struct pthread {int /*<<< orphan*/  rdlock_count; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESTORE_ERRNO () ; 
 int /*<<< orphan*/  SAVE_ERRNO () ; 
 int /*<<< orphan*/  THR_CRITICAL_LEAVE (struct pthread*) ; 
 int URWLOCK_WRITE_OWNER ; 
 struct pthread* _get_curthread () ; 
 scalar_t__ _thr_rwlock_unlock (TYPE_1__*) ; 

__attribute__((used)) static void
_thr_rtld_lock_release(void *lock)
{
	struct pthread		*curthread;
	struct rtld_lock	*l;
	int32_t			state;
	int			errsave;

	curthread = _get_curthread();
	SAVE_ERRNO();
	l = (struct rtld_lock *)lock;
	
	state = l->lock.rw_state;
	if (_thr_rwlock_unlock(&l->lock) == 0) {
		if ((state & URWLOCK_WRITE_OWNER) == 0)
			curthread->rdlock_count--;
		THR_CRITICAL_LEAVE(curthread);
	}
	RESTORE_ERRNO();
}