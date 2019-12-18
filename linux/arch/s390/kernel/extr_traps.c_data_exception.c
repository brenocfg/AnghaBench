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
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int fpc; } ;
struct TYPE_5__ {TYPE_1__ fpu; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int FPC_DXC_MASK ; 
 int /*<<< orphan*/  ILL_ILLOPN ; 
 int /*<<< orphan*/  SIGILL ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  do_fp_trap (struct pt_regs*,int) ; 
 int /*<<< orphan*/  do_trap (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 

void data_exception(struct pt_regs *regs)
{
	save_fpu_regs();
	if (current->thread.fpu.fpc & FPC_DXC_MASK)
		do_fp_trap(regs, current->thread.fpu.fpc);
	else
		do_trap(regs, SIGILL, ILL_ILLOPN, "data exception");
}