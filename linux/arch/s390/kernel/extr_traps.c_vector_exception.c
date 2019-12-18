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
 int FPE_FLTDIV ; 
 int FPE_FLTINV ; 
 int FPE_FLTOVF ; 
 int FPE_FLTRES ; 
 int FPE_FLTUND ; 
 int ILL_ILLOPN ; 
 int /*<<< orphan*/  MACHINE_HAS_VX ; 
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGILL ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  do_trap (struct pt_regs*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 

void vector_exception(struct pt_regs *regs)
{
	int si_code, vic;

	if (!MACHINE_HAS_VX) {
		do_trap(regs, SIGILL, ILL_ILLOPN, "illegal operation");
		return;
	}

	/* get vector interrupt code from fpc */
	save_fpu_regs();
	vic = (current->thread.fpu.fpc & 0xf00) >> 8;
	switch (vic) {
	case 1: /* invalid vector operation */
		si_code = FPE_FLTINV;
		break;
	case 2: /* division by zero */
		si_code = FPE_FLTDIV;
		break;
	case 3: /* overflow */
		si_code = FPE_FLTOVF;
		break;
	case 4: /* underflow */
		si_code = FPE_FLTUND;
		break;
	case 5:	/* inexact */
		si_code = FPE_FLTRES;
		break;
	default: /* unknown cause */
		si_code = 0;
	}
	do_trap(regs, SIGFPE, si_code, "vector exception");
}