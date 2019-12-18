#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t rt; size_t rd; size_t sel; int rs; } ;
struct TYPE_6__ {int /*<<< orphan*/  sc; } ;
struct TYPE_7__ {int func; scalar_t__ co; } ;
union mips_instruction {TYPE_3__ c0r_format; TYPE_1__ mfmc0_format; TYPE_2__ co_format; } ;
typedef  size_t u32 ;
struct mips_coproc {size_t** reg; int /*<<< orphan*/ ** stat; } ;
struct TYPE_9__ {unsigned long pc; size_t* gprs; int aux_inuse; struct mips_coproc* cop0; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct kvm_run {int dummy; } ;
typedef  void* s32 ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;
struct TYPE_10__ {int fpu_id; } ;

/* Variables and functions */
 size_t CAUSEF_DC ; 
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int KVM_MIPS_AUX_FPU ; 
 int KVM_MIPS_AUX_MSA ; 
 size_t KVM_MIPS_GUEST_TLB_SIZE ; 
 int /*<<< orphan*/  KVM_TRACE_COP0 (size_t,size_t) ; 
 int /*<<< orphan*/  KVM_TRACE_DMFC0 ; 
 int /*<<< orphan*/  KVM_TRACE_DMTC0 ; 
 int /*<<< orphan*/  KVM_TRACE_MFC0 ; 
 int /*<<< orphan*/  KVM_TRACE_MTC0 ; 
 int MIPS_CONF3_ULRI ; 
 unsigned int MIPS_CONF5_FRE ; 
 unsigned int MIPS_CONF5_MSAEN ; 
 size_t MIPS_CP0_CAUSE ; 
 size_t MIPS_CP0_COMPARE ; 
 size_t MIPS_CP0_CONFIG ; 
 size_t MIPS_CP0_COUNT ; 
 size_t MIPS_CP0_ERRCTL ; 
 size_t MIPS_CP0_HWRENA ; 
 size_t MIPS_CP0_PRID ; 
 size_t MIPS_CP0_STATUS ; 
 size_t MIPS_CP0_TLB_HI ; 
 size_t MIPS_CP0_TLB_INDEX ; 
 int MIPS_FPIR_F64 ; 
 size_t MIPS_HWRENA_CC ; 
 size_t MIPS_HWRENA_CCRES ; 
 size_t MIPS_HWRENA_CPUNUM ; 
 size_t MIPS_HWRENA_SYNCISTEP ; 
 size_t MIPS_HWRENA_ULR ; 
 unsigned int ST0_CU1 ; 
 unsigned int ST0_FR ; 
 int /*<<< orphan*/  ST0_IE ; 
 unsigned int ST0_NMI ; 
 int /*<<< orphan*/  change_c0_config5 (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  change_c0_status (unsigned int,unsigned int) ; 
 TYPE_5__ current_cpu_data ; 
#define  dmfc_op 141 
#define  dmtc_op 140 
#define  eret_op 139 
#define  hypcall_op 138 
 int /*<<< orphan*/  kvm_change_c0_guest_cause (struct mips_coproc*,int,size_t) ; 
 int /*<<< orphan*/  kvm_change_c0_guest_ebase (struct mips_coproc*,int,size_t) ; 
 int /*<<< orphan*/  kvm_clear_c0_guest_status (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_debug (char*,size_t,...) ; 
 int /*<<< orphan*/  kvm_drop_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_err (char*,...) ; 
 int /*<<< orphan*/  kvm_lose_fpu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_change_entryhi (struct kvm_vcpu*,size_t) ; 
 unsigned int kvm_mips_config5_wrmask (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_count_disable_cause (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_count_enable_cause (struct kvm_vcpu*) ; 
 int kvm_mips_emul_eret (struct kvm_vcpu*) ; 
 int kvm_mips_emul_hypcall (struct kvm_vcpu*,union mips_instruction) ; 
 int kvm_mips_emul_tlbp (struct kvm_vcpu*) ; 
 int kvm_mips_emul_tlbr (struct kvm_vcpu*) ; 
 int kvm_mips_emul_tlbwi (struct kvm_vcpu*) ; 
 int kvm_mips_emul_tlbwr (struct kvm_vcpu*) ; 
 int kvm_mips_emul_wait (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_guest_has_fpu (TYPE_4__*) ; 
 int /*<<< orphan*/  kvm_mips_read_count (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_trans_mfc0 (union mips_instruction,size_t*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_trans_mtc0 (union mips_instruction,size_t*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mips_write_compare (struct kvm_vcpu*,size_t,int) ; 
 int /*<<< orphan*/  kvm_mips_write_count (struct kvm_vcpu*,size_t) ; 
 size_t kvm_read_c0_guest_cause (struct mips_coproc*) ; 
 int kvm_read_c0_guest_config3 (struct mips_coproc*) ; 
 unsigned int kvm_read_c0_guest_config5 (struct mips_coproc*) ; 
 void* kvm_read_c0_guest_status (struct mips_coproc*) ; 
 int /*<<< orphan*/  kvm_set_c0_guest_status (struct mips_coproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_config5 (struct mips_coproc*,unsigned int) ; 
 int /*<<< orphan*/  kvm_write_c0_guest_status (struct mips_coproc*,unsigned int) ; 
#define  mfc_op 137 
#define  mfmc0_op 136 
#define  mtc_op 135 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
#define  rfe_op 134 
#define  tlbp_op 133 
#define  tlbr_op 132 
#define  tlbwi_op 131 
#define  tlbwr_op 130 
 int /*<<< orphan*/  trace_kvm_hwr (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int update_pc (struct kvm_vcpu*,size_t) ; 
#define  wait_op 129 
#define  wrpgpr_op 128 

enum emulation_result kvm_mips_emulate_CP0(union mips_instruction inst,
					   u32 *opc, u32 cause,
					   struct kvm_run *run,
					   struct kvm_vcpu *vcpu)
{
	struct mips_coproc *cop0 = vcpu->arch.cop0;
	enum emulation_result er = EMULATE_DONE;
	u32 rt, rd, sel;
	unsigned long curr_pc;

	/*
	 * Update PC and hold onto current PC in case there is
	 * an error and we want to rollback the PC
	 */
	curr_pc = vcpu->arch.pc;
	er = update_pc(vcpu, cause);
	if (er == EMULATE_FAIL)
		return er;

	if (inst.co_format.co) {
		switch (inst.co_format.func) {
		case tlbr_op:	/*  Read indexed TLB entry  */
			er = kvm_mips_emul_tlbr(vcpu);
			break;
		case tlbwi_op:	/*  Write indexed  */
			er = kvm_mips_emul_tlbwi(vcpu);
			break;
		case tlbwr_op:	/*  Write random  */
			er = kvm_mips_emul_tlbwr(vcpu);
			break;
		case tlbp_op:	/* TLB Probe */
			er = kvm_mips_emul_tlbp(vcpu);
			break;
		case rfe_op:
			kvm_err("!!!COP0_RFE!!!\n");
			break;
		case eret_op:
			er = kvm_mips_emul_eret(vcpu);
			goto dont_update_pc;
		case wait_op:
			er = kvm_mips_emul_wait(vcpu);
			break;
		case hypcall_op:
			er = kvm_mips_emul_hypcall(vcpu, inst);
			break;
		}
	} else {
		rt = inst.c0r_format.rt;
		rd = inst.c0r_format.rd;
		sel = inst.c0r_format.sel;

		switch (inst.c0r_format.rs) {
		case mfc_op:
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
			cop0->stat[rd][sel]++;
#endif
			/* Get reg */
			if ((rd == MIPS_CP0_COUNT) && (sel == 0)) {
				vcpu->arch.gprs[rt] =
				    (s32)kvm_mips_read_count(vcpu);
			} else if ((rd == MIPS_CP0_ERRCTL) && (sel == 0)) {
				vcpu->arch.gprs[rt] = 0x0;
#ifdef CONFIG_KVM_MIPS_DYN_TRANS
				kvm_mips_trans_mfc0(inst, opc, vcpu);
#endif
			} else {
				vcpu->arch.gprs[rt] = (s32)cop0->reg[rd][sel];

#ifdef CONFIG_KVM_MIPS_DYN_TRANS
				kvm_mips_trans_mfc0(inst, opc, vcpu);
#endif
			}

			trace_kvm_hwr(vcpu, KVM_TRACE_MFC0,
				      KVM_TRACE_COP0(rd, sel),
				      vcpu->arch.gprs[rt]);
			break;

		case dmfc_op:
			vcpu->arch.gprs[rt] = cop0->reg[rd][sel];

			trace_kvm_hwr(vcpu, KVM_TRACE_DMFC0,
				      KVM_TRACE_COP0(rd, sel),
				      vcpu->arch.gprs[rt]);
			break;

		case mtc_op:
#ifdef CONFIG_KVM_MIPS_DEBUG_COP0_COUNTERS
			cop0->stat[rd][sel]++;
#endif
			trace_kvm_hwr(vcpu, KVM_TRACE_MTC0,
				      KVM_TRACE_COP0(rd, sel),
				      vcpu->arch.gprs[rt]);

			if ((rd == MIPS_CP0_TLB_INDEX)
			    && (vcpu->arch.gprs[rt] >=
				KVM_MIPS_GUEST_TLB_SIZE)) {
				kvm_err("Invalid TLB Index: %ld",
					vcpu->arch.gprs[rt]);
				er = EMULATE_FAIL;
				break;
			}
			if ((rd == MIPS_CP0_PRID) && (sel == 1)) {
				/*
				 * Preserve core number, and keep the exception
				 * base in guest KSeg0.
				 */
				kvm_change_c0_guest_ebase(cop0, 0x1ffff000,
							  vcpu->arch.gprs[rt]);
			} else if (rd == MIPS_CP0_TLB_HI && sel == 0) {
				kvm_mips_change_entryhi(vcpu,
							vcpu->arch.gprs[rt]);
			}
			/* Are we writing to COUNT */
			else if ((rd == MIPS_CP0_COUNT) && (sel == 0)) {
				kvm_mips_write_count(vcpu, vcpu->arch.gprs[rt]);
				goto done;
			} else if ((rd == MIPS_CP0_COMPARE) && (sel == 0)) {
				/* If we are writing to COMPARE */
				/* Clear pending timer interrupt, if any */
				kvm_mips_write_compare(vcpu,
						       vcpu->arch.gprs[rt],
						       true);
			} else if ((rd == MIPS_CP0_STATUS) && (sel == 0)) {
				unsigned int old_val, val, change;

				old_val = kvm_read_c0_guest_status(cop0);
				val = vcpu->arch.gprs[rt];
				change = val ^ old_val;

				/* Make sure that the NMI bit is never set */
				val &= ~ST0_NMI;

				/*
				 * Don't allow CU1 or FR to be set unless FPU
				 * capability enabled and exists in guest
				 * configuration.
				 */
				if (!kvm_mips_guest_has_fpu(&vcpu->arch))
					val &= ~(ST0_CU1 | ST0_FR);

				/*
				 * Also don't allow FR to be set if host doesn't
				 * support it.
				 */
				if (!(current_cpu_data.fpu_id & MIPS_FPIR_F64))
					val &= ~ST0_FR;


				/* Handle changes in FPU mode */
				preempt_disable();

				/*
				 * FPU and Vector register state is made
				 * UNPREDICTABLE by a change of FR, so don't
				 * even bother saving it.
				 */
				if (change & ST0_FR)
					kvm_drop_fpu(vcpu);

				/*
				 * If MSA state is already live, it is undefined
				 * how it interacts with FR=0 FPU state, and we
				 * don't want to hit reserved instruction
				 * exceptions trying to save the MSA state later
				 * when CU=1 && FR=1, so play it safe and save
				 * it first.
				 */
				if (change & ST0_CU1 && !(val & ST0_FR) &&
				    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA)
					kvm_lose_fpu(vcpu);

				/*
				 * Propagate CU1 (FPU enable) changes
				 * immediately if the FPU context is already
				 * loaded. When disabling we leave the context
				 * loaded so it can be quickly enabled again in
				 * the near future.
				 */
				if (change & ST0_CU1 &&
				    vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)
					change_c0_status(ST0_CU1, val);

				preempt_enable();

				kvm_write_c0_guest_status(cop0, val);

#ifdef CONFIG_KVM_MIPS_DYN_TRANS
				/*
				 * If FPU present, we need CU1/FR bits to take
				 * effect fairly soon.
				 */
				if (!kvm_mips_guest_has_fpu(&vcpu->arch))
					kvm_mips_trans_mtc0(inst, opc, vcpu);
#endif
			} else if ((rd == MIPS_CP0_CONFIG) && (sel == 5)) {
				unsigned int old_val, val, change, wrmask;

				old_val = kvm_read_c0_guest_config5(cop0);
				val = vcpu->arch.gprs[rt];

				/* Only a few bits are writable in Config5 */
				wrmask = kvm_mips_config5_wrmask(vcpu);
				change = (val ^ old_val) & wrmask;
				val = old_val ^ change;


				/* Handle changes in FPU/MSA modes */
				preempt_disable();

				/*
				 * Propagate FRE changes immediately if the FPU
				 * context is already loaded.
				 */
				if (change & MIPS_CONF5_FRE &&
				    vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU)
					change_c0_config5(MIPS_CONF5_FRE, val);

				/*
				 * Propagate MSAEn changes immediately if the
				 * MSA context is already loaded. When disabling
				 * we leave the context loaded so it can be
				 * quickly enabled again in the near future.
				 */
				if (change & MIPS_CONF5_MSAEN &&
				    vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA)
					change_c0_config5(MIPS_CONF5_MSAEN,
							  val);

				preempt_enable();

				kvm_write_c0_guest_config5(cop0, val);
			} else if ((rd == MIPS_CP0_CAUSE) && (sel == 0)) {
				u32 old_cause, new_cause;

				old_cause = kvm_read_c0_guest_cause(cop0);
				new_cause = vcpu->arch.gprs[rt];
				/* Update R/W bits */
				kvm_change_c0_guest_cause(cop0, 0x08800300,
							  new_cause);
				/* DC bit enabling/disabling timer? */
				if ((old_cause ^ new_cause) & CAUSEF_DC) {
					if (new_cause & CAUSEF_DC)
						kvm_mips_count_disable_cause(vcpu);
					else
						kvm_mips_count_enable_cause(vcpu);
				}
			} else if ((rd == MIPS_CP0_HWRENA) && (sel == 0)) {
				u32 mask = MIPS_HWRENA_CPUNUM |
					   MIPS_HWRENA_SYNCISTEP |
					   MIPS_HWRENA_CC |
					   MIPS_HWRENA_CCRES;

				if (kvm_read_c0_guest_config3(cop0) &
				    MIPS_CONF3_ULRI)
					mask |= MIPS_HWRENA_ULR;
				cop0->reg[rd][sel] = vcpu->arch.gprs[rt] & mask;
			} else {
				cop0->reg[rd][sel] = vcpu->arch.gprs[rt];
#ifdef CONFIG_KVM_MIPS_DYN_TRANS
				kvm_mips_trans_mtc0(inst, opc, vcpu);
#endif
			}
			break;

		case dmtc_op:
			kvm_err("!!!!!!![%#lx]dmtc_op: rt: %d, rd: %d, sel: %d!!!!!!\n",
				vcpu->arch.pc, rt, rd, sel);
			trace_kvm_hwr(vcpu, KVM_TRACE_DMTC0,
				      KVM_TRACE_COP0(rd, sel),
				      vcpu->arch.gprs[rt]);
			er = EMULATE_FAIL;
			break;

		case mfmc0_op:
#ifdef KVM_MIPS_DEBUG_COP0_COUNTERS
			cop0->stat[MIPS_CP0_STATUS][0]++;
#endif
			if (rt != 0)
				vcpu->arch.gprs[rt] =
				    kvm_read_c0_guest_status(cop0);
			/* EI */
			if (inst.mfmc0_format.sc) {
				kvm_debug("[%#lx] mfmc0_op: EI\n",
					  vcpu->arch.pc);
				kvm_set_c0_guest_status(cop0, ST0_IE);
			} else {
				kvm_debug("[%#lx] mfmc0_op: DI\n",
					  vcpu->arch.pc);
				kvm_clear_c0_guest_status(cop0, ST0_IE);
			}

			break;

		case wrpgpr_op:
			{
				u32 css = cop0->reg[MIPS_CP0_STATUS][2] & 0xf;
				u32 pss =
				    (cop0->reg[MIPS_CP0_STATUS][2] >> 6) & 0xf;
				/*
				 * We don't support any shadow register sets, so
				 * SRSCtl[PSS] == SRSCtl[CSS] = 0
				 */
				if (css || pss) {
					er = EMULATE_FAIL;
					break;
				}
				kvm_debug("WRPGPR[%d][%d] = %#lx\n", pss, rd,
					  vcpu->arch.gprs[rt]);
				vcpu->arch.gprs[rd] = vcpu->arch.gprs[rt];
			}
			break;
		default:
			kvm_err("[%#lx]MachEmulateCP0: unsupported COP0, copz: 0x%x\n",
				vcpu->arch.pc, inst.c0r_format.rs);
			er = EMULATE_FAIL;
			break;
		}
	}

done:
	/* Rollback PC only if emulation was unsuccessful */
	if (er == EMULATE_FAIL)
		vcpu->arch.pc = curr_pc;

dont_update_pc:
	/*
	 * This is for special instructions whose emulation
	 * updates the PC, so do not overwrite the PC under
	 * any circumstances
	 */

	return er;
}