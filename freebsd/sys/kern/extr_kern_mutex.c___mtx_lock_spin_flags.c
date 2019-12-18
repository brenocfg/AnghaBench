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
struct TYPE_5__ {int lo_flags; int /*<<< orphan*/  lo_name; } ;
struct mtx {scalar_t__ mtx_lock; TYPE_1__ lock_object; int /*<<< orphan*/  mtx_recurse; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOCKSTAT_PROFILE_OBTAIN_LOCK_SUCCESS (int /*<<< orphan*/ ,struct mtx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * LOCK_CLASS (TYPE_1__*) ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,TYPE_1__*,int,int /*<<< orphan*/ ,char const*,int) ; 
 int LOP_EXCLUSIVE ; 
 int LOP_NEWORDER ; 
 int LO_RECURSABLE ; 
 scalar_t__ MTX_DESTROYED ; 
 int MTX_RECURSE ; 
 uintptr_t MTX_UNOWNED ; 
 int /*<<< orphan*/  WITNESS_CHECKORDER (TYPE_1__*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WITNESS_LOCK (TYPE_1__*,int,char const*,int) ; 
 int /*<<< orphan*/  __mtx_lock_spin (struct mtx*,scalar_t__,int,char const*,int) ; 
 int /*<<< orphan*/  _mtx_lock_spin (struct mtx*,uintptr_t,int,char const*,int) ; 
 int /*<<< orphan*/  _mtx_obtain_lock_fetch (struct mtx*,uintptr_t*,uintptr_t) ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  lock_class_mtx_spin ; 
 scalar_t__ mtx_owned (struct mtx*) ; 
 struct mtx* mtxlock2mtx (uintptr_t volatile*) ; 
 int /*<<< orphan*/  spin__acquire ; 
 int /*<<< orphan*/  spinlock_enter () ; 

void
__mtx_lock_spin_flags(volatile uintptr_t *c, int opts, const char *file,
    int line)
{
	struct mtx *m;
#ifdef SMP
	uintptr_t tid, v;
#endif

	m = mtxlock2mtx(c);

	KASSERT(m->mtx_lock != MTX_DESTROYED,
	    ("mtx_lock_spin() of destroyed mutex @ %s:%d", file, line));
	KASSERT(LOCK_CLASS(&m->lock_object) == &lock_class_mtx_spin,
	    ("mtx_lock_spin() of sleep mutex %s @ %s:%d",
	    m->lock_object.lo_name, file, line));
	if (mtx_owned(m))
		KASSERT((m->lock_object.lo_flags & LO_RECURSABLE) != 0 ||
		    (opts & MTX_RECURSE) != 0,
	    ("mtx_lock_spin: recursed on non-recursive mutex %s @ %s:%d\n",
		    m->lock_object.lo_name, file, line));
	opts &= ~MTX_RECURSE;
	WITNESS_CHECKORDER(&m->lock_object, opts | LOP_NEWORDER | LOP_EXCLUSIVE,
	    file, line, NULL);
#ifdef SMP
	spinlock_enter();
	tid = (uintptr_t)curthread;
	v = MTX_UNOWNED;
	if (!_mtx_obtain_lock_fetch(m, &v, tid))
		_mtx_lock_spin(m, v, opts, file, line);
	else
		LOCKSTAT_PROFILE_OBTAIN_LOCK_SUCCESS(spin__acquire,
		    m, 0, 0, file, line);
#else
	__mtx_lock_spin(m, curthread, opts, file, line);
#endif
	LOCK_LOG_LOCK("LOCK", &m->lock_object, opts, m->mtx_recurse, file,
	    line);
	WITNESS_LOCK(&m->lock_object, opts | LOP_EXCLUSIVE, file, line);
}