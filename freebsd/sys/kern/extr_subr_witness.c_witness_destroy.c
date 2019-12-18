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
struct witness {scalar_t__ w_refcount; } ;
struct lock_object {int lo_flags; struct witness* lo_witness; int /*<<< orphan*/  lo_name; } ;
struct lock_class {int /*<<< orphan*/  lc_name; } ;

/* Variables and functions */
 struct lock_class* LOCK_CLASS (struct lock_object*) ; 
 int LO_WITNESS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  depart (struct witness*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_mtx ; 
 scalar_t__ witness_cold ; 

void
witness_destroy(struct lock_object *lock)
{
	struct lock_class *class;
	struct witness *w;

	class = LOCK_CLASS(lock);

	if (witness_cold)
		panic("lock (%s) %s destroyed while witness_cold",
		    class->lc_name, lock->lo_name);

	/* XXX: need to verify that no one holds the lock */
	if ((lock->lo_flags & LO_WITNESS) == 0 || lock->lo_witness == NULL)
		return;
	w = lock->lo_witness;

	mtx_lock_spin(&w_mtx);
	MPASS(w->w_refcount > 0);
	w->w_refcount--;

	if (w->w_refcount == 0)
		depart(w);
	mtx_unlock_spin(&w_mtx);
}