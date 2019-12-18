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
struct TYPE_6__ {scalar_t__ msr_val; } ;
struct TYPE_7__ {int apic_base; scalar_t__ apic_attention; scalar_t__ apic_arb_prio; scalar_t__ apicv_active; TYPE_2__ pv_eoi; struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_3__ arch; int /*<<< orphan*/  kvm; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  pending; int /*<<< orphan*/  timer; } ;
struct kvm_lapic {int isr_count; int highest_isr_cache; TYPE_1__ lapic_timer; scalar_t__ irr_pending; int /*<<< orphan*/  vcpu; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* hwapic_isr_update ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* hwapic_irr_update ) (struct kvm_vcpu*,int) ;int /*<<< orphan*/  (* apicv_post_state_restore ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int APIC_DEFAULT_PHYS_BASE ; 
 scalar_t__ APIC_DFR ; 
 scalar_t__ APIC_ESR ; 
 scalar_t__ APIC_ICR ; 
 scalar_t__ APIC_ICR2 ; 
 scalar_t__ APIC_IRR ; 
 scalar_t__ APIC_ISR ; 
 scalar_t__ APIC_LVT0 ; 
 scalar_t__ APIC_LVTT ; 
 int APIC_LVT_MASKED ; 
 int /*<<< orphan*/  APIC_MODE_EXTINT ; 
 scalar_t__ APIC_TASKPRI ; 
 scalar_t__ APIC_TDCR ; 
 scalar_t__ APIC_TMICT ; 
 scalar_t__ APIC_TMR ; 
 int KVM_APIC_LVT_NUM ; 
 int /*<<< orphan*/  KVM_X86_QUIRK_LINT0_REENABLED ; 
 int MSR_IA32_APICBASE_BSP ; 
 int MSR_IA32_APICBASE_ENABLE ; 
 int SET_APIC_DELIVERY_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_manage_nmi_watchdog (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_set_spiv (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  apic_update_lvtt (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_x2apic_mode (struct kvm_lapic*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_apic_set_ldr (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_apic_set_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_apic_set_xapic_id (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_check_has_quirk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_get_reg (struct kvm_lapic*,scalar_t__) ; 
 int /*<<< orphan*/  kvm_lapic_set_base (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,scalar_t__,int) ; 
 scalar_t__ kvm_vcpu_is_bsp (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_is_reset_bsp (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  stub3 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  update_divide_count (struct kvm_lapic*) ; 

void kvm_lapic_reset(struct kvm_vcpu *vcpu, bool init_event)
{
	struct kvm_lapic *apic = vcpu->arch.apic;
	int i;

	if (!apic)
		return;

	/* Stop the timer in case it's a reset to an active apic */
	hrtimer_cancel(&apic->lapic_timer.timer);

	if (!init_event) {
		kvm_lapic_set_base(vcpu, APIC_DEFAULT_PHYS_BASE |
		                         MSR_IA32_APICBASE_ENABLE);
		kvm_apic_set_xapic_id(apic, vcpu->vcpu_id);
	}
	kvm_apic_set_version(apic->vcpu);

	for (i = 0; i < KVM_APIC_LVT_NUM; i++)
		kvm_lapic_set_reg(apic, APIC_LVTT + 0x10 * i, APIC_LVT_MASKED);
	apic_update_lvtt(apic);
	if (kvm_vcpu_is_reset_bsp(vcpu) &&
	    kvm_check_has_quirk(vcpu->kvm, KVM_X86_QUIRK_LINT0_REENABLED))
		kvm_lapic_set_reg(apic, APIC_LVT0,
			     SET_APIC_DELIVERY_MODE(0, APIC_MODE_EXTINT));
	apic_manage_nmi_watchdog(apic, kvm_lapic_get_reg(apic, APIC_LVT0));

	kvm_lapic_set_reg(apic, APIC_DFR, 0xffffffffU);
	apic_set_spiv(apic, 0xff);
	kvm_lapic_set_reg(apic, APIC_TASKPRI, 0);
	if (!apic_x2apic_mode(apic))
		kvm_apic_set_ldr(apic, 0);
	kvm_lapic_set_reg(apic, APIC_ESR, 0);
	kvm_lapic_set_reg(apic, APIC_ICR, 0);
	kvm_lapic_set_reg(apic, APIC_ICR2, 0);
	kvm_lapic_set_reg(apic, APIC_TDCR, 0);
	kvm_lapic_set_reg(apic, APIC_TMICT, 0);
	for (i = 0; i < 8; i++) {
		kvm_lapic_set_reg(apic, APIC_IRR + 0x10 * i, 0);
		kvm_lapic_set_reg(apic, APIC_ISR + 0x10 * i, 0);
		kvm_lapic_set_reg(apic, APIC_TMR + 0x10 * i, 0);
	}
	apic->irr_pending = vcpu->arch.apicv_active;
	apic->isr_count = vcpu->arch.apicv_active ? 1 : 0;
	apic->highest_isr_cache = -1;
	update_divide_count(apic);
	atomic_set(&apic->lapic_timer.pending, 0);
	if (kvm_vcpu_is_bsp(vcpu))
		kvm_lapic_set_base(vcpu,
				vcpu->arch.apic_base | MSR_IA32_APICBASE_BSP);
	vcpu->arch.pv_eoi.msr_val = 0;
	apic_update_ppr(apic);
	if (vcpu->arch.apicv_active) {
		kvm_x86_ops->apicv_post_state_restore(vcpu);
		kvm_x86_ops->hwapic_irr_update(vcpu, -1);
		kvm_x86_ops->hwapic_isr_update(vcpu, -1);
	}

	vcpu->arch.apic_arb_prio = 0;
	vcpu->arch.apic_attention = 0;
}