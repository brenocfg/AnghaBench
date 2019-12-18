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
struct kvm_vcpu {int /*<<< orphan*/  arch; } ;
struct TYPE_4__ {int fpu_id; } ;
struct TYPE_3__ {scalar_t__ (* num_regs ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int MIPS_FPIR_F64 ; 
 TYPE_2__ boot_cpu_data ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_mips_get_one_regs ; 
 int /*<<< orphan*/  kvm_mips_get_one_regs_fpu ; 
 int /*<<< orphan*/  kvm_mips_get_one_regs_msa ; 
 scalar_t__ kvm_mips_guest_can_have_fpu (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_mips_guest_can_have_msa (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static unsigned long kvm_mips_num_regs(struct kvm_vcpu *vcpu)
{
	unsigned long ret;

	ret = ARRAY_SIZE(kvm_mips_get_one_regs);
	if (kvm_mips_guest_can_have_fpu(&vcpu->arch)) {
		ret += ARRAY_SIZE(kvm_mips_get_one_regs_fpu) + 48;
		/* odd doubles */
		if (boot_cpu_data.fpu_id & MIPS_FPIR_F64)
			ret += 16;
	}
	if (kvm_mips_guest_can_have_msa(&vcpu->arch))
		ret += ARRAY_SIZE(kvm_mips_get_one_regs_msa) + 32;
	ret += kvm_mips_callbacks->num_regs(vcpu);

	return ret;
}