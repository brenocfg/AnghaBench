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
struct proc {int p_numthreads; int p_boundary_count; int p_suspcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int SINGLE_ALLPROC ; 
 int SINGLE_BOUNDARY ; 
 int SINGLE_EXIT ; 
 int SINGLE_NO_EXIT ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
calc_remaining(struct proc *p, int mode)
{
	int remaining;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	PROC_SLOCK_ASSERT(p, MA_OWNED);
	if (mode == SINGLE_EXIT)
		remaining = p->p_numthreads;
	else if (mode == SINGLE_BOUNDARY)
		remaining = p->p_numthreads - p->p_boundary_count;
	else if (mode == SINGLE_NO_EXIT || mode == SINGLE_ALLPROC)
		remaining = p->p_numthreads - p->p_suspcount;
	else
		panic("calc_remaining: wrong mode %d", mode);
	return (remaining);
}