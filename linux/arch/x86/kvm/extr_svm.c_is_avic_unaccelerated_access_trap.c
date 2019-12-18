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

/* Variables and functions */
#define  APIC_DFR 143 
#define  APIC_EOI 142 
#define  APIC_ESR 141 
#define  APIC_ICR 140 
#define  APIC_ID 139 
#define  APIC_LDR 138 
#define  APIC_LVT0 137 
#define  APIC_LVT1 136 
#define  APIC_LVTERR 135 
#define  APIC_LVTPC 134 
#define  APIC_LVTT 133 
#define  APIC_LVTTHMR 132 
#define  APIC_RRR 131 
#define  APIC_SPIV 130 
#define  APIC_TDCR 129 
#define  APIC_TMICT 128 

__attribute__((used)) static bool is_avic_unaccelerated_access_trap(u32 offset)
{
	bool ret = false;

	switch (offset) {
	case APIC_ID:
	case APIC_EOI:
	case APIC_RRR:
	case APIC_LDR:
	case APIC_DFR:
	case APIC_SPIV:
	case APIC_ESR:
	case APIC_ICR:
	case APIC_LVTT:
	case APIC_LVTTHMR:
	case APIC_LVTPC:
	case APIC_LVT0:
	case APIC_LVT1:
	case APIC_LVTERR:
	case APIC_TMICT:
	case APIC_TDCR:
		ret = true;
		break;
	default:
		break;
	}
	return ret;
}