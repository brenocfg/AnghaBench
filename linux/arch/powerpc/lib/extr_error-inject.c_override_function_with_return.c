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
struct pt_regs {int /*<<< orphan*/  link; int /*<<< orphan*/  nip; } ;

/* Variables and functions */

void override_function_with_return(struct pt_regs *regs)
{
	/*
	 * Emulate 'blr'. 'regs' represents the state on entry of a predefined
	 * function in the kernel/module, captured on a kprobe. We don't need
	 * to worry about 32-bit userspace on a 64-bit kernel.
	 */
	regs->nip = regs->link;
}