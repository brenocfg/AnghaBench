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
struct TYPE_4__ {int /*<<< orphan*/  simmediate; int /*<<< orphan*/  rt; int /*<<< orphan*/  rs; int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int /*<<< orphan*/  simmediate; } ;
union mips_instruction {TYPE_2__ i_format; TYPE_1__ spec3_format; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcond_op ; 
 scalar_t__ cpu_has_mips_r6 ; 
 int kvm_mips_trans_replace (struct kvm_vcpu*,int /*<<< orphan*/ *,union mips_instruction) ; 
 int /*<<< orphan*/  synci_op ; 

int kvm_mips_trans_cache_va(union mips_instruction inst, u32 *opc,
			    struct kvm_vcpu *vcpu)
{
	union mips_instruction synci_inst = { 0 };

	synci_inst.i_format.opcode = bcond_op;
	synci_inst.i_format.rs = inst.i_format.rs;
	synci_inst.i_format.rt = synci_op;
	if (cpu_has_mips_r6)
		synci_inst.i_format.simmediate = inst.spec3_format.simmediate;
	else
		synci_inst.i_format.simmediate = inst.i_format.simmediate;

	return kvm_mips_trans_replace(vcpu, opc, synci_inst);
}