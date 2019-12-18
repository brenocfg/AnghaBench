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
typedef  int /*<<< orphan*/ * Ctrl_C_Handler ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/ ** ctrlc_stack ; 
 size_t ctrlc_stack_len ; 

int/*BOOL*/
pop_ctrl_c_handler(
	Ctrl_C_Handler func
	)
{
	size_t size = ctrlc_stack_len;
	if (size) {
		--size;
		if (func == NULL || func == ctrlc_stack[size]) {
			ctrlc_stack_len = size;
			return TRUE;
		}
	}
	return FALSE;
}