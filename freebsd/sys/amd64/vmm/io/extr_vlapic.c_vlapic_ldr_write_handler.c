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
struct vlapic {struct LAPIC* apic_page; } ;
struct LAPIC {int /*<<< orphan*/  ldr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LDR_RESERVED ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ x2apic (struct vlapic*) ; 
 int /*<<< orphan*/  x2apic_ldr (struct vlapic*) ; 

void
vlapic_ldr_write_handler(struct vlapic *vlapic)
{
	struct LAPIC *lapic;

	lapic = vlapic->apic_page;

	/* LDR is read-only in x2apic mode */
	if (x2apic(vlapic)) {
		VLAPIC_CTR1(vlapic, "ignoring write to LDR in x2apic mode: %#x",
		    lapic->ldr);
		lapic->ldr = x2apic_ldr(vlapic);
	} else {
		lapic->ldr &= ~APIC_LDR_RESERVED;
		VLAPIC_CTR1(vlapic, "vlapic LDR set to %#x", lapic->ldr);
	}
}