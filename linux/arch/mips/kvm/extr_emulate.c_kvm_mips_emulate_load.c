#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int rt; int opcode; } ;
union mips_instruction {int /*<<< orphan*/  word; TYPE_1__ i_format; } ;
typedef  int u32 ;
struct TYPE_6__ {unsigned long pc; unsigned long io_pc; int io_gpr; int /*<<< orphan*/  host_cp0_badvaddr; } ;
struct kvm_vcpu {int mmio_needed; scalar_t__ mmio_is_write; TYPE_2__ arch; } ;
struct TYPE_7__ {scalar_t__ phys_addr; int len; scalar_t__ is_write; } ;
struct kvm_run {TYPE_3__ mmio; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_8__ {scalar_t__ (* gva_to_gpa ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EMULATE_DO_MMIO ; 
 int EMULATE_FAIL ; 
 scalar_t__ KVM_INVALID_ADDR ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* kvm_mips_callbacks ; 
#define  lb_op 134 
#define  lbu_op 133 
#define  ld_op 132 
#define  lh_op 131 
#define  lhu_op 130 
#define  lw_op 129 
#define  lwu_op 128 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int update_pc (struct kvm_vcpu*,int) ; 

enum emulation_result kvm_mips_emulate_load(union mips_instruction inst,
					    u32 cause, struct kvm_run *run,
					    struct kvm_vcpu *vcpu)
{
	enum emulation_result er;
	unsigned long curr_pc;
	u32 op, rt;

	rt = inst.i_format.rt;
	op = inst.i_format.opcode;

	/*
	 * Find the resume PC now while we have safe and easy access to the
	 * prior branch instruction, and save it for
	 * kvm_mips_complete_mmio_load() to restore later.
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	if (er == EMULATE_FAIL)
		return er;
	vcpu->arch.io_pc = vcpu->arch.pc;
	vcpu->arch.pc = curr_pc;

	vcpu->arch.io_gpr = rt;

	run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
						vcpu->arch.host_cp0_badvaddr);
	if (run->mmio.phys_addr == KVM_INVALID_ADDR)
		return EMULATE_FAIL;

	vcpu->mmio_needed = 2;	/* signed */
	switch (op) {
#if defined(CONFIG_64BIT) && defined(CONFIG_KVM_MIPS_VZ)
	case ld_op:
		run->mmio.len = 8;
		break;

	case lwu_op:
		vcpu->mmio_needed = 1;	/* unsigned */
		/* fall through */
#endif
	case lw_op:
		run->mmio.len = 4;
		break;

	case lhu_op:
		vcpu->mmio_needed = 1;	/* unsigned */
		/* fall through */
	case lh_op:
		run->mmio.len = 2;
		break;

	case lbu_op:
		vcpu->mmio_needed = 1;	/* unsigned */
		/* fall through */
	case lb_op:
		run->mmio.len = 1;
		break;

	default:
		kvm_err("Load not yet supported (inst=0x%08x)\n",
			inst.word);
		vcpu->mmio_needed = 0;
		return EMULATE_FAIL;
	}

	run->mmio.is_write = 0;
	vcpu->mmio_is_write = 0;
	return EMULATE_DO_MMIO;
}