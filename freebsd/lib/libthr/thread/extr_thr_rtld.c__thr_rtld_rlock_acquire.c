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
struct rtld_lock {int /*<<< orphan*/  lock; } ;
struct pthread {int /*<<< orphan*/  rdlock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESTORE_ERRNO () ; 
 int /*<<< orphan*/  SAVE_ERRNO () ; 
 int /*<<< orphan*/  THR_CRITICAL_ENTER (struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 scalar_t__ _thr_rwlock_rdlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_thr_rtld_rlock_acquire(void *lock)
{
	struct pthread		*curthread;
	struct rtld_lock	*l;
	int			errsave;

	curthread = _get_curthread();
	SAVE_ERRNO();
	l = (struct rtld_lock *)lock;

	THR_CRITICAL_ENTER(curthread);
	while (_thr_rwlock_rdlock(&l->lock, 0, NULL) != 0)
		;
	curthread->rdlock_count++;
	RESTORE_ERRNO();
}