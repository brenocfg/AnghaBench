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
struct thread {int dummy; } ;
struct save87 {int dummy; } ;
struct fpreg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sv_87; int /*<<< orphan*/  sv_xmm; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (struct fpreg*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cpu_fxsr ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_1__* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  npx_set_fpregs_xmm (struct save87*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npxuserinited (struct thread*) ; 

int
set_fpregs(struct thread *td, struct fpreg *fpregs)
{

	critical_enter();
	if (cpu_fxsr)
		npx_set_fpregs_xmm((struct save87 *)fpregs,
		    &get_pcb_user_save_td(td)->sv_xmm);
	else
		bcopy(fpregs, &get_pcb_user_save_td(td)->sv_87,
		    sizeof(*fpregs));
	npxuserinited(td);
	critical_exit();
	return (0);
}