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
struct vlapic {int /*<<< orphan*/  vm; struct LAPIC* apic_page; } ;
struct LAPIC {int dfr; } ;

/* Variables and functions */
 int APIC_DFR_MODEL_CLUSTER ; 
 int APIC_DFR_MODEL_FLAT ; 
 int APIC_DFR_MODEL_MASK ; 
 int APIC_DFR_RESERVED ; 
 int /*<<< orphan*/  VLAPIC_CTR0 (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ x2apic (struct vlapic*) ; 

void
vlapic_dfr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;

	lapic = vlapic->apic_page;
	if (x2apic(vlapic)) {
		VM_CTR1(vlapic->vm, "ignoring write to DFR in x2apic mode: %#x",
		    lapic->dfr);
		lapic->dfr = 0;
		return;
	}

	lapic->dfr &= APIC_DFR_MODEL_MASK;
	lapic->dfr |= APIC_DFR_RESERVED;

	if ((lapic->dfr & APIC_DFR_MODEL_MASK) == APIC_DFR_MODEL_FLAT)
		VLAPIC_CTR0(vlapic, "vlapic DFR in Flat Model");
	else if ((lapic->dfr & APIC_DFR_MODEL_MASK) == APIC_DFR_MODEL_CLUSTER)
		VLAPIC_CTR0(vlapic, "vlapic DFR in Cluster Model");
	else
		VLAPIC_CTR1(vlapic, "DFR in Unknown Model %#x", lapic->dfr);
}