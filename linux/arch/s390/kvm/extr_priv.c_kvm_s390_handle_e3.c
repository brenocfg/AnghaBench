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
 int handle_gs (struct kvm_vcpu*) ; 

int kvm_s390_handle_e3(struct kvm_vcpu *vcpu)
{
	int code = vcpu->arch.sie_block->ipb & 0xff;

	if (code == 0x49 || code == 0x4d)
		return handle_gs(vcpu);
	else
		return -EOPNOTSUPP;
}