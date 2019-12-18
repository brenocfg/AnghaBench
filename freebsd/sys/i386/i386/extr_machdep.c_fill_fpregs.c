#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_proc; } ;
struct save87 {int dummy; } ;
struct fpreg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sv_87; int /*<<< orphan*/  sv_xmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ P_SHOULDSTOP (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_IS_SUSPENDED (struct thread*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct fpreg*,int) ; 
 scalar_t__ cpu_fxsr ; 
 struct thread* curthread ; 
 TYPE_1__* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  npx_fill_fpregs_xmm (int /*<<< orphan*/ *,struct save87*) ; 
 int /*<<< orphan*/  npxgetregs (struct thread*) ; 

int
fill_fpregs(struct thread *td, struct fpreg *fpregs)
{

	KASSERT(td == curthread || TD_IS_SUSPENDED(td) ||
	    P_SHOULDSTOP(td->td_proc),
	    ("not suspended thread %p", td));
	npxgetregs(td);
	if (cpu_fxsr)
		npx_fill_fpregs_xmm(&get_pcb_user_save_td(td)->sv_xmm,
		    (struct save87 *)fpregs);
	else
		bcopy(&get_pcb_user_save_td(td)->sv_87, fpregs,
		    sizeof(*fpregs));
	return (0);
}