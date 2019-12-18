#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t register_t ;
struct TYPE_6__ {TYPE_2__* pc_curpcb; TYPE_1__* pc_curthread; TYPE_1__* pc_idlethread; } ;
struct TYPE_5__ {uintptr_t pcb_sp; } ;
struct TYPE_4__ {TYPE_2__* td_pcb; } ;

/* Variables and functions */
 uintptr_t PSL_EE ; 
 int /*<<< orphan*/  mtmsr (uintptr_t) ; 
 TYPE_3__* pcpup ; 
 uintptr_t psl_kernset ; 

uintptr_t
cpudep_ap_bootstrap(void)
{
	register_t msr, sp;

	msr = psl_kernset & ~PSL_EE;
	mtmsr(msr);

	pcpup->pc_curthread = pcpup->pc_idlethread;
#ifdef __powerpc64__
	__asm __volatile("mr 13,%0" :: "r"(pcpup->pc_curthread));
#else
	__asm __volatile("mr 2,%0" :: "r"(pcpup->pc_curthread));
#endif
	pcpup->pc_curpcb = pcpup->pc_curthread->td_pcb;
	sp = pcpup->pc_curpcb->pcb_sp;

	return (sp);
}