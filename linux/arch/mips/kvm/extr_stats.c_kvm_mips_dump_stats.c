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
struct TYPE_3__ {TYPE_2__* cop0; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_4__ {scalar_t__** stat; } ;

/* Variables and functions */
 int N_MIPS_COPROC_REGS ; 
 int N_MIPS_COPROC_SEL ; 
 int /*<<< orphan*/ * kvm_cop0_str ; 
 int /*<<< orphan*/  kvm_info (char*,int /*<<< orphan*/ ,...) ; 

void kvm_mips_dump_stats(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
	int i, j;

	kvm_info("\nKVM VCPU[%d] COP0 Access Profile:\n", vcpu->vcpu_id);
	for (i = 0; i < N_MIPS_COPROC_REGS; i++) {
		for (j = 0; j < N_MIPS_COPROC_SEL; j++) {
			if (vcpu->arch.cop0->stat[i][j])
				kvm_info("%s[%d]: %lu\n", kvm_cop0_str[i], j,
					 vcpu->arch.cop0->stat[i][j]);
		}
	}
#endif
}