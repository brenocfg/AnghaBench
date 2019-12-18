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
 int /*<<< orphan*/  die_if_kernel (char*,struct pt_regs*) ; 
 int /*<<< orphan*/  exception_enter () ; 

void do_paw(struct pt_regs *regs)
{
	exception_enter();
	die_if_kernel("TL0: Phys Watchpoint Exception", regs);
}