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
struct proc {int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int P_INMEM ; 
 int /*<<< orphan*/  panic (char*,struct proc*) ; 

void
faultin(struct proc *p)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	if ((p->p_flag & P_INMEM) == 0)
		panic("faultin: proc %p swapped out with NO_SWAPPING", p);
}