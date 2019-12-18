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
struct mtx {scalar_t__ mtx_lock; int /*<<< orphan*/  mtx_recurse; TYPE_1__ lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/ * LOCK_CLASS (TYPE_1__*) ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,TYPE_1__*,int,int /*<<< orphan*/ ,char const*,int) ; 
 int LOP_EXCLUSIVE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ MTX_DESTROYED ; 
 int /*<<< orphan*/  WITNESS_UNLOCK (TYPE_1__*,int,char const*,int) ; 
 int /*<<< orphan*/  __mtx_unlock_spin (struct mtx*) ; 
 int /*<<< orphan*/  lock_class_mtx_spin ; 
 int /*<<< orphan*/  mtx_assert (struct mtx*,int /*<<< orphan*/ ) ; 
 struct mtx* mtxlock2mtx (uintptr_t volatile*) ; 

void
__mtx_unlock_spin_flags(volatile uintptr_t *c, int opts, const char *file,
    int line)
{
	struct mtx *m;

	m = mtxlock2mtx(c);

	KASSERT(m->mtx_lock != MTX_DESTROYED,
	    ("mtx_unlock_spin() of destroyed mutex @ %s:%d", file, line));
	KASSERT(LOCK_CLASS(&m->lock_object) == &lock_class_mtx_spin,
	    ("mtx_unlock_spin() of sleep mutex %s @ %s:%d",
	    m->lock_object.lo_name, file, line));
	WITNESS_UNLOCK(&m->lock_object, opts | LOP_EXCLUSIVE, file, line);
	LOCK_LOG_LOCK("UNLOCK", &m->lock_object, opts, m->mtx_recurse, file,
	    line);
	mtx_assert(m, MA_OWNED);

	__mtx_unlock_spin(m);
}