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
struct smt_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_STATE_UNUSED ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
t4_smt_release(struct smt_entry *e)
{
	MPASS(e != NULL);
	if (atomic_fetchadd_int(&e->refcnt, -1) == 1) {
		mtx_lock(&e->lock);
		e->state = SMT_STATE_UNUSED;
		mtx_unlock(&e->lock);
	}

}