#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct reg {uintptr_t r_rip; } ;
struct TYPE_4__ {int p_flag; int /*<<< orphan*/  p_pid; struct TYPE_4__* p_parent; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_5__ {uintptr_t t_dtrace_pc; uintptr_t t_dtrace_npc; scalar_t__ t_dtrace_astpc; scalar_t__ t_dtrace_scrpc; } ;

/* Variables and functions */
 int SVFORK ; 
 TYPE_1__* curproc ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  fasttrap_return_common (struct reg*,uintptr_t,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  fill_frame_regs (struct trapframe*,struct reg*) ; 

int
fasttrap_return_probe(struct trapframe *tf)
{
	struct reg reg, *rp;
	proc_t *p = curproc;
	uintptr_t pc = curthread->t_dtrace_pc;
	uintptr_t npc = curthread->t_dtrace_npc;

	fill_frame_regs(tf, &reg);
	rp = &reg;

	curthread->t_dtrace_pc = 0;
	curthread->t_dtrace_npc = 0;
	curthread->t_dtrace_scrpc = 0;
	curthread->t_dtrace_astpc = 0;

#ifdef illumos
	/*
	 * Treat a child created by a call to vfork(2) as if it were its
	 * parent. We know that there's only one thread of control in such a
	 * process: this one.
	 */
	while (p->p_flag & SVFORK) {
		p = p->p_parent;
	}
#endif

	/*
	 * We set rp->r_rip to the address of the traced instruction so
	 * that it appears to dtrace_probe() that we're on the original
	 * instruction.
	 */
	rp->r_rip = pc;

	fasttrap_return_common(rp, pc, p->p_pid, npc);

	return (0);
}