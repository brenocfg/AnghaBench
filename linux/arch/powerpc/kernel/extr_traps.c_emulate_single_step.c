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
 int /*<<< orphan*/  single_step_exception (struct pt_regs*) ; 
 scalar_t__ single_stepping (struct pt_regs*) ; 

__attribute__((used)) static void emulate_single_step(struct pt_regs *regs)
{
	if (single_stepping(regs))
		single_step_exception(regs);
}