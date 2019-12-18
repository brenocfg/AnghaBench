#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct TYPE_4__ {int /*<<< orphan*/  exit_instruction; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_1__ stat; } ;
struct TYPE_5__ {int ipa; int /*<<< orphan*/  ipb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int kvm_s390_handle_01 (struct kvm_vcpu*) ; 
 int kvm_s390_handle_aa (struct kvm_vcpu*) ; 
 int kvm_s390_handle_b2 (struct kvm_vcpu*) ; 
 int kvm_s390_handle_b9 (struct kvm_vcpu*) ; 
 int kvm_s390_handle_diag (struct kvm_vcpu*) ; 
 int kvm_s390_handle_e3 (struct kvm_vcpu*) ; 
 int kvm_s390_handle_e5 (struct kvm_vcpu*) ; 
 int kvm_s390_handle_eb (struct kvm_vcpu*) ; 
 int kvm_s390_handle_lctl (struct kvm_vcpu*) ; 
 int kvm_s390_handle_lpsw (struct kvm_vcpu*) ; 
 int kvm_s390_handle_sigp (struct kvm_vcpu*) ; 
 int kvm_s390_handle_stctl (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_s390_intercept_instruction (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_instruction(struct kvm_vcpu *vcpu)
{
	vcpu->stat.exit_instruction++;
	trace_kvm_s390_intercept_instruction(vcpu,
					     vcpu->arch.sie_block->ipa,
					     vcpu->arch.sie_block->ipb);

	switch (vcpu->arch.sie_block->ipa >> 8) {
	case 0x01:
		return kvm_s390_handle_01(vcpu);
	case 0x82:
		return kvm_s390_handle_lpsw(vcpu);
	case 0x83:
		return kvm_s390_handle_diag(vcpu);
	case 0xaa:
		return kvm_s390_handle_aa(vcpu);
	case 0xae:
		return kvm_s390_handle_sigp(vcpu);
	case 0xb2:
		return kvm_s390_handle_b2(vcpu);
	case 0xb6:
		return kvm_s390_handle_stctl(vcpu);
	case 0xb7:
		return kvm_s390_handle_lctl(vcpu);
	case 0xb9:
		return kvm_s390_handle_b9(vcpu);
	case 0xe3:
		return kvm_s390_handle_e3(vcpu);
	case 0xe5:
		return kvm_s390_handle_e5(vcpu);
	case 0xeb:
		return kvm_s390_handle_eb(vcpu);
	default:
		return -EOPNOTSUPP;
	}
}