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

/* Variables and functions */
 int CW_Denormal ; 
 int /*<<< orphan*/  EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EX_Denormal ; 
 int FPU_Exception ; 
 int /*<<< orphan*/  SW_Denorm_Op ; 
 int TAG_Special ; 
 int control_word ; 
 int /*<<< orphan*/  partial_status ; 

int denormal_operand(void)
{
	if (control_word & CW_Denormal) {	/* The masked response */
		partial_status |= SW_Denorm_Op;
		return TAG_Special;
	} else {
		EXCEPTION(EX_Denormal);
		return TAG_Special | FPU_Exception;
	}
}