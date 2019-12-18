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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  instruction_pointer_set (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procedure_link_pointer (struct pt_regs*) ; 

void override_function_with_return(struct pt_regs *regs)
{
	/*
	 * 'regs' represents the state on entry of a predefined function in
	 * the kernel/module and which is captured on a kprobe.
	 *
	 * When kprobe returns back from exception it will override the end
	 * of probed function and directly return to the predefined
	 * function's caller.
	 */
	instruction_pointer_set(regs, procedure_link_pointer(regs));
}