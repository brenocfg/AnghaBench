#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_proc; } ;
struct linux_pt_fpxreg {int dummy; } ;
struct TYPE_4__ {int p_flag; } ;
struct TYPE_3__ {int /*<<< orphan*/  sv_xmm; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int P_INMEM ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,struct linux_pt_fpxreg*,int) ; 
 scalar_t__ cpu_fxsr ; 
 TYPE_1__* get_pcb_user_save_td (struct thread*) ; 

__attribute__((used)) static int
linux_proc_read_fpxregs(struct thread *td, struct linux_pt_fpxreg *fpxregs)
{

	PROC_LOCK_ASSERT(td->td_proc, MA_OWNED);
	if (cpu_fxsr == 0 || (td->td_proc->p_flag & P_INMEM) == 0)
		return (EIO);
	bcopy(&get_pcb_user_save_td(td)->sv_xmm, fpxregs, sizeof(*fpxregs));
	return (0);
}