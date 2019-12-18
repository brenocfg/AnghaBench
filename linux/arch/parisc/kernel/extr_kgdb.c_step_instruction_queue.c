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
struct pt_regs {int* iaoq; } ;

/* Variables and functions */

__attribute__((used)) static void step_instruction_queue(struct pt_regs *regs)
{
	regs->iaoq[0] = regs->iaoq[1];
	regs->iaoq[1] += 4;
}