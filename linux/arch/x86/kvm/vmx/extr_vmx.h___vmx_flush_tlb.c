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
struct TYPE_4__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int /*<<< orphan*/  root_hpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALID_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  construct_eptp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ enable_ept ; 
 int /*<<< orphan*/  enable_vpid ; 
 int /*<<< orphan*/  ept_sync_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpid_sync_context (int) ; 

__attribute__((used)) static inline void __vmx_flush_tlb(struct kvm_vcpu *vcpu, int vpid,
				bool invalidate_gpa)
{
	if (enable_ept && (invalidate_gpa || !enable_vpid)) {
		if (!VALID_PAGE(vcpu->arch.mmu->root_hpa))
			return;
		ept_sync_context(construct_eptp(vcpu,
						vcpu->arch.mmu->root_hpa));
	} else {
		vpid_sync_context(vpid);
	}
}