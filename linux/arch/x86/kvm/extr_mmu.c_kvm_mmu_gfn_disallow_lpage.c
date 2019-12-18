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
struct kvm_memory_slot {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  update_gfn_disallow_lpage_count (struct kvm_memory_slot*,int /*<<< orphan*/ ,int) ; 

void kvm_mmu_gfn_disallow_lpage(struct kvm_memory_slot *slot, gfn_t gfn)
{
	update_gfn_disallow_lpage_count(slot, gfn, 1);
}