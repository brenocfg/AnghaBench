#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct sys_reg_params {int regval; scalar_t__ is_32bit; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_ARM64_DEBUG_DIRTY ; 

__attribute__((used)) static void reg_to_dbg(struct kvm_vcpu *vcpu,
		       struct sys_reg_params *p,
		       u64 *dbg_reg)
{
	u64 val = p->regval;

	if (p->is_32bit) {
		val &= 0xffffffffUL;
		val |= ((*dbg_reg >> 32) << 32);
	}

	*dbg_reg = val;
	vcpu->arch.flags |= KVM_ARM64_DEBUG_DIRTY;
}