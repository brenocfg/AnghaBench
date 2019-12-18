#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {unsigned long address; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_BUG_F00F ; 
 scalar_t__ boot_cpu_has_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_invalid_op (struct pt_regs*,int /*<<< orphan*/ ) ; 
 TYPE_1__ idt_descr ; 

__attribute__((used)) static int is_f00f_bug(struct pt_regs *regs, unsigned long address)
{
#ifdef CONFIG_X86_F00F_BUG
	unsigned long nr;

	/*
	 * Pentium F0 0F C7 C8 bug workaround:
	 */
	if (boot_cpu_has_bug(X86_BUG_F00F)) {
		nr = (address - idt_descr.address) >> 3;

		if (nr == 6) {
			do_invalid_op(regs, 0);
			return 1;
		}
	}
#endif
	return 0;
}