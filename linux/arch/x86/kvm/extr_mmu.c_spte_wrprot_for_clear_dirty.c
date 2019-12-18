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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PT_WRITABLE_SHIFT ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_ad_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spte_to_pfn (int /*<<< orphan*/ ) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static bool spte_wrprot_for_clear_dirty(u64 *sptep)
{
	bool was_writable = test_and_clear_bit(PT_WRITABLE_SHIFT,
					       (unsigned long *)sptep);
	if (was_writable && !spte_ad_enabled(*sptep))
		kvm_set_pfn_dirty(spte_to_pfn(*sptep));

	return was_writable;
}