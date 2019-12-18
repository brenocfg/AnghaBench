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
typedef  scalar_t__ Ctrl_C_Handler ;

/* Variables and functions */
 size_t CTRLC_STACK_MAX ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__* ctrlc_stack ; 
 size_t ctrlc_stack_len ; 

int/*BOOL*/
push_ctrl_c_handler(
	Ctrl_C_Handler func
	)
{
	size_t size = ctrlc_stack_len;
	if (func && (size < CTRLC_STACK_MAX)) {
		ctrlc_stack[size] = func;
		ctrlc_stack_len = size + 1;
		return TRUE;
	}
	return FALSE;	
}