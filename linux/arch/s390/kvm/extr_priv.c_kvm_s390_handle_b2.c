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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int ipa; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int handle_io_inst (struct kvm_vcpu*) ; 
 int handle_ipte_interlock (struct kvm_vcpu*) ; 
 int handle_iske (struct kvm_vcpu*) ; 
 int handle_lpswe (struct kvm_vcpu*) ; 
 int handle_pqap (struct kvm_vcpu*) ; 
 int handle_rrbe (struct kvm_vcpu*) ; 
 int handle_set_clock (struct kvm_vcpu*) ; 
 int handle_set_prefix (struct kvm_vcpu*) ; 
 int handle_sske (struct kvm_vcpu*) ; 
 int handle_stfl (struct kvm_vcpu*) ; 
 int handle_sthyi (struct kvm_vcpu*) ; 
 int handle_stidp (struct kvm_vcpu*) ; 
 int handle_store_cpu_address (struct kvm_vcpu*) ; 
 int handle_store_prefix (struct kvm_vcpu*) ; 
 int handle_stsi (struct kvm_vcpu*) ; 
 int handle_test_block (struct kvm_vcpu*) ; 
 int kvm_s390_handle_vsie (struct kvm_vcpu*) ; 

int kvm_s390_handle_b2(struct kvm_vcpu *vcpu)
{
	switch (vcpu->arch.sie_block->ipa & 0x00ff) {
	case 0x02:
		return handle_stidp(vcpu);
	case 0x04:
		return handle_set_clock(vcpu);
	case 0x10:
		return handle_set_prefix(vcpu);
	case 0x11:
		return handle_store_prefix(vcpu);
	case 0x12:
		return handle_store_cpu_address(vcpu);
	case 0x14:
		return kvm_s390_handle_vsie(vcpu);
	case 0x21:
	case 0x50:
		return handle_ipte_interlock(vcpu);
	case 0x29:
		return handle_iske(vcpu);
	case 0x2a:
		return handle_rrbe(vcpu);
	case 0x2b:
		return handle_sske(vcpu);
	case 0x2c:
		return handle_test_block(vcpu);
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x5f:
	case 0x74:
	case 0x76:
		return handle_io_inst(vcpu);
	case 0x56:
		return handle_sthyi(vcpu);
	case 0x7d:
		return handle_stsi(vcpu);
	case 0xaf:
		return handle_pqap(vcpu);
	case 0xb1:
		return handle_stfl(vcpu);
	case 0xb2:
		return handle_lpswe(vcpu);
	default:
		return -EOPNOTSUPP;
	}
}