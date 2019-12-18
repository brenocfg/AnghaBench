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
 int /*<<< orphan*/  CONST_QNaN ; 
 int CW_Invalid ; 
 int /*<<< orphan*/  EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EX_StackUnder ; 
 int /*<<< orphan*/  FPU_copy_to_regi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TAG_Special ; 
 int control_word ; 

void FPU_stack_underflow_i(int i)
{

	if (control_word & CW_Invalid) {
		/* The masked response */
		FPU_copy_to_regi(&CONST_QNaN, TAG_Special, i);
	}

	EXCEPTION(EX_StackUnder);

	return;

}