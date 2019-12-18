#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int sigh; } ;
typedef  TYPE_1__ FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_QNaN ; 
 int CW_Invalid ; 
 int /*<<< orphan*/  EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ EXP_OVER ; 
 int /*<<< orphan*/  EX_Invalid ; 
 int FPU_Exception ; 
 int TAG_Special ; 
 int control_word ; 
 scalar_t__ exponent (TYPE_1__*) ; 
 int /*<<< orphan*/  reg_copy (int /*<<< orphan*/ *,TYPE_1__*) ; 

int real_1op_NaN(FPU_REG *a)
{
	int signalling, isNaN;

	isNaN = (exponent(a) == EXP_OVER) && (a->sigh & 0x80000000);

	/* The default result for the case of two "equal" NaNs (signs may
	   differ) is chosen to reproduce 80486 behaviour */
	signalling = isNaN && !(a->sigh & 0x40000000);

	if (!signalling) {
		if (!isNaN) {	/* pseudo-NaN, or other unsupported? */
			if (control_word & CW_Invalid) {
				/* Masked response */
				reg_copy(&CONST_QNaN, a);
			}
			EXCEPTION(EX_Invalid);
			return (!(control_word & CW_Invalid) ? FPU_Exception :
				0) | TAG_Special;
		}
		return TAG_Special;
	}

	if (control_word & CW_Invalid) {
		/* The masked response */
		if (!(a->sigh & 0x80000000)) {	/* pseudo-NaN ? */
			reg_copy(&CONST_QNaN, a);
		}
		/* ensure a Quiet NaN */
		a->sigh |= 0x40000000;
	}

	EXCEPTION(EX_Invalid);

	return (!(control_word & CW_Invalid) ? FPU_Exception : 0) | TAG_Special;
}