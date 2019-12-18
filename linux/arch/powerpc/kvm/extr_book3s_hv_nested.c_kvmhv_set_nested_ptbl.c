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
struct kvm_nested_guest {int /*<<< orphan*/  process_table; int /*<<< orphan*/  shadow_lpid; int /*<<< orphan*/  shadow_pgtable; } ;

/* Variables and functions */
 unsigned long PATB_HR ; 
 unsigned long RADIX_PGD_INDEX_SIZE ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmhv_set_ptbl_entry (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long radix__get_tree_size () ; 

__attribute__((used)) static void kvmhv_set_nested_ptbl(struct kvm_nested_guest *gp)
{
	unsigned long dw0;

	dw0 = PATB_HR | radix__get_tree_size() |
		__pa(gp->shadow_pgtable) | RADIX_PGD_INDEX_SIZE;
	kvmhv_set_ptbl_entry(gp->shadow_lpid, dw0, gp->process_table);
}