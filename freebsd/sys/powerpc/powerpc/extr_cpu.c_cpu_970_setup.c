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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HID0_970_BITMASK ; 
 int HID0_DEEPNAP ; 
 int HID0_DOZE ; 
 int HID0_DPM ; 
 int HID0_NAP ; 
#define  IBM970MP 128 
 int /*<<< orphan*/  cpu_idle_60x ; 
 int /*<<< orphan*/  cpu_idle_hook ; 
 int powerpc_pow_enabled ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpu_970_setup(int cpuid, uint16_t vers)
{
#ifdef AIM
	uint32_t hid0_hi, hid0_lo;

	__asm __volatile ("mfspr %0,%2; clrldi %1,%0,32; srdi %0,%0,32;"
	    : "=r" (hid0_hi), "=r" (hid0_lo) : "K" (SPR_HID0));

	/* Configure power-saving mode */
	switch (vers) {
	case IBM970MP:
		hid0_hi |= (HID0_DEEPNAP | HID0_NAP | HID0_DPM);
		hid0_hi &= ~HID0_DOZE;
		break;
	default:
		hid0_hi |= (HID0_NAP | HID0_DPM);
		hid0_hi &= ~(HID0_DOZE | HID0_DEEPNAP);
		break;
	}
	powerpc_pow_enabled = 1;

	__asm __volatile (" \
		sync; isync;					\
		sldi	%0,%0,32; or %0,%0,%1;			\
		mtspr	%2, %0;					\
		mfspr   %0, %2; mfspr   %0, %2; mfspr   %0, %2; \
		mfspr   %0, %2; mfspr   %0, %2; mfspr   %0, %2; \
		sync; isync"
	    :: "r" (hid0_hi), "r"(hid0_lo), "K" (SPR_HID0));

	__asm __volatile ("mfspr %0,%1; srdi %0,%0,32;"
	    : "=r" (hid0_hi) : "K" (SPR_HID0));
	printf("cpu%d: HID0 %b\n", cpuid, (int)(hid0_hi), HID0_970_BITMASK);
#endif

	cpu_idle_hook = cpu_idle_60x;
}