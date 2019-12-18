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
struct TYPE_3__ {unsigned long* regs; int /*<<< orphan*/  regs_avail; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  enum kvm_reg { ____Placeholder_kvm_reg } kvm_reg ;
struct TYPE_4__ {int /*<<< orphan*/  (* cache_reg ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static inline unsigned long kvm_register_read(struct kvm_vcpu *vcpu,
					      enum kvm_reg reg)
{
	if (!test_bit(reg, (unsigned long *)&vcpu->arch.regs_avail))
		kvm_x86_ops->cache_reg(vcpu, reg);

	return vcpu->arch.regs[reg];
}