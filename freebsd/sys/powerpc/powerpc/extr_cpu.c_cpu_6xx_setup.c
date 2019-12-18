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
 char* HID0_7450_BITMASK ; 
 int HID0_BHT ; 
 char* HID0_BITMASK ; 
 int HID0_BTIC ; 
 int HID0_DBP ; 
 int HID0_DOZE ; 
 int HID0_DPM ; 
 int HID0_EIEC ; 
 int HID0_EMCP ; 
 int HID0_FOLD ; 
 int HID0_LRSTK ; 
 int HID0_NAP ; 
 int HID0_SGE ; 
 int HID0_SLEEP ; 
 int HID0_SPD ; 
#define  IBM750FX 142 
#define  MPC603 141 
#define  MPC603e 140 
#define  MPC603ev 139 
#define  MPC604ev 138 
#define  MPC7400 137 
#define  MPC7410 136 
#define  MPC7447A 135 
#define  MPC7448 134 
#define  MPC7450 133 
#define  MPC7455 132 
#define  MPC7457 131 
#define  MPC750 130 
#define  MPC8240 129 
#define  MPC8245 128 
 int /*<<< orphan*/  SPR_HID0 ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cpu_6xx_print_cacheinfo (int,int) ; 
 int /*<<< orphan*/ * cpu_idle_60x ; 
 int /*<<< orphan*/ * cpu_idle_hook ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int powerpc_pow_enabled ; 
 int /*<<< orphan*/  printf (char*,int,int,char const*) ; 

void
cpu_6xx_setup(int cpuid, uint16_t vers)
{
	register_t hid0, pvr;
	const char *bitmask;

	hid0 = mfspr(SPR_HID0);
	pvr = mfpvr();

	/*
	 * Configure power-saving mode.
	 */
	switch (vers) {
		case MPC603:
		case MPC603e:
		case MPC603ev:
		case MPC604ev:
		case MPC750:
		case IBM750FX:
		case MPC7400:
		case MPC7410:
		case MPC8240:
		case MPC8245:
			/* Select DOZE mode. */
			hid0 &= ~(HID0_DOZE | HID0_NAP | HID0_SLEEP);
			hid0 |= HID0_DOZE | HID0_DPM;
			powerpc_pow_enabled = 1;
			break;

		case MPC7448:
		case MPC7447A:
		case MPC7457:
		case MPC7455:
		case MPC7450:
			/* Enable the 7450 branch caches */
			hid0 |= HID0_SGE | HID0_BTIC;
			hid0 |= HID0_LRSTK | HID0_FOLD | HID0_BHT;
			/* Disable BTIC on 7450 Rev 2.0 or earlier and on 7457 */
			if (((pvr >> 16) == MPC7450 && (pvr & 0xFFFF) <= 0x0200)
					|| (pvr >> 16) == MPC7457)
				hid0 &= ~HID0_BTIC;
			/* Select NAP mode. */
			hid0 &= ~(HID0_DOZE | HID0_NAP | HID0_SLEEP);
			hid0 |= HID0_NAP | HID0_DPM;
			powerpc_pow_enabled = 1;
			break;

		default:
			/* No power-saving mode is available. */ ;
	}

	switch (vers) {
		case IBM750FX:
		case MPC750:
			hid0 &= ~HID0_DBP;		/* XXX correct? */
			hid0 |= HID0_EMCP | HID0_BTIC | HID0_SGE | HID0_BHT;
			break;

		case MPC7400:
		case MPC7410:
			hid0 &= ~HID0_SPD;
			hid0 |= HID0_EMCP | HID0_BTIC | HID0_SGE | HID0_BHT;
			hid0 |= HID0_EIEC;
			break;

	}

	mtspr(SPR_HID0, hid0);

	if (bootverbose)
		cpu_6xx_print_cacheinfo(cpuid, vers);

	switch (vers) {
		case MPC7447A:
		case MPC7448:
		case MPC7450:
		case MPC7455:
		case MPC7457:
			bitmask = HID0_7450_BITMASK;
			break;
		default:
			bitmask = HID0_BITMASK;
			break;
	}

	printf("cpu%d: HID0 %b\n", cpuid, (int)hid0, bitmask);

	if (cpu_idle_hook == NULL)
		cpu_idle_hook = cpu_idle_60x;
}