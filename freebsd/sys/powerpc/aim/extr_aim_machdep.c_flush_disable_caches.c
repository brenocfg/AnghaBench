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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int register_t ;

/* Variables and functions */
 int HID0_DCE ; 
 int L2CR_L2DO_7450 ; 
 int L2CR_L2E ; 
 int L2CR_L2HWF ; 
 int L2CR_L2I ; 
 int L2CR_L2IO_7450 ; 
 int L3CR_L3DO ; 
 int L3CR_L3E ; 
 int L3CR_L3HWF ; 
 int L3CR_L3I ; 
 int L3CR_L3IO ; 
 int MSSCR0_L2PFE ; 
 int PSL_DR ; 
 int PSL_EE ; 
 int /*<<< orphan*/  SPR_HID0 ; 
 int /*<<< orphan*/  SPR_L2CR ; 
 int /*<<< orphan*/  SPR_L3CR ; 
 int /*<<< orphan*/  SPR_LDSTCR ; 
 int /*<<< orphan*/  SPR_MSSCR0 ; 
 int /*<<< orphan*/  isync () ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

void
flush_disable_caches(void)
{
	register_t msr;
	register_t msscr0;
	register_t cache_reg;
	volatile uint32_t *memp;
	uint32_t temp;
	int i;
	int x;

	msr = mfmsr();
	powerpc_sync();
	mtmsr(msr & ~(PSL_EE | PSL_DR));
	msscr0 = mfspr(SPR_MSSCR0);
	msscr0 &= ~MSSCR0_L2PFE;
	mtspr(SPR_MSSCR0, msscr0);
	powerpc_sync();
	isync();
	__asm__ __volatile__("dssall; sync");
	powerpc_sync();
	isync();
	__asm__ __volatile__("dcbf 0,%0" :: "r"(0));
	__asm__ __volatile__("dcbf 0,%0" :: "r"(0));
	__asm__ __volatile__("dcbf 0,%0" :: "r"(0));

	/* Lock the L1 Data cache. */
	mtspr(SPR_LDSTCR, mfspr(SPR_LDSTCR) | 0xFF);
	powerpc_sync();
	isync();

	mtspr(SPR_LDSTCR, 0);

	/*
	 * Perform this in two stages: Flush the cache starting in RAM, then do it
	 * from ROM.
	 */
	memp = (volatile uint32_t *)0x00000000;
	for (i = 0; i < 128 * 1024; i++) {
		temp = *memp;
		__asm__ __volatile__("dcbf 0,%0" :: "r"(memp));
		memp += 32/sizeof(*memp);
	}

	memp = (volatile uint32_t *)0xfff00000;
	x = 0xfe;

	for (; x != 0xff;) {
		mtspr(SPR_LDSTCR, x);
		for (i = 0; i < 128; i++) {
			temp = *memp;
			__asm__ __volatile__("dcbf 0,%0" :: "r"(memp));
			memp += 32/sizeof(*memp);
		}
		x = ((x << 1) | 1) & 0xff;
	}
	mtspr(SPR_LDSTCR, 0);

	cache_reg = mfspr(SPR_L2CR);
	if (cache_reg & L2CR_L2E) {
		cache_reg &= ~(L2CR_L2IO_7450 | L2CR_L2DO_7450);
		mtspr(SPR_L2CR, cache_reg);
		powerpc_sync();
		mtspr(SPR_L2CR, cache_reg | L2CR_L2HWF);
		while (mfspr(SPR_L2CR) & L2CR_L2HWF)
			; /* Busy wait for cache to flush */
		powerpc_sync();
		cache_reg &= ~L2CR_L2E;
		mtspr(SPR_L2CR, cache_reg);
		powerpc_sync();
		mtspr(SPR_L2CR, cache_reg | L2CR_L2I);
		powerpc_sync();
		while (mfspr(SPR_L2CR) & L2CR_L2I)
			; /* Busy wait for L2 cache invalidate */
		powerpc_sync();
	}

	cache_reg = mfspr(SPR_L3CR);
	if (cache_reg & L3CR_L3E) {
		cache_reg &= ~(L3CR_L3IO | L3CR_L3DO);
		mtspr(SPR_L3CR, cache_reg);
		powerpc_sync();
		mtspr(SPR_L3CR, cache_reg | L3CR_L3HWF);
		while (mfspr(SPR_L3CR) & L3CR_L3HWF)
			; /* Busy wait for cache to flush */
		powerpc_sync();
		cache_reg &= ~L3CR_L3E;
		mtspr(SPR_L3CR, cache_reg);
		powerpc_sync();
		mtspr(SPR_L3CR, cache_reg | L3CR_L3I);
		powerpc_sync();
		while (mfspr(SPR_L3CR) & L3CR_L3I)
			; /* Busy wait for L3 cache invalidate */
		powerpc_sync();
	}

	mtspr(SPR_HID0, mfspr(SPR_HID0) & ~HID0_DCE);
	powerpc_sync();
	isync();

	mtmsr(msr);
}