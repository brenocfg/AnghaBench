#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_INF ; 
 int CW_Overflow ; 
 int /*<<< orphan*/  EXCEPTION (int) ; 
 int EX_Overflow ; 
 int EX_Precision ; 
 int SW_C1 ; 
 int TAG_Special ; 
 int TAG_Valid ; 
 int /*<<< orphan*/  addexponent (int /*<<< orphan*/ *,int) ; 
 int control_word ; 
 int /*<<< orphan*/  reg_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int arith_overflow(FPU_REG *dest)
{
	int tag = TAG_Valid;

	if (control_word & CW_Overflow) {
		/* The masked response */
/* ###### The response here depends upon the rounding mode */
		reg_copy(&CONST_INF, dest);
		tag = TAG_Special;
	} else {
		/* Subtract the magic number from the exponent */
		addexponent(dest, (-3 * (1 << 13)));
	}

	EXCEPTION(EX_Overflow);
	if (control_word & CW_Overflow) {
		/* The overflow exception is masked. */
		/* By definition, precision is lost.
		   The roundup bit (C1) is also set because we have
		   "rounded" upwards to Infinity. */
		EXCEPTION(EX_Precision | SW_C1);
		return tag;
	}

	return tag;

}