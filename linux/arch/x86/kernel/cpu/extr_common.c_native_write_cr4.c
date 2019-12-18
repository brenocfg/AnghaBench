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

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (unsigned long,char*,unsigned long) ; 
 unsigned long cr4_pinned_bits ; 
 int /*<<< orphan*/  cr_pinning ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void native_write_cr4(unsigned long val)
{
	unsigned long bits_missing = 0;

set_register:
	asm volatile("mov %0,%%cr4": "+r" (val), "+m" (cr4_pinned_bits));

	if (static_branch_likely(&cr_pinning)) {
		if (unlikely((val & cr4_pinned_bits) != cr4_pinned_bits)) {
			bits_missing = ~val & cr4_pinned_bits;
			val |= bits_missing;
			goto set_register;
		}
		/* Warn after we've set the missing bits. */
		WARN_ONCE(bits_missing, "CR4 bits went missing: %lx!?\n",
			  bits_missing);
	}
}