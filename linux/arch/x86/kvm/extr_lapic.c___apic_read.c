#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
#define  APIC_ARBPRI 131 
#define  APIC_PROCPRI 130 
#define  APIC_TASKPRI 129 
#define  APIC_TMCCT 128 
 unsigned int LAPIC_MMIO_LENGTH ; 
 int /*<<< orphan*/  apic_get_tmcct (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_lvtt_tscdeadline (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_lapic_get_reg (struct kvm_lapic*,unsigned int) ; 
 int /*<<< orphan*/  report_tpr_access (struct kvm_lapic*,int) ; 

__attribute__((used)) static u32 __apic_read(struct kvm_lapic *apic, unsigned int offset)
{
	u32 val = 0;

	if (offset >= LAPIC_MMIO_LENGTH)
		return 0;

	switch (offset) {
	case APIC_ARBPRI:
		break;

	case APIC_TMCCT:	/* Timer CCR */
		if (apic_lvtt_tscdeadline(apic))
			return 0;

		val = apic_get_tmcct(apic);
		break;
	case APIC_PROCPRI:
		apic_update_ppr(apic);
		val = kvm_lapic_get_reg(apic, offset);
		break;
	case APIC_TASKPRI:
		report_tpr_access(apic, false);
		/* fall thru */
	default:
		val = kvm_lapic_get_reg(apic, offset);
		break;
	}

	return val;
}