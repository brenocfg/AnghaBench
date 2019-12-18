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
struct TYPE_4__ {int /*<<< orphan*/  lo_name; } ;
struct rwlock {scalar_t__ rw_lock; TYPE_1__ lock_object; int /*<<< orphan*/  rw_recurse; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOCKSTAT_PROFILE_OBTAIN_RWLOCK_SUCCESS (int /*<<< orphan*/ ,struct rwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_WRITER ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int LOP_EXCLUSIVE ; 
 int LOP_NEWORDER ; 
 scalar_t__ RW_DESTROYED ; 
 uintptr_t RW_UNLOCKED ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  TD_IS_IDLETHREAD (scalar_t__) ; 
 int /*<<< orphan*/  TD_LOCKS_INC (scalar_t__) ; 
 int /*<<< orphan*/  WITNESS_CHECKORDER (TYPE_1__*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WITNESS_LOCK (TYPE_1__*,int,char const*,int) ; 
 int /*<<< orphan*/  _rw_wlock_hard (struct rwlock*,uintptr_t,char const*,int) ; 
 int /*<<< orphan*/  _rw_write_lock_fetch (struct rwlock*,uintptr_t*,uintptr_t) ; 
 scalar_t__ curthread ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  rw__acquire ; 
 struct rwlock* rwlock2rw (uintptr_t volatile*) ; 

void
_rw_wlock_cookie(volatile uintptr_t *c, const char *file, int line)
{
	struct rwlock *rw;
	uintptr_t tid, v;

	rw = rwlock2rw(c);

	KASSERT(kdb_active != 0 || SCHEDULER_STOPPED() ||
	    !TD_IS_IDLETHREAD(curthread),
	    ("rw_wlock() by idle thread %p on rwlock %s @ %s:%d",
	    curthread, rw->lock_object.lo_name, file, line));
	KASSERT(rw->rw_lock != RW_DESTROYED,
	    ("rw_wlock() of destroyed rwlock @ %s:%d", file, line));
	WITNESS_CHECKORDER(&rw->lock_object, LOP_NEWORDER | LOP_EXCLUSIVE, file,
	    line, NULL);
	tid = (uintptr_t)curthread;
	v = RW_UNLOCKED;
	if (!_rw_write_lock_fetch(rw, &v, tid))
		_rw_wlock_hard(rw, v, file, line);
	else
		LOCKSTAT_PROFILE_OBTAIN_RWLOCK_SUCCESS(rw__acquire, rw,
		    0, 0, file, line, LOCKSTAT_WRITER);

	LOCK_LOG_LOCK("WLOCK", &rw->lock_object, 0, rw->rw_recurse, file, line);
	WITNESS_LOCK(&rw->lock_object, LOP_EXCLUSIVE, file, line);
	TD_LOCKS_INC(curthread);
}