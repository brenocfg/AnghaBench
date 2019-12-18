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
struct kvm_vcpu {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTSIDE_GUEST_MODE ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walk_shadow_page_lockless_end(struct kvm_vcpu *vcpu)
{
	/*
	 * Make sure the write to vcpu->mode is not reordered in front of
	 * reads to sptes.  If it does, kvm_mmu_commit_zap_page() can see us
	 * OUTSIDE_GUEST_MODE and proceed to free the shadow page table.
	 */
	smp_store_release(&vcpu->mode, OUTSIDE_GUEST_MODE);
	local_irq_enable();
}