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
struct TYPE_3__ {int root_hpa; int /*<<< orphan*/  (* set_cr3 ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 scalar_t__ VALID_PAGE (int) ; 
 int kvm_get_active_pcid (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

__attribute__((used)) static inline void kvm_mmu_load_cr3(struct kvm_vcpu *vcpu)
{
	if (VALID_PAGE(vcpu->arch.mmu->root_hpa))
		vcpu->arch.mmu->set_cr3(vcpu, vcpu->arch.mmu->root_hpa |
					      kvm_get_active_pcid(vcpu));
}