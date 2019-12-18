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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int DBCR0_IDM ; 
 int DBCR0_RST_SYSTEM ; 
 int /*<<< orphan*/  OCP85XX_RSTCR ; 
 int PSL_DE ; 
 int /*<<< orphan*/  SPR_DBCR0 ; 
 int /*<<< orphan*/  ccsr_write4 (int /*<<< orphan*/ ,int) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
mpc85xx_reset(platform_t plat)
{

	/*
	 * Try the dedicated reset register first.
	 * If the SoC doesn't have one, we'll fall
	 * back to using the debug control register.
	 */
	ccsr_write4(OCP85XX_RSTCR, 2);

	mtmsr(mfmsr() & ~PSL_DE);

	/* Enable debug interrupts and issue reset. */
	mtspr(SPR_DBCR0, DBCR0_IDM | DBCR0_RST_SYSTEM);
	__asm __volatile("isync");

	/* Enable Debug Interrupts in MSR. */
	mtmsr(mfmsr() | PSL_DE);

	printf("Reset failed...\n");
	while (1)
		;
}