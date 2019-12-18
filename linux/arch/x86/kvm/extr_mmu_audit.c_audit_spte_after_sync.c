#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_mmu_page {scalar_t__ unsync; } ;
struct TYPE_3__ {scalar_t__ audit_point; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ AUDIT_POST_SYNC ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_printk (TYPE_2__*,char*,struct kvm_mmu_page*) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_spte_after_sync(struct kvm_vcpu *vcpu, u64 *sptep, int level)
{
	struct kvm_mmu_page *sp = page_header(__pa(sptep));

	if (vcpu->kvm->arch.audit_point == AUDIT_POST_SYNC && sp->unsync)
		audit_printk(vcpu->kvm, "meet unsync sp(%p) after sync "
			     "root.\n", sp);
}