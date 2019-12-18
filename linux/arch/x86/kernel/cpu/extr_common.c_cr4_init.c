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
struct TYPE_2__ {int /*<<< orphan*/  cr4; } ;

/* Variables and functions */
 unsigned long X86_CR4_PCIDE ; 
 int /*<<< orphan*/  X86_FEATURE_PCID ; 
 unsigned long __read_cr4 () ; 
 int /*<<< orphan*/  __write_cr4 (unsigned long) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_1__ cpu_tlbstate ; 
 unsigned long cr4_pinned_bits ; 
 int /*<<< orphan*/  cr_pinning ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 

void cr4_init(void)
{
	unsigned long cr4 = __read_cr4();

	if (boot_cpu_has(X86_FEATURE_PCID))
		cr4 |= X86_CR4_PCIDE;
	if (static_branch_likely(&cr_pinning))
		cr4 |= cr4_pinned_bits;

	__write_cr4(cr4);

	/* Initialize cr4 shadow for this CPU. */
	this_cpu_write(cpu_tlbstate.cr4, cr4);
}