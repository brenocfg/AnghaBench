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
struct TYPE_3__ {int ipb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int handle_lctlg (struct kvm_vcpu*) ; 
 int handle_ri (struct kvm_vcpu*) ; 
 int handle_stctg (struct kvm_vcpu*) ; 

int kvm_s390_handle_eb(struct kvm_vcpu *vcpu)
{
	switch (vcpu->arch.sie_block->ipb & 0x000000ff) {
	case 0x25:
		return handle_stctg(vcpu);
	case 0x2f:
		return handle_lctlg(vcpu);
	case 0x60:
	case 0x61:
	case 0x62:
		return handle_ri(vcpu);
	default:
		return -EOPNOTSUPP;
	}
}