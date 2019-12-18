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
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

__attribute__((used)) static inline int decode_access_size(struct pt_regs *regs, unsigned int insn)
{
	unsigned int tmp;

	tmp = ((insn >> 19) & 0xf);
	if (tmp == 11 || tmp == 14) /* ldx/stx */
		return 8;
	tmp &= 3;
	if (!tmp)
		return 4;
	else if (tmp == 3)
		return 16;	/* ldd/std - Although it is actually 8 */
	else if (tmp == 2)
		return 2;
	else {
		printk("Impossible unaligned trap. insn=%08x\n", insn);
		die_if_kernel("Byte sized unaligned access?!?!", regs);

		/* GCC should never warn that control reaches the end
		 * of this function without returning a value because
		 * die_if_kernel() is marked with attribute 'noreturn'.
		 * Alas, some versions do...
		 */

		return 0;
	}
}