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

/* Variables and functions */
#define  IBMPOWER8 131 
#define  IBMPOWER8E 130 
#define  IBMPOWER8NVL 129 
#define  IBMPOWER9 128 
 int LPCR_PECE_WAKESET ; 
 int PSL_HV ; 
 int /*<<< orphan*/  SPR_FSCR ; 
 int /*<<< orphan*/  SPR_LPCR ; 
 int /*<<< orphan*/  cpu_idle_hook ; 
 int /*<<< orphan*/  cpu_idle_power9 ; 
 int /*<<< orphan*/  cpu_idle_powerx ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cpu_powerx_setup(int cpuid, uint16_t vers)
{

#if defined(__powerpc64__) && defined(AIM)
	if ((mfmsr() & PSL_HV) == 0)
		return;

	/* Nuke the FSCR, to disable all facilities. */
	mtspr(SPR_FSCR, 0);

	/* Configure power-saving */
	switch (vers) {
	case IBMPOWER8:
	case IBMPOWER8E:
	case IBMPOWER8NVL:
		cpu_idle_hook = cpu_idle_powerx;
		mtspr(SPR_LPCR, mfspr(SPR_LPCR) | LPCR_PECE_WAKESET);
		isync();
		break;
	case IBMPOWER9:
		cpu_idle_hook = cpu_idle_power9;
		mtspr(SPR_LPCR, mfspr(SPR_LPCR) | LPCR_PECE_WAKESET);
		isync();
		break;
	default:
		return;
	}

#endif
}