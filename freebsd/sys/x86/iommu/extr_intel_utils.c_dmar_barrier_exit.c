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
typedef  int /*<<< orphan*/  u_int ;
struct dmar_unit {int barrier_flags; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER_F ; 
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int f_done ; 
 int f_inproc ; 
 int f_wakeup ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
dmar_barrier_exit(struct dmar_unit *dmar, u_int barrier_id)
{
	BARRIER_F;

	DMAR_ASSERT_LOCKED(dmar);
	KASSERT((dmar->barrier_flags & (f_done | f_inproc)) == f_inproc,
	    ("dmar%d barrier %d missed entry", dmar->unit, barrier_id));
	dmar->barrier_flags |= f_done;
	if ((dmar->barrier_flags & f_wakeup) != 0)
		wakeup(&dmar->barrier_flags);
	dmar->barrier_flags &= ~(f_inproc | f_wakeup);
	DMAR_UNLOCK(dmar);
}