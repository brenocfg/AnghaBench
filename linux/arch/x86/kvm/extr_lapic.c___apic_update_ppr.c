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
typedef  int u32 ;
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_PROCPRI ; 
 int /*<<< orphan*/  APIC_TASKPRI ; 
 int apic_find_highest_isr (struct kvm_lapic*) ; 
 int kvm_lapic_get_reg (struct kvm_lapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_set_reg (struct kvm_lapic*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool __apic_update_ppr(struct kvm_lapic *apic, u32 *new_ppr)
{
	u32 tpr, isrv, ppr, old_ppr;
	int isr;

	old_ppr = kvm_lapic_get_reg(apic, APIC_PROCPRI);
	tpr = kvm_lapic_get_reg(apic, APIC_TASKPRI);
	isr = apic_find_highest_isr(apic);
	isrv = (isr != -1) ? isr : 0;

	if ((tpr & 0xf0) >= (isrv & 0xf0))
		ppr = tpr & 0xff;
	else
		ppr = isrv & 0xf0;

	*new_ppr = ppr;
	if (old_ppr != ppr)
		kvm_lapic_set_reg(apic, APIC_PROCPRI, ppr);

	return ppr < old_ppr;
}