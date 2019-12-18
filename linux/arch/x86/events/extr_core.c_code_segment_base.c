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
struct pt_regs {int flags; int cs; } ;

/* Variables and functions */
 int X86_VM_MASK ; 
 int __USER32_CS ; 
 int __USER_CS ; 
 unsigned long get_segment_base (int) ; 
 int /*<<< orphan*/  user_64bit_mode (struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static unsigned long code_segment_base(struct pt_regs *regs)
{
	/*
	 * For IA32 we look at the GDT/LDT segment base to convert the
	 * effective IP to a linear address.
	 */

#ifdef CONFIG_X86_32
	/*
	 * If we are in VM86 mode, add the segment offset to convert to a
	 * linear address.
	 */
	if (regs->flags & X86_VM_MASK)
		return 0x10 * regs->cs;

	if (user_mode(regs) && regs->cs != __USER_CS)
		return get_segment_base(regs->cs);
#else
	if (user_mode(regs) && !user_64bit_mode(regs) &&
	    regs->cs != __USER32_CS)
		return get_segment_base(regs->cs);
#endif
	return 0;
}