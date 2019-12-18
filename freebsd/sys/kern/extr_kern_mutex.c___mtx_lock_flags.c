#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lo_name; } ;
struct mtx {scalar_t__ mtx_lock; TYPE_1__ lock_object; int /*<<< orphan*/  mtx_recurse; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOCKSTAT_PROFILE_OBTAIN_LOCK_SUCCESS (int /*<<< orphan*/ ,struct mtx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * LOCK_CLASS (TYPE_1__*) ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,TYPE_1__*,int,int /*<<< orphan*/ ,char const*,int) ; 
 int LOP_EXCLUSIVE ; 
 int LOP_NEWORDER ; 
 scalar_t__ MTX_DESTROYED ; 
 int MTX_RECURSE ; 
 uintptr_t MTX_UNOWNED ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  TD_IS_IDLETHREAD (scalar_t__) ; 
 int /*<<< orphan*/  TD_LOCKS_INC (scalar_t__) ; 
 int /*<<< orphan*/  WITNESS_CHECKORDER (TYPE_1__*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WITNESS_LOCK (TYPE_1__*,int,char const*,int) ; 
 int /*<<< orphan*/  _mtx_lock_sleep (struct mtx*,uintptr_t,int,char const*,int) ; 
 int /*<<< orphan*/  _mtx_obtain_lock_fetch (struct mtx*,uintptr_t*,uintptr_t) ; 
 int /*<<< orphan*/  adaptive__acquire ; 
 scalar_t__ curthread ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  lock_class_mtx_sleep ; 
 struct mtx* mtxlock2mtx (uintptr_t volatile*) ; 

void
__mtx_lock_flags(volatile uintptr_t *c, int opts, const char *file, int line)
{
	struct mtx *m;
	uintptr_t tid, v;

	m = mtxlock2mtx(c);

	KASSERT(kdb_active != 0 || SCHEDULER_STOPPED() ||
	    !TD_IS_IDLETHREAD(curthread),
	    ("mtx_lock() by idle thread %p on sleep mutex %s @ %s:%d",
	    curthread, m->lock_object.lo_name, file, line));
	KASSERT(m->mtx_lock != MTX_DESTROYED,
	    ("mtx_lock() of destroyed mutex @ %s:%d", file, line));
	KASSERT(LOCK_CLASS(&m->lock_object) == &lock_class_mtx_sleep,
	    ("mtx_lock() of spin mutex %s @ %s:%d", m->lock_object.lo_name,
	    file, line));
	WITNESS_CHECKORDER(&m->lock_object, (opts & ~MTX_RECURSE) |
	    LOP_NEWORDER | LOP_EXCLUSIVE, file, line, NULL);

	tid = (uintptr_t)curthread;
	v = MTX_UNOWNED;
	if (!_mtx_obtain_lock_fetch(m, &v, tid))
		_mtx_lock_sleep(m, v, opts, file, line);
	else
		LOCKSTAT_PROFILE_OBTAIN_LOCK_SUCCESS(adaptive__acquire,
		    m, 0, 0, file, line);
	LOCK_LOG_LOCK("LOCK", &m->lock_object, opts, m->mtx_recurse, file,
	    line);
	WITNESS_LOCK(&m->lock_object, (opts & ~MTX_RECURSE) | LOP_EXCLUSIVE,
	    file, line);
	TD_LOCKS_INC(curthread);
}