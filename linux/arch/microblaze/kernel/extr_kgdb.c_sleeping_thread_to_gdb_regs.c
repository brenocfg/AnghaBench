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
struct TYPE_3__ {scalar_t__ regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pvr_s {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_4__ {unsigned long* pvr; } ;

/* Variables and functions */
 unsigned int GDB_PVR ; 
 TYPE_2__ pvr ; 

void sleeping_thread_to_gdb_regs(unsigned long *gdb_regs, struct task_struct *p)
{
	unsigned int i;
	unsigned long *pt_regb = (unsigned long *)(p->thread.regs);

	/* registers r0 - r31, pc, msr, ear, esr, fsr + do not save pt_mode */
	for (i = 0; i < (sizeof(struct pt_regs) / 4) - 1; i++)
		gdb_regs[i] = pt_regb[i];

	/* pvr part  - we have 11 pvr regs */
	for (i = 0; i < sizeof(struct pvr_s)/4; i++)
		gdb_regs[GDB_PVR + i] = pvr.pvr[i];
}