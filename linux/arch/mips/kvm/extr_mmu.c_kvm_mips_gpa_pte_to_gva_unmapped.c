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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_wrprotect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pte_t kvm_mips_gpa_pte_to_gva_unmapped(pte_t pte)
{
	/*
	 * Don't leak writeable but clean entries from GPA page tables. We don't
	 * want the normal Linux tlbmod handler to handle dirtying when KVM
	 * accesses guest memory.
	 */
	if (!pte_dirty(pte))
		pte = pte_wrprotect(pte);

	return pte;
}