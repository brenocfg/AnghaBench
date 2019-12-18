#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct pt_regs {TYPE_3__ psw; int /*<<< orphan*/ * gprs; } ;
struct TYPE_9__ {int /*<<< orphan*/  ui; } ;
typedef  TYPE_4__ freg_t ;
struct TYPE_6__ {TYPE_4__* fprs; scalar_t__ vxrs; } ;
struct TYPE_7__ {TYPE_1__ fpu; } ;
struct TYPE_10__ {TYPE_2__ thread; } ;

/* Variables and functions */
 scalar_t__ MACHINE_HAS_VX ; 
 int PERF_REG_S390_FP0 ; 
 int PERF_REG_S390_FP15 ; 
 int PERF_REG_S390_MASK ; 
 scalar_t__ PERF_REG_S390_MAX ; 
 int PERF_REG_S390_PC ; 
 int PERF_REG_S390_R0 ; 
 int PERF_REG_S390_R15 ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

u64 perf_reg_value(struct pt_regs *regs, int idx)
{
	freg_t fp;

	if (idx >= PERF_REG_S390_R0 && idx <= PERF_REG_S390_R15)
		return regs->gprs[idx];

	if (idx >= PERF_REG_S390_FP0 && idx <= PERF_REG_S390_FP15) {
		if (!user_mode(regs))
			return 0;

		idx -= PERF_REG_S390_FP0;
		fp = MACHINE_HAS_VX ? *(freg_t *)(current->thread.fpu.vxrs + idx)
				    : current->thread.fpu.fprs[idx];
		return fp.ui;
	}

	if (idx == PERF_REG_S390_MASK)
		return regs->psw.mask;
	if (idx == PERF_REG_S390_PC)
		return regs->psw.addr;

	WARN_ON_ONCE((u32)idx >= PERF_REG_S390_MAX);
	return 0;
}