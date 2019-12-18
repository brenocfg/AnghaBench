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

/* Variables and functions */
 scalar_t__ MIPS_CACHE_ERR_EXC_VEC ; 
 scalar_t__ MIPS_GEN_EXC_VEC ; 
 int MIPS_SR_BEV ; 
 scalar_t__ MIPS_UTLB_MISS_EXC_VEC ; 
 scalar_t__ MIPS_XTLB_MISS_EXC_VEC ; 
 int MipsCache ; 
 int MipsCacheEnd ; 
 int MipsException ; 
 int MipsExceptionEnd ; 
 int MipsTLBMiss ; 
 int MipsTLBMissEnd ; 
 int MipsWaitEnd ; 
 int MipsWaitStart ; 
 int /*<<< orphan*/  bcopy (int,void*,int) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_all () ; 
 int /*<<< orphan*/  mips_icache_sync_all () ; 
 int mips_rd_status () ; 
 int /*<<< orphan*/  mips_wr_status (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  set_intr_mask (int /*<<< orphan*/ ) ; 

void
mips_vector_init(void)
{
	/*
	 * Make sure that the Wait region logic is not been 
	 * changed
	 */
	if (MipsWaitEnd - MipsWaitStart != 16)
		panic("startup: MIPS wait region not correct");
	/*
	 * Copy down exception vector code.
	 */
	if (MipsTLBMissEnd - MipsTLBMiss > 0x80)
		panic("startup: UTLB code too large");

	if (MipsCacheEnd - MipsCache > 0x80)
		panic("startup: Cache error code too large");

	bcopy(MipsTLBMiss, (void *)MIPS_UTLB_MISS_EXC_VEC,
	      MipsTLBMissEnd - MipsTLBMiss);

	/*
	 * XXXRW: Why don't we install the XTLB handler for all 64-bit
	 * architectures?
	 */
#if defined(__mips_n64) || defined(CPU_RMI) || defined(CPU_NLM) || defined(CPU_BERI)
/* Fake, but sufficient, for the 32-bit with 64-bit hardware addresses  */
	bcopy(MipsTLBMiss, (void *)MIPS_XTLB_MISS_EXC_VEC,
	      MipsTLBMissEnd - MipsTLBMiss);
#endif

	bcopy(MipsException, (void *)MIPS_GEN_EXC_VEC,
	      MipsExceptionEnd - MipsException);

	bcopy(MipsCache, (void *)MIPS_CACHE_ERR_EXC_VEC,
	      MipsCacheEnd - MipsCache);

	/*
	 * Clear out the I and D caches.
	 */
	mips_icache_sync_all();
	mips_dcache_wbinv_all();

	/* 
	 * Mask all interrupts. Each interrupt will be enabled
	 * when handler is installed for it
	 */
	set_intr_mask(0);

	/* Clear BEV in SR so we start handling our own exceptions */
	mips_wr_status(mips_rd_status() & ~MIPS_SR_BEV);
}