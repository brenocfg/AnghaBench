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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_3__ {int prefix; } ;

/* Variables and functions */
 int GUEST_PREFIX_SHIFT ; 
 int /*<<< orphan*/  KVM_REQ_MMU_RELOAD ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 

__attribute__((used)) static inline void kvm_s390_set_prefix(struct kvm_vcpu *vcpu, u32 prefix)
{
	VCPU_EVENT(vcpu, 3, "set prefix of cpu %03u to 0x%x", vcpu->vcpu_id,
		   prefix);
	vcpu->arch.sie_block->prefix = prefix >> GUEST_PREFIX_SHIFT;
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	kvm_make_request(KVM_REQ_MMU_RELOAD, vcpu);
}