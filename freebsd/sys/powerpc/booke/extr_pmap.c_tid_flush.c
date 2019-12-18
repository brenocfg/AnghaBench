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
typedef  int tlbtid_t ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
#define  FSL_E500mc 130 
#define  FSL_E5500 129 
#define  FSL_E6500 128 
 int MAS0_ESEL (int) ; 
 int MAS0_TLBSEL (int /*<<< orphan*/ ) ; 
 int MAS1_TID_MASK ; 
 int MAS1_TID_SHIFT ; 
 int MAS1_VALID ; 
 int MAS2_TLB0_ENTRY_IDX_SHIFT ; 
 int MAS6_SPID0_SHIFT ; 
 int /*<<< orphan*/  SPR_MAS0 ; 
 int /*<<< orphan*/  SPR_MAS1 ; 
 int /*<<< orphan*/  SPR_MAS2 ; 
 int /*<<< orphan*/  SPR_MAS6 ; 
 int TID_KERNEL ; 
 int TLB0_ENTRIES_PER_WAY ; 
 int TLB0_WAYS ; 
 int /*<<< orphan*/  mfmsr () ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tid_flush(tlbtid_t tid)
{
	register_t msr;
	uint32_t mas0, mas1, mas2;
	int entry, way;


	/* Don't evict kernel translations */
	if (tid == TID_KERNEL)
		return;

	msr = mfmsr();
	__asm __volatile("wrteei 0");

	/*
	 * Newer (e500mc and later) have tlbilx, which doesn't broadcast, so use
	 * it for PID invalidation.
	 */
	switch ((mfpvr() >> 16) & 0xffff) {
	case FSL_E500mc:
	case FSL_E5500:
	case FSL_E6500:
		mtspr(SPR_MAS6, tid << MAS6_SPID0_SHIFT);
		/* tlbilxpid */
		__asm __volatile("isync; .long 0x7c000024; isync; msync");
		__asm __volatile("wrtee %0" :: "r"(msr));
		return;
	}

	for (way = 0; way < TLB0_WAYS; way++)
		for (entry = 0; entry < TLB0_ENTRIES_PER_WAY; entry++) {

			mas0 = MAS0_TLBSEL(0) | MAS0_ESEL(way);
			mtspr(SPR_MAS0, mas0);

			mas2 = entry << MAS2_TLB0_ENTRY_IDX_SHIFT;
			mtspr(SPR_MAS2, mas2);

			__asm __volatile("isync; tlbre");

			mas1 = mfspr(SPR_MAS1);

			if (!(mas1 & MAS1_VALID))
				continue;
			if (((mas1 & MAS1_TID_MASK) >> MAS1_TID_SHIFT) != tid)
				continue;
			mas1 &= ~MAS1_VALID;
			mtspr(SPR_MAS1, mas1);
			__asm __volatile("isync; tlbwe; isync; msync");
		}
	__asm __volatile("wrtee %0" :: "r"(msr));
}