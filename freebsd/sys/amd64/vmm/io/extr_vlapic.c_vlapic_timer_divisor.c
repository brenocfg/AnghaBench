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
typedef  int uint32_t ;

/* Variables and functions */
#define  APIC_TDCR_1 135 
#define  APIC_TDCR_128 134 
#define  APIC_TDCR_16 133 
#define  APIC_TDCR_2 132 
#define  APIC_TDCR_32 131 
#define  APIC_TDCR_4 130 
#define  APIC_TDCR_64 129 
#define  APIC_TDCR_8 128 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
vlapic_timer_divisor(uint32_t dcr)
{
	switch (dcr & 0xB) {
	case APIC_TDCR_1:
		return (1);
	case APIC_TDCR_2:
		return (2);
	case APIC_TDCR_4:
		return (4);
	case APIC_TDCR_8:
		return (8);
	case APIC_TDCR_16:
		return (16);
	case APIC_TDCR_32:
		return (32);
	case APIC_TDCR_64:
		return (64);
	case APIC_TDCR_128:
		return (128);
	default:
		panic("vlapic_timer_divisor: invalid dcr 0x%08x", dcr);
	}
}