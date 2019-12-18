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
typedef  int uint16_t ;
typedef  int register_t ;

/* Variables and functions */
#define  FSL_E500mc 132 
#define  FSL_E500v1 131 
#define  FSL_E500v2 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 int HID0_DOZE ; 
 char* HID0_E500MC_BITMASK ; 
 char* HID0_E500_BITMASK ; 
 char* HID0_E5500_BITMASK ; 
 int HID0_NAP ; 
 int HID0_SLEEP ; 
 int /*<<< orphan*/  SPR_HID0 ; 
 int /*<<< orphan*/ * cpu_idle_booke ; 
 int /*<<< orphan*/ * cpu_idle_e500mc ; 
 int /*<<< orphan*/ * cpu_idle_hook ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,char const*) ; 

__attribute__((used)) static void
cpu_booke_setup(int cpuid, uint16_t vers)
{
#ifdef BOOKE_E500
	register_t hid0;
	const char *bitmask;

	hid0 = mfspr(SPR_HID0);

	switch (vers) {
	case FSL_E500mc:
		bitmask = HID0_E500MC_BITMASK;
		cpu_idle_hook = cpu_idle_e500mc;
		break;
	case FSL_E5500:
	case FSL_E6500:
		bitmask = HID0_E5500_BITMASK;
		cpu_idle_hook = cpu_idle_e500mc;
		break;
	case FSL_E500v1:
	case FSL_E500v2:
		/* Only e500v1/v2 support HID0 power management setup. */

		/* Program power-management mode. */
		hid0 &= ~(HID0_DOZE | HID0_NAP | HID0_SLEEP);
		hid0 |= HID0_DOZE;

		mtspr(SPR_HID0, hid0);
	default:
		bitmask = HID0_E500_BITMASK;
		break;
	}
	printf("cpu%d: HID0 %b\n", cpuid, (int)hid0, bitmask);
#endif

	if (cpu_idle_hook == NULL)
		cpu_idle_hook = cpu_idle_booke;
}