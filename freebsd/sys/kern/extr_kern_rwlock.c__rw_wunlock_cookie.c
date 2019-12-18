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
struct rwlock {scalar_t__ rw_lock; int /*<<< orphan*/  rw_recurse; int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  LOP_EXCLUSIVE ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 scalar_t__ RW_DESTROYED ; 
 int /*<<< orphan*/  TD_LOCKS_DEC (scalar_t__) ; 
 int /*<<< orphan*/  WITNESS_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  __rw_assert (uintptr_t volatile*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  __rw_wunlock (struct rwlock*,scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  _rw_wunlock_hard (struct rwlock*,uintptr_t,char const*,int) ; 
 scalar_t__ curthread ; 
 struct rwlock* rwlock2rw (uintptr_t volatile*) ; 

void
_rw_wunlock_cookie(volatile uintptr_t *c, const char *file, int line)
{
	struct rwlock *rw;

	rw = rwlock2rw(c);

	KASSERT(rw->rw_lock != RW_DESTROYED,
	    ("rw_wunlock() of destroyed rwlock @ %s:%d", file, line));
	__rw_assert(c, RA_WLOCKED, file, line);
	WITNESS_UNLOCK(&rw->lock_object, LOP_EXCLUSIVE, file, line);
	LOCK_LOG_LOCK("WUNLOCK", &rw->lock_object, 0, rw->rw_recurse, file,
	    line);

#ifdef LOCK_PROFILING
	_rw_wunlock_hard(rw, (uintptr_t)curthread, file, line);
#else
	__rw_wunlock(rw, curthread, file, line);
#endif

	TD_LOCKS_DEC(curthread);
}