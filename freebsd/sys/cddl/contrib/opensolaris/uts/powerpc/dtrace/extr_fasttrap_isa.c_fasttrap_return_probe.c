#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct reg {uintptr_t pc; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_pid; } ;
typedef  TYPE_1__ proc_t ;
struct TYPE_6__ {uintptr_t t_dtrace_pc; uintptr_t t_dtrace_npc; scalar_t__ t_dtrace_astpc; scalar_t__ t_dtrace_scrpc; } ;

/* Variables and functions */
 TYPE_1__* curproc ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  fasttrap_return_common (struct reg*,uintptr_t,int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  fill_regs (TYPE_2__*,struct reg*) ; 

int
fasttrap_return_probe(struct trapframe *tf)
{
	struct reg reg, *rp;
	proc_t *p = curproc;
	uintptr_t pc = curthread->t_dtrace_pc;
	uintptr_t npc = curthread->t_dtrace_npc;

	curthread->t_dtrace_pc = 0;
	curthread->t_dtrace_npc = 0;
	curthread->t_dtrace_scrpc = 0;
	curthread->t_dtrace_astpc = 0;

	fill_regs(curthread, &reg);
	rp = &reg;

	/*
	 * We set rp->pc to the address of the traced instruction so
	 * that it appears to dtrace_probe() that we're on the original
	 * instruction.
	 */
	rp->pc = pc;

	fasttrap_return_common(rp, pc, p->p_pid, npc);

	return (0);
}