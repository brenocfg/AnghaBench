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
typedef  int uint64_t ;
typedef  int uint16_t ;
struct vlapic_vtx {struct pir_desc* pir_desc; } ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; struct LAPIC* apic_page; } ;
struct pir_desc {int /*<<< orphan*/ * pir; int /*<<< orphan*/  pending; } ;
struct LAPIC {int irr0; int irr1; int irr2; int irr3; int irr4; int irr5; int irr6; int irr7; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VCPU_CTR2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  VLAPIC_CTR_IRR (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VMCS_GUEST_INTR_STATUS ; 
 scalar_t__ atomic_cmpset_long (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int atomic_readandclear_long (int /*<<< orphan*/ *) ; 
 int flsl (int) ; 
 int vmcs_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmx_inject_pir(struct vlapic *vlapic)
{
	struct vlapic_vtx *vlapic_vtx;
	struct pir_desc *pir_desc;
	struct LAPIC *lapic;
	uint64_t val, pirval;
	int rvi, pirbase = -1;
	uint16_t intr_status_old, intr_status_new;

	vlapic_vtx = (struct vlapic_vtx *)vlapic;
	pir_desc = vlapic_vtx->pir_desc;
	if (atomic_cmpset_long(&pir_desc->pending, 1, 0) == 0) {
		VCPU_CTR0(vlapic->vm, vlapic->vcpuid, "vmx_inject_pir: "
		    "no posted interrupt pending");
		return;
	}

	pirval = 0;
	pirbase = -1;
	lapic = vlapic->apic_page;

	val = atomic_readandclear_long(&pir_desc->pir[0]);
	if (val != 0) {
		lapic->irr0 |= val;
		lapic->irr1 |= val >> 32;
		pirbase = 0;
		pirval = val;
	}

	val = atomic_readandclear_long(&pir_desc->pir[1]);
	if (val != 0) {
		lapic->irr2 |= val;
		lapic->irr3 |= val >> 32;
		pirbase = 64;
		pirval = val;
	}

	val = atomic_readandclear_long(&pir_desc->pir[2]);
	if (val != 0) {
		lapic->irr4 |= val;
		lapic->irr5 |= val >> 32;
		pirbase = 128;
		pirval = val;
	}

	val = atomic_readandclear_long(&pir_desc->pir[3]);
	if (val != 0) {
		lapic->irr6 |= val;
		lapic->irr7 |= val >> 32;
		pirbase = 192;
		pirval = val;
	}

	VLAPIC_CTR_IRR(vlapic, "vmx_inject_pir");

	/*
	 * Update RVI so the processor can evaluate pending virtual
	 * interrupts on VM-entry.
	 *
	 * It is possible for pirval to be 0 here, even though the
	 * pending bit has been set. The scenario is:
	 * CPU-Y is sending a posted interrupt to CPU-X, which
	 * is running a guest and processing posted interrupts in h/w.
	 * CPU-X will eventually exit and the state seen in s/w is
	 * the pending bit set, but no PIR bits set.
	 *
	 *      CPU-X                      CPU-Y
	 *   (vm running)                (host running)
	 *   rx posted interrupt
	 *   CLEAR pending bit
	 *				 SET PIR bit
	 *   READ/CLEAR PIR bits
	 *				 SET pending bit
	 *   (vm exit)
	 *   pending bit set, PIR 0
	 */
	if (pirval != 0) {
		rvi = pirbase + flsl(pirval) - 1;
		intr_status_old = vmcs_read(VMCS_GUEST_INTR_STATUS);
		intr_status_new = (intr_status_old & 0xFF00) | rvi;
		if (intr_status_new > intr_status_old) {
			vmcs_write(VMCS_GUEST_INTR_STATUS, intr_status_new);
			VCPU_CTR2(vlapic->vm, vlapic->vcpuid, "vmx_inject_pir: "
			    "guest_intr_status changed from 0x%04x to 0x%04x",
			    intr_status_old, intr_status_new);
		}
	}
}