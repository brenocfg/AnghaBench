#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int pending; } ;
struct TYPE_17__ {int /*<<< orphan*/  exit; } ;
struct TYPE_22__ {int halted; } ;
struct TYPE_13__ {int pending_ioapic_eoi; scalar_t__ mp_state; int switch_db_regs; int tsc_always_catchup; int apic_attention; int gpa_available; TYPE_6__* apic; int /*<<< orphan*/  last_guest_tsc; int /*<<< orphan*/  dr6; int /*<<< orphan*/ * eff_db; scalar_t__ apicv_active; TYPE_3__ exception; scalar_t__ nmi_pending; scalar_t__ smi_pending; TYPE_2__ hyperv; int /*<<< orphan*/  ioapic_handled_vectors; TYPE_7__ apf; } ;
struct TYPE_19__ {int /*<<< orphan*/  exits; int /*<<< orphan*/  req_event; } ;
struct kvm_vcpu {scalar_t__ mode; int guest_debug; TYPE_10__ arch; TYPE_12__* kvm; void* srcu_idx; int /*<<< orphan*/  vcpu_id; TYPE_4__ stat; TYPE_9__* run; scalar_t__ mmio_needed; } ;
typedef  scalar_t__ s64 ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct TYPE_23__ {int vector; } ;
struct TYPE_24__ {int /*<<< orphan*/  hyperv; void* exit_reason; TYPE_1__ system_event; TYPE_8__ eoi; } ;
struct TYPE_20__ {scalar_t__ advance_expire_delta; } ;
struct TYPE_21__ {TYPE_5__ lapic_timer; } ;
struct TYPE_15__ {int /*<<< orphan*/  srcu; } ;
struct TYPE_14__ {int (* handle_exit ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* cancel_injection ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* handle_exit_irqoff ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* sync_dirty_debug_regs ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* run ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* request_immediate_exit ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* sync_pir_to_irr ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* prepare_guest_switch ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* enable_irq_window ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* enable_nmi_window ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* enable_smi_window ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* get_vmcs12_pages ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXITING_GUEST_MODE ; 
 scalar_t__ IN_GUEST_MODE ; 
 int KVM_DEBUGREG_RELOAD ; 
 int KVM_DEBUGREG_WONT_EXIT ; 
 void* KVM_EXIT_HYPERV ; 
 void* KVM_EXIT_IOAPIC_EOI ; 
 void* KVM_EXIT_SHUTDOWN ; 
 void* KVM_EXIT_SYSTEM_EVENT ; 
 void* KVM_EXIT_TPR_ACCESS ; 
 int KVM_GUESTDBG_USE_HW_BP ; 
 scalar_t__ KVM_MP_STATE_INIT_RECEIVED ; 
 scalar_t__ KVM_PROFILING ; 
 int /*<<< orphan*/  KVM_REQ_APF_HALT ; 
 int /*<<< orphan*/  KVM_REQ_APIC_PAGE_RELOAD ; 
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  KVM_REQ_GET_VMCS12_PAGES ; 
 int /*<<< orphan*/  KVM_REQ_GLOBAL_CLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_HV_CRASH ; 
 int /*<<< orphan*/  KVM_REQ_HV_EXIT ; 
 int /*<<< orphan*/  KVM_REQ_HV_RESET ; 
 int /*<<< orphan*/  KVM_REQ_HV_STIMER ; 
 int /*<<< orphan*/  KVM_REQ_IOAPIC_EOI_EXIT ; 
 int /*<<< orphan*/  KVM_REQ_LOAD_CR3 ; 
 int /*<<< orphan*/  KVM_REQ_LOAD_EOI_EXITMAP ; 
 int /*<<< orphan*/  KVM_REQ_MASTERCLOCK_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_MIGRATE_TIMER ; 
 int /*<<< orphan*/  KVM_REQ_MMU_RELOAD ; 
 int /*<<< orphan*/  KVM_REQ_MMU_SYNC ; 
 int /*<<< orphan*/  KVM_REQ_NMI ; 
 int /*<<< orphan*/  KVM_REQ_PMI ; 
 int /*<<< orphan*/  KVM_REQ_PMU ; 
 int /*<<< orphan*/  KVM_REQ_REPORT_TPR_ACCESS ; 
 int /*<<< orphan*/  KVM_REQ_SCAN_IOAPIC ; 
 int /*<<< orphan*/  KVM_REQ_SMI ; 
 int /*<<< orphan*/  KVM_REQ_STEAL_UPDATE ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  KVM_REQ_TRIPLE_FAULT ; 
 int /*<<< orphan*/  KVM_SYSTEM_EVENT_CRASH ; 
 int /*<<< orphan*/  KVM_SYSTEM_EVENT_RESET ; 
 void* OUTSIDE_GUEST_MODE ; 
 scalar_t__ S64_MIN ; 
 int /*<<< orphan*/  TIF_NEED_FPU_LOAD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kvm_migrate_timers (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ dm_request_for_irq_injection (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  guest_enter_irqoff () ; 
 int /*<<< orphan*/  guest_exit_irqoff () ; 
 scalar_t__ hw_breakpoint_active () ; 
 int /*<<< orphan*/  hw_breakpoint_restore () ; 
 scalar_t__ inject_pending_event (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_after_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_apic_accept_events (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_before_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_check_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_accept_dm_intr (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_injectable_intr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_gen_kvmclock_update (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_gen_update_masterclock (TYPE_12__*) ; 
 int kvm_guest_time_update (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_hv_process_stimers (struct kvm_vcpu*) ; 
 scalar_t__ kvm_lapic_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_lapic_sync_from_vapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_lapic_sync_to_vapic (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_load_cr3 (struct kvm_vcpu*) ; 
 int kvm_mmu_reload (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_sync_roots (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_unload (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_deliver_pmi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_pmu_handle_event (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_read_l1_tsc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_request_pending (struct kvm_vcpu*) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr0123 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_dr7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_flush_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_vcpu_reload_apic_access_page (struct kvm_vcpu*) ; 
 TYPE_11__* kvm_x86_ops ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  process_nmi (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  process_smi (struct kvm_vcpu*) ; 
 scalar_t__ prof_on ; 
 int /*<<< orphan*/  profile_hit (scalar_t__,void*) ; 
 int /*<<< orphan*/  rdtsc () ; 
 int /*<<< orphan*/  record_steal_time (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_debugreg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_srcu_read_unlock () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 void* srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub10 (struct kvm_vcpu*) ; 
 int stub11 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub12 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub4 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub5 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub8 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub9 (struct kvm_vcpu*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_wait_lapic_expire (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_cr8_intercept (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load_eoi_exitmap (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_scan_ioapic (struct kvm_vcpu*) ; 

__attribute__((used)) static int vcpu_enter_guest(struct kvm_vcpu *vcpu)
{
	int r;
	bool req_int_win =
		dm_request_for_irq_injection(vcpu) &&
		kvm_cpu_accept_dm_intr(vcpu);

	bool req_immediate_exit = false;

	if (kvm_request_pending(vcpu)) {
		if (kvm_check_request(KVM_REQ_GET_VMCS12_PAGES, vcpu)) {
			if (unlikely(!kvm_x86_ops->get_vmcs12_pages(vcpu))) {
				r = 0;
				goto out;
			}
		}
		if (kvm_check_request(KVM_REQ_MMU_RELOAD, vcpu))
			kvm_mmu_unload(vcpu);
		if (kvm_check_request(KVM_REQ_MIGRATE_TIMER, vcpu))
			__kvm_migrate_timers(vcpu);
		if (kvm_check_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu))
			kvm_gen_update_masterclock(vcpu->kvm);
		if (kvm_check_request(KVM_REQ_GLOBAL_CLOCK_UPDATE, vcpu))
			kvm_gen_kvmclock_update(vcpu);
		if (kvm_check_request(KVM_REQ_CLOCK_UPDATE, vcpu)) {
			r = kvm_guest_time_update(vcpu);
			if (unlikely(r))
				goto out;
		}
		if (kvm_check_request(KVM_REQ_MMU_SYNC, vcpu))
			kvm_mmu_sync_roots(vcpu);
		if (kvm_check_request(KVM_REQ_LOAD_CR3, vcpu))
			kvm_mmu_load_cr3(vcpu);
		if (kvm_check_request(KVM_REQ_TLB_FLUSH, vcpu))
			kvm_vcpu_flush_tlb(vcpu, true);
		if (kvm_check_request(KVM_REQ_REPORT_TPR_ACCESS, vcpu)) {
			vcpu->run->exit_reason = KVM_EXIT_TPR_ACCESS;
			r = 0;
			goto out;
		}
		if (kvm_check_request(KVM_REQ_TRIPLE_FAULT, vcpu)) {
			vcpu->run->exit_reason = KVM_EXIT_SHUTDOWN;
			vcpu->mmio_needed = 0;
			r = 0;
			goto out;
		}
		if (kvm_check_request(KVM_REQ_APF_HALT, vcpu)) {
			/* Page is swapped out. Do synthetic halt */
			vcpu->arch.apf.halted = true;
			r = 1;
			goto out;
		}
		if (kvm_check_request(KVM_REQ_STEAL_UPDATE, vcpu))
			record_steal_time(vcpu);
		if (kvm_check_request(KVM_REQ_SMI, vcpu))
			process_smi(vcpu);
		if (kvm_check_request(KVM_REQ_NMI, vcpu))
			process_nmi(vcpu);
		if (kvm_check_request(KVM_REQ_PMU, vcpu))
			kvm_pmu_handle_event(vcpu);
		if (kvm_check_request(KVM_REQ_PMI, vcpu))
			kvm_pmu_deliver_pmi(vcpu);
		if (kvm_check_request(KVM_REQ_IOAPIC_EOI_EXIT, vcpu)) {
			BUG_ON(vcpu->arch.pending_ioapic_eoi > 255);
			if (test_bit(vcpu->arch.pending_ioapic_eoi,
				     vcpu->arch.ioapic_handled_vectors)) {
				vcpu->run->exit_reason = KVM_EXIT_IOAPIC_EOI;
				vcpu->run->eoi.vector =
						vcpu->arch.pending_ioapic_eoi;
				r = 0;
				goto out;
			}
		}
		if (kvm_check_request(KVM_REQ_SCAN_IOAPIC, vcpu))
			vcpu_scan_ioapic(vcpu);
		if (kvm_check_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu))
			vcpu_load_eoi_exitmap(vcpu);
		if (kvm_check_request(KVM_REQ_APIC_PAGE_RELOAD, vcpu))
			kvm_vcpu_reload_apic_access_page(vcpu);
		if (kvm_check_request(KVM_REQ_HV_CRASH, vcpu)) {
			vcpu->run->exit_reason = KVM_EXIT_SYSTEM_EVENT;
			vcpu->run->system_event.type = KVM_SYSTEM_EVENT_CRASH;
			r = 0;
			goto out;
		}
		if (kvm_check_request(KVM_REQ_HV_RESET, vcpu)) {
			vcpu->run->exit_reason = KVM_EXIT_SYSTEM_EVENT;
			vcpu->run->system_event.type = KVM_SYSTEM_EVENT_RESET;
			r = 0;
			goto out;
		}
		if (kvm_check_request(KVM_REQ_HV_EXIT, vcpu)) {
			vcpu->run->exit_reason = KVM_EXIT_HYPERV;
			vcpu->run->hyperv = vcpu->arch.hyperv.exit;
			r = 0;
			goto out;
		}

		/*
		 * KVM_REQ_HV_STIMER has to be processed after
		 * KVM_REQ_CLOCK_UPDATE, because Hyper-V SynIC timers
		 * depend on the guest clock being up-to-date
		 */
		if (kvm_check_request(KVM_REQ_HV_STIMER, vcpu))
			kvm_hv_process_stimers(vcpu);
	}

	if (kvm_check_request(KVM_REQ_EVENT, vcpu) || req_int_win) {
		++vcpu->stat.req_event;
		kvm_apic_accept_events(vcpu);
		if (vcpu->arch.mp_state == KVM_MP_STATE_INIT_RECEIVED) {
			r = 1;
			goto out;
		}

		if (inject_pending_event(vcpu, req_int_win) != 0)
			req_immediate_exit = true;
		else {
			/* Enable SMI/NMI/IRQ window open exits if needed.
			 *
			 * SMIs have three cases:
			 * 1) They can be nested, and then there is nothing to
			 *    do here because RSM will cause a vmexit anyway.
			 * 2) There is an ISA-specific reason why SMI cannot be
			 *    injected, and the moment when this changes can be
			 *    intercepted.
			 * 3) Or the SMI can be pending because
			 *    inject_pending_event has completed the injection
			 *    of an IRQ or NMI from the previous vmexit, and
			 *    then we request an immediate exit to inject the
			 *    SMI.
			 */
			if (vcpu->arch.smi_pending && !is_smm(vcpu))
				if (!kvm_x86_ops->enable_smi_window(vcpu))
					req_immediate_exit = true;
			if (vcpu->arch.nmi_pending)
				kvm_x86_ops->enable_nmi_window(vcpu);
			if (kvm_cpu_has_injectable_intr(vcpu) || req_int_win)
				kvm_x86_ops->enable_irq_window(vcpu);
			WARN_ON(vcpu->arch.exception.pending);
		}

		if (kvm_lapic_enabled(vcpu)) {
			update_cr8_intercept(vcpu);
			kvm_lapic_sync_to_vapic(vcpu);
		}
	}

	r = kvm_mmu_reload(vcpu);
	if (unlikely(r)) {
		goto cancel_injection;
	}

	preempt_disable();

	kvm_x86_ops->prepare_guest_switch(vcpu);

	/*
	 * Disable IRQs before setting IN_GUEST_MODE.  Posted interrupt
	 * IPI are then delayed after guest entry, which ensures that they
	 * result in virtual interrupt delivery.
	 */
	local_irq_disable();
	vcpu->mode = IN_GUEST_MODE;

	srcu_read_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);

	/*
	 * 1) We should set ->mode before checking ->requests.  Please see
	 * the comment in kvm_vcpu_exiting_guest_mode().
	 *
	 * 2) For APICv, we should set ->mode before checking PID.ON. This
	 * pairs with the memory barrier implicit in pi_test_and_set_on
	 * (see vmx_deliver_posted_interrupt).
	 *
	 * 3) This also orders the write to mode from any reads to the page
	 * tables done while the VCPU is running.  Please see the comment
	 * in kvm_flush_remote_tlbs.
	 */
	smp_mb__after_srcu_read_unlock();

	/*
	 * This handles the case where a posted interrupt was
	 * notified with kvm_vcpu_kick.
	 */
	if (kvm_lapic_enabled(vcpu) && vcpu->arch.apicv_active)
		kvm_x86_ops->sync_pir_to_irr(vcpu);

	if (vcpu->mode == EXITING_GUEST_MODE || kvm_request_pending(vcpu)
	    || need_resched() || signal_pending(current)) {
		vcpu->mode = OUTSIDE_GUEST_MODE;
		smp_wmb();
		local_irq_enable();
		preempt_enable();
		vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);
		r = 1;
		goto cancel_injection;
	}

	if (req_immediate_exit) {
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		kvm_x86_ops->request_immediate_exit(vcpu);
	}

	trace_kvm_entry(vcpu->vcpu_id);
	guest_enter_irqoff();

	/* The preempt notifier should have taken care of the FPU already.  */
	WARN_ON_ONCE(test_thread_flag(TIF_NEED_FPU_LOAD));

	if (unlikely(vcpu->arch.switch_db_regs)) {
		set_debugreg(0, 7);
		set_debugreg(vcpu->arch.eff_db[0], 0);
		set_debugreg(vcpu->arch.eff_db[1], 1);
		set_debugreg(vcpu->arch.eff_db[2], 2);
		set_debugreg(vcpu->arch.eff_db[3], 3);
		set_debugreg(vcpu->arch.dr6, 6);
		vcpu->arch.switch_db_regs &= ~KVM_DEBUGREG_RELOAD;
	}

	kvm_x86_ops->run(vcpu);

	/*
	 * Do this here before restoring debug registers on the host.  And
	 * since we do this before handling the vmexit, a DR access vmexit
	 * can (a) read the correct value of the debug registers, (b) set
	 * KVM_DEBUGREG_WONT_EXIT again.
	 */
	if (unlikely(vcpu->arch.switch_db_regs & KVM_DEBUGREG_WONT_EXIT)) {
		WARN_ON(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP);
		kvm_x86_ops->sync_dirty_debug_regs(vcpu);
		kvm_update_dr0123(vcpu);
		kvm_update_dr6(vcpu);
		kvm_update_dr7(vcpu);
		vcpu->arch.switch_db_regs &= ~KVM_DEBUGREG_RELOAD;
	}

	/*
	 * If the guest has used debug registers, at least dr7
	 * will be disabled while returning to the host.
	 * If we don't have active breakpoints in the host, we don't
	 * care about the messed up debug address registers. But if
	 * we have some of them active, restore the old state.
	 */
	if (hw_breakpoint_active())
		hw_breakpoint_restore();

	vcpu->arch.last_guest_tsc = kvm_read_l1_tsc(vcpu, rdtsc());

	vcpu->mode = OUTSIDE_GUEST_MODE;
	smp_wmb();

	kvm_x86_ops->handle_exit_irqoff(vcpu);

	/*
	 * Consume any pending interrupts, including the possible source of
	 * VM-Exit on SVM and any ticks that occur between VM-Exit and now.
	 * An instruction is required after local_irq_enable() to fully unblock
	 * interrupts on processors that implement an interrupt shadow, the
	 * stat.exits increment will do nicely.
	 */
	kvm_before_interrupt(vcpu);
	local_irq_enable();
	++vcpu->stat.exits;
	local_irq_disable();
	kvm_after_interrupt(vcpu);

	guest_exit_irqoff();
	if (lapic_in_kernel(vcpu)) {
		s64 delta = vcpu->arch.apic->lapic_timer.advance_expire_delta;
		if (delta != S64_MIN) {
			trace_kvm_wait_lapic_expire(vcpu->vcpu_id, delta);
			vcpu->arch.apic->lapic_timer.advance_expire_delta = S64_MIN;
		}
	}

	local_irq_enable();
	preempt_enable();

	vcpu->srcu_idx = srcu_read_lock(&vcpu->kvm->srcu);

	/*
	 * Profile KVM exit RIPs:
	 */
	if (unlikely(prof_on == KVM_PROFILING)) {
		unsigned long rip = kvm_rip_read(vcpu);
		profile_hit(KVM_PROFILING, (void *)rip);
	}

	if (unlikely(vcpu->arch.tsc_always_catchup))
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);

	if (vcpu->arch.apic_attention)
		kvm_lapic_sync_from_vapic(vcpu);

	vcpu->arch.gpa_available = false;
	r = kvm_x86_ops->handle_exit(vcpu);
	return r;

cancel_injection:
	kvm_x86_ops->cancel_injection(vcpu);
	if (unlikely(vcpu->arch.apic_attention))
		kvm_lapic_sync_from_vapic(vcpu);
out:
	return r;
}