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
struct TYPE_5__ {size_t rt; int opcode; } ;
union mips_instruction {int /*<<< orphan*/  word; TYPE_1__ i_format; } ;
typedef  size_t u8 ;
typedef  size_t u64 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct TYPE_7__ {unsigned long pc; size_t* gprs; int /*<<< orphan*/  host_cp0_badvaddr; } ;
struct kvm_vcpu {int mmio_needed; int mmio_is_write; TYPE_3__ arch; } ;
struct TYPE_6__ {scalar_t__ phys_addr; int len; int is_write; void* data; } ;
struct kvm_run {TYPE_2__ mmio; } ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_8__ {scalar_t__ (* gva_to_gpa ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EMULATE_DO_MMIO ; 
 int EMULATE_FAIL ; 
 scalar_t__ KVM_INVALID_ADDR ; 
 int /*<<< orphan*/  kvm_debug (char*,unsigned long,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* kvm_mips_callbacks ; 
#define  sb_op 131 
#define  sd_op 130 
#define  sh_op 129 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
#define  sw_op 128 
 int update_pc (struct kvm_vcpu*,size_t) ; 

enum emulation_result kvm_mips_emulate_store(union mips_instruction inst,
					     u32 cause,
					     struct kvm_run *run,
					     struct kvm_vcpu *vcpu)
{
	enum emulation_result er;
	u32 rt;
	void *data = run->mmio.data;
	unsigned long curr_pc;

	/*
	 * Update PC and hold onto current PC in case there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	if (er == EMULATE_FAIL)
		return er;

	rt = inst.i_format.rt;

	run->mmio.phys_addr = kvm_mips_callbacks->gva_to_gpa(
						vcpu->arch.host_cp0_badvaddr);
	if (run->mmio.phys_addr == KVM_INVALID_ADDR)
		goto out_fail;

	switch (inst.i_format.opcode) {
#if defined(CONFIG_64BIT) && defined(CONFIG_KVM_MIPS_VZ)
	case sd_op:
		run->mmio.len = 8;
		*(u64 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SD: eaddr: %#lx, gpr: %#lx, data: %#llx\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u64 *)data);
		break;
#endif

	case sw_op:
		run->mmio.len = 4;
		*(u32 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SW: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u32 *)data);
		break;

	case sh_op:
		run->mmio.len = 2;
		*(u16 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SH: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u16 *)data);
		break;

	case sb_op:
		run->mmio.len = 1;
		*(u8 *)data = vcpu->arch.gprs[rt];

		kvm_debug("[%#lx] OP_SB: eaddr: %#lx, gpr: %#lx, data: %#x\n",
			  vcpu->arch.pc, vcpu->arch.host_cp0_badvaddr,
			  vcpu->arch.gprs[rt], *(u8 *)data);
		break;

	default:
		kvm_err("Store not yet supported (inst=0x%08x)\n",
			inst.word);
		goto out_fail;
	}

	run->mmio.is_write = 1;
	vcpu->mmio_needed = 1;
	vcpu->mmio_is_write = 1;
	return EMULATE_DO_MMIO;

out_fail:
	/* Rollback PC if emulation was unsuccessful */
	vcpu->arch.pc = curr_pc;
	return EMULATE_FAIL;
}