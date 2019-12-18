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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u32 ;
struct TYPE_4__ {int timer_mode_mask; int /*<<< orphan*/  timer; int /*<<< orphan*/  period; int /*<<< orphan*/  pending; } ;
struct kvm_lapic {TYPE_2__ lapic_timer; int /*<<< orphan*/  divide_count; TYPE_1__* vcpu; } ;
struct TYPE_3__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
#define  APIC_DFR 145 
#define  APIC_EOI 144 
#define  APIC_ESR 143 
#define  APIC_ICR 142 
#define  APIC_ICR2 141 
#define  APIC_ID 140 
#define  APIC_LDR 139 
 int APIC_LDR_MASK ; 
 int APIC_LVR ; 
 int APIC_LVR_DIRECTED_EOI ; 
#define  APIC_LVT0 138 
#define  APIC_LVT1 137 
#define  APIC_LVTERR 136 
#define  APIC_LVTPC 135 
#define  APIC_LVTT 134 
#define  APIC_LVTTHMR 133 
 int APIC_LVT_MASKED ; 
#define  APIC_SELF_IPI 132 
#define  APIC_SPIV 131 
 int APIC_SPIV_APIC_ENABLED ; 
 int APIC_SPIV_DIRECTED_EOI ; 
#define  APIC_TASKPRI 130 
#define  APIC_TDCR 129 
#define  APIC_TMICT 128 
 int KVM_APIC_LVT_NUM ; 
 int* apic_lvt_mask ; 
 int /*<<< orphan*/  apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_manage_nmi_watchdog (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  apic_send_ipi (struct kvm_lapic*,int,int) ; 
 int /*<<< orphan*/  apic_set_eoi (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_set_spiv (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  apic_set_tpr (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  apic_update_lvtt (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_x2apic_mode (struct kvm_lapic*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_apic_set_ldr (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  kvm_apic_set_xapic_id (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  kvm_apic_sw_enabled (struct kvm_lapic*) ; 
 int kvm_lapic_get_reg (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int const,int) ; 
 int /*<<< orphan*/  recalculate_apic_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_tpr_access (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  restart_apic_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  start_apic_timer (struct kvm_lapic*) ; 
 int /*<<< orphan*/  trace_kvm_apic_write (int,int) ; 
 int /*<<< orphan*/  update_divide_count (struct kvm_lapic*) ; 
 int /*<<< orphan*/  update_target_expiration (struct kvm_lapic*,int /*<<< orphan*/ ) ; 

int kvm_lapic_reg_write(struct kvm_lapic *apic, u32 reg, u32 val)
{
	int ret = 0;

	trace_kvm_apic_write(reg, val);

	switch (reg) {
	case APIC_ID:		/* Local APIC ID */
		if (!apic_x2apic_mode(apic))
			kvm_apic_set_xapic_id(apic, val >> 24);
		else
			ret = 1;
		break;

	case APIC_TASKPRI:
		report_tpr_access(apic, true);
		apic_set_tpr(apic, val & 0xff);
		break;

	case APIC_EOI:
		apic_set_eoi(apic);
		break;

	case APIC_LDR:
		if (!apic_x2apic_mode(apic))
			kvm_apic_set_ldr(apic, val & APIC_LDR_MASK);
		else
			ret = 1;
		break;

	case APIC_DFR:
		if (!apic_x2apic_mode(apic)) {
			kvm_lapic_set_reg(apic, APIC_DFR, val | 0x0FFFFFFF);
			recalculate_apic_map(apic->vcpu->kvm);
		} else
			ret = 1;
		break;

	case APIC_SPIV: {
		u32 mask = 0x3ff;
		if (kvm_lapic_get_reg(apic, APIC_LVR) & APIC_LVR_DIRECTED_EOI)
			mask |= APIC_SPIV_DIRECTED_EOI;
		apic_set_spiv(apic, val & mask);
		if (!(val & APIC_SPIV_APIC_ENABLED)) {
			int i;
			u32 lvt_val;

			for (i = 0; i < KVM_APIC_LVT_NUM; i++) {
				lvt_val = kvm_lapic_get_reg(apic,
						       APIC_LVTT + 0x10 * i);
				kvm_lapic_set_reg(apic, APIC_LVTT + 0x10 * i,
					     lvt_val | APIC_LVT_MASKED);
			}
			apic_update_lvtt(apic);
			atomic_set(&apic->lapic_timer.pending, 0);

		}
		break;
	}
	case APIC_ICR:
		/* No delay here, so we always clear the pending bit */
		val &= ~(1 << 12);
		apic_send_ipi(apic, val, kvm_lapic_get_reg(apic, APIC_ICR2));
		kvm_lapic_set_reg(apic, APIC_ICR, val);
		break;

	case APIC_ICR2:
		if (!apic_x2apic_mode(apic))
			val &= 0xff000000;
		kvm_lapic_set_reg(apic, APIC_ICR2, val);
		break;

	case APIC_LVT0:
		apic_manage_nmi_watchdog(apic, val);
		/* fall through */
	case APIC_LVTTHMR:
	case APIC_LVTPC:
	case APIC_LVT1:
	case APIC_LVTERR:
		/* TODO: Check vector */
		if (!kvm_apic_sw_enabled(apic))
			val |= APIC_LVT_MASKED;

		val &= apic_lvt_mask[(reg - APIC_LVTT) >> 4];
		kvm_lapic_set_reg(apic, reg, val);

		break;

	case APIC_LVTT:
		if (!kvm_apic_sw_enabled(apic))
			val |= APIC_LVT_MASKED;
		val &= (apic_lvt_mask[0] | apic->lapic_timer.timer_mode_mask);
		kvm_lapic_set_reg(apic, APIC_LVTT, val);
		apic_update_lvtt(apic);
		break;

	case APIC_TMICT:
		if (apic_lvtt_tscdeadline(apic))
			break;

		hrtimer_cancel(&apic->lapic_timer.timer);
		kvm_lapic_set_reg(apic, APIC_TMICT, val);
		start_apic_timer(apic);
		break;

	case APIC_TDCR: {
		uint32_t old_divisor = apic->divide_count;

		kvm_lapic_set_reg(apic, APIC_TDCR, val);
		update_divide_count(apic);
		if (apic->divide_count != old_divisor &&
				apic->lapic_timer.period) {
			hrtimer_cancel(&apic->lapic_timer.timer);
			update_target_expiration(apic, old_divisor);
			restart_apic_timer(apic);
		}
		break;
	}
	case APIC_ESR:
		if (apic_x2apic_mode(apic) && val != 0)
			ret = 1;
		break;

	case APIC_SELF_IPI:
		if (apic_x2apic_mode(apic)) {
			kvm_lapic_reg_write(apic, APIC_ICR, 0x40000 | (val & 0xff));
		} else
			ret = 1;
		break;
	default:
		ret = 1;
		break;
	}

	return ret;
}