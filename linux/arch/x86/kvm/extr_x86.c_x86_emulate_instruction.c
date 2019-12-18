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
struct TYPE_8__ {int vector; unsigned long address; } ;
struct x86_emulate_ctxt {int have_exception; int perm_ok; int ud; int eflags; scalar_t__ tf; int /*<<< orphan*/  eip; TYPE_3__ exception; scalar_t__ interruptibility; int /*<<< orphan*/  _eip; } ;
struct TYPE_6__ {scalar_t__ count; int /*<<< orphan*/  in; } ;
struct TYPE_9__ {int write_fault_to_shadow_pgtable; int l1tf_flush_l1d; int emulate_regs_need_sync_from_vcpu; int emulate_regs_need_sync_to_vcpu; int /*<<< orphan*/  complete_userspace_io; TYPE_1__ pio; struct x86_emulate_ctxt emulate_ctxt; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmio_exits; int /*<<< orphan*/  insn_emulation; } ;
struct kvm_vcpu {TYPE_4__ arch; int /*<<< orphan*/  mmio_is_write; TYPE_2__ stat; scalar_t__ mmio_needed; } ;
struct TYPE_10__ {unsigned long (* get_rflags ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int EMULATION_FAILED ; 
 int EMULATION_INTERCEPTED ; 
 int EMULATION_OK ; 
 int EMULATION_RESTART ; 
 int EMULTYPE_NO_DECODE ; 
 int EMULTYPE_SKIP ; 
 int EMULTYPE_TRAP_UD ; 
 int EMULTYPE_TRAP_UD_FORCED ; 
 int EMULTYPE_VMWARE_GP ; 
 scalar_t__ EXCPT_TRAP ; 
 int /*<<< orphan*/  GP_VECTOR ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int UD_VECTOR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned long X86_EFLAGS_IF ; 
 int X86_EFLAGS_RF ; 
 int /*<<< orphan*/  __kvm_set_rflags (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  complete_emulated_mmio ; 
 int /*<<< orphan*/  complete_emulated_pio ; 
 int /*<<< orphan*/  emulator_invalidate_register_cache (struct x86_emulate_ctxt*) ; 
 scalar_t__ exception_type (int) ; 
 int handle_emulation_failure (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  init_emulate_ctxt (struct kvm_vcpu*) ; 
 scalar_t__ inject_emulated_exception (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_vmware_backdoor_opcode (struct x86_emulate_ctxt*) ; 
 int /*<<< orphan*/  kvm_clear_exception_queue (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_queue_exception (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_queue_exception_e (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_rflags (struct kvm_vcpu*,int) ; 
 scalar_t__ kvm_vcpu_check_breakpoint (struct kvm_vcpu*,int*) ; 
 int kvm_vcpu_do_singlestep (struct kvm_vcpu*) ; 
 TYPE_5__* kvm_x86_ops ; 
 scalar_t__ reexecute_instruction (struct kvm_vcpu*,unsigned long,int,int) ; 
 scalar_t__ retry_instruction (struct x86_emulate_ctxt*,unsigned long,int) ; 
 unsigned long stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  toggle_interruptibility (struct kvm_vcpu*,scalar_t__) ; 
 int /*<<< orphan*/  trace_kvm_emulate_insn_start (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (unsigned long) ; 
 int x86_decode_insn (struct x86_emulate_ctxt*,void*,int) ; 
 int x86_emulate_insn (struct x86_emulate_ctxt*) ; 

int x86_emulate_instruction(struct kvm_vcpu *vcpu,
			    unsigned long cr2,
			    int emulation_type,
			    void *insn,
			    int insn_len)
{
	int r;
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;
	bool writeback = true;
	bool write_fault_to_spt = vcpu->arch.write_fault_to_shadow_pgtable;

	vcpu->arch.l1tf_flush_l1d = true;

	/*
	 * Clear write_fault_to_shadow_pgtable here to ensure it is
	 * never reused.
	 */
	vcpu->arch.write_fault_to_shadow_pgtable = false;
	kvm_clear_exception_queue(vcpu);

	if (!(emulation_type & EMULTYPE_NO_DECODE)) {
		init_emulate_ctxt(vcpu);

		/*
		 * We will reenter on the same instruction since
		 * we do not set complete_userspace_io.  This does not
		 * handle watchpoints yet, those would be handled in
		 * the emulate_ops.
		 */
		if (!(emulation_type & EMULTYPE_SKIP) &&
		    kvm_vcpu_check_breakpoint(vcpu, &r))
			return r;

		ctxt->interruptibility = 0;
		ctxt->have_exception = false;
		ctxt->exception.vector = -1;
		ctxt->perm_ok = false;

		ctxt->ud = emulation_type & EMULTYPE_TRAP_UD;

		r = x86_decode_insn(ctxt, insn, insn_len);

		trace_kvm_emulate_insn_start(vcpu);
		++vcpu->stat.insn_emulation;
		if (r != EMULATION_OK)  {
			if ((emulation_type & EMULTYPE_TRAP_UD) ||
			    (emulation_type & EMULTYPE_TRAP_UD_FORCED)) {
				kvm_queue_exception(vcpu, UD_VECTOR);
				return 1;
			}
			if (reexecute_instruction(vcpu, cr2, write_fault_to_spt,
						emulation_type))
				return 1;
			if (ctxt->have_exception) {
				/*
				 * #UD should result in just EMULATION_FAILED, and trap-like
				 * exception should not be encountered during decode.
				 */
				WARN_ON_ONCE(ctxt->exception.vector == UD_VECTOR ||
					     exception_type(ctxt->exception.vector) == EXCPT_TRAP);
				inject_emulated_exception(vcpu);
				return 1;
			}
			return handle_emulation_failure(vcpu, emulation_type);
		}
	}

	if ((emulation_type & EMULTYPE_VMWARE_GP) &&
	    !is_vmware_backdoor_opcode(ctxt)) {
		kvm_queue_exception_e(vcpu, GP_VECTOR, 0);
		return 1;
	}

	/*
	 * Note, EMULTYPE_SKIP is intended for use *only* by vendor callbacks
	 * for kvm_skip_emulated_instruction().  The caller is responsible for
	 * updating interruptibility state and injecting single-step #DBs.
	 */
	if (emulation_type & EMULTYPE_SKIP) {
		kvm_rip_write(vcpu, ctxt->_eip);
		if (ctxt->eflags & X86_EFLAGS_RF)
			kvm_set_rflags(vcpu, ctxt->eflags & ~X86_EFLAGS_RF);
		return 1;
	}

	if (retry_instruction(ctxt, cr2, emulation_type))
		return 1;

	/* this is needed for vmware backdoor interface to work since it
	   changes registers values  during IO operation */
	if (vcpu->arch.emulate_regs_need_sync_from_vcpu) {
		vcpu->arch.emulate_regs_need_sync_from_vcpu = false;
		emulator_invalidate_register_cache(ctxt);
	}

restart:
	/* Save the faulting GPA (cr2) in the address field */
	ctxt->exception.address = cr2;

	r = x86_emulate_insn(ctxt);

	if (r == EMULATION_INTERCEPTED)
		return 1;

	if (r == EMULATION_FAILED) {
		if (reexecute_instruction(vcpu, cr2, write_fault_to_spt,
					emulation_type))
			return 1;

		return handle_emulation_failure(vcpu, emulation_type);
	}

	if (ctxt->have_exception) {
		r = 1;
		if (inject_emulated_exception(vcpu))
			return r;
	} else if (vcpu->arch.pio.count) {
		if (!vcpu->arch.pio.in) {
			/* FIXME: return into emulator if single-stepping.  */
			vcpu->arch.pio.count = 0;
		} else {
			writeback = false;
			vcpu->arch.complete_userspace_io = complete_emulated_pio;
		}
		r = 0;
	} else if (vcpu->mmio_needed) {
		++vcpu->stat.mmio_exits;

		if (!vcpu->mmio_is_write)
			writeback = false;
		r = 0;
		vcpu->arch.complete_userspace_io = complete_emulated_mmio;
	} else if (r == EMULATION_RESTART)
		goto restart;
	else
		r = 1;

	if (writeback) {
		unsigned long rflags = kvm_x86_ops->get_rflags(vcpu);
		toggle_interruptibility(vcpu, ctxt->interruptibility);
		vcpu->arch.emulate_regs_need_sync_to_vcpu = false;
		if (!ctxt->have_exception ||
		    exception_type(ctxt->exception.vector) == EXCPT_TRAP) {
			kvm_rip_write(vcpu, ctxt->eip);
			if (r && ctxt->tf)
				r = kvm_vcpu_do_singlestep(vcpu);
			__kvm_set_rflags(vcpu, ctxt->eflags);
		}

		/*
		 * For STI, interrupts are shadowed; so KVM_REQ_EVENT will
		 * do nothing, and it will be requested again as soon as
		 * the shadow expires.  But we still need to check here,
		 * because POPF has no interrupt shadow.
		 */
		if (unlikely((ctxt->eflags & ~rflags) & X86_EFLAGS_IF))
			kvm_make_request(KVM_REQ_EVENT, vcpu);
	} else
		vcpu->arch.emulate_regs_need_sync_to_vcpu = true;

	return r;
}