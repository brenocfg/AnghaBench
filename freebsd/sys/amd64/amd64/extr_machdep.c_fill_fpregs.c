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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ P_SHOULDSTOP (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_IS_SUSPENDED (struct thread*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fill_fpregs_xmm (int /*<<< orphan*/ ,struct fpreg*) ; 
 int /*<<< orphan*/  fpugetregs (struct thread*) ; 
 int /*<<< orphan*/  get_pcb_user_save_td (struct thread*) ; 

int
fill_fpregs(struct thread *td, struct fpreg *fpregs)
{

	KASSERT(td == curthread || TD_IS_SUSPENDED(td) ||
	    P_SHOULDSTOP(td->td_proc),
	    ("not suspended thread %p", td));
	fpugetregs(td);
	fill_fpregs_xmm(get_pcb_user_save_td(td), fpregs);
	return (0);
}