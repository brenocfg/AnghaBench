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
struct pt_regs {unsigned long ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  just_return_func ; 

void override_function_with_return(struct pt_regs *regs)
{
	regs->ip = (unsigned long)&just_return_func;
}