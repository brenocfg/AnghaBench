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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ register_t ;

/* Variables and functions */
 int ADDR_PIDX_SHFT ; 
 int /*<<< orphan*/  atomic_cmpset_int (scalar_t__ volatile*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intr_disable () ; 
 int /*<<< orphan*/  intr_restore (scalar_t__) ; 
 int /*<<< orphan*/  isync () ; 
 scalar_t__ moea64_crop_tlbie ; 
 int moea64_need_lock ; 

__attribute__((used)) static __inline void
TLBIE(uint64_t vpn) {
#ifndef __powerpc64__
	register_t vpn_hi, vpn_lo;
	register_t msr;
	register_t scratch, intr;
#endif

	static volatile u_int tlbie_lock = 0;
	bool need_lock = moea64_need_lock;

	vpn <<= ADDR_PIDX_SHFT;

	/* Hobo spinlock: we need stronger guarantees than mutexes provide */
	if (need_lock) {
		while (!atomic_cmpset_int(&tlbie_lock, 0, 1));
		isync(); /* Flush instruction queue once lock acquired */

		if (moea64_crop_tlbie)
			vpn &= ~(0xffffULL << 48);
	}

#ifdef __powerpc64__
	/*
	 * Explicitly clobber r0.  The tlbie instruction has two forms: an old
	 * one used by PowerISA 2.03 and prior, and a newer one used by PowerISA
	 * 2.06 (maybe 2.05?) and later.  We need to support both, and it just
	 * so happens that since we use 4k pages we can simply zero out r0, and
	 * clobber it, and the assembler will interpret the single-operand form
	 * of tlbie as having RB set, and everything else as 0.  The RS operand
	 * in the newer form is in the same position as the L(page size) bit of
	 * the old form, so a slong as RS is 0, we're good on both sides.
	 */
	__asm __volatile("li 0, 0 \n tlbie %0" :: "r"(vpn) : "r0", "memory");
	__asm __volatile("eieio; tlbsync; ptesync" ::: "memory");
#else
	vpn_hi = (uint32_t)(vpn >> 32);
	vpn_lo = (uint32_t)vpn;

	intr = intr_disable();
	__asm __volatile("\
	    mfmsr %0; \
	    mr %1, %0; \
	    insrdi %1,%5,1,0; \
	    mtmsrd %1; isync; \
	    \
	    sld %1,%2,%4; \
	    or %1,%1,%3; \
	    tlbie %1; \
	    \
	    mtmsrd %0; isync; \
	    eieio; \
	    tlbsync; \
	    ptesync;" 
	: "=r"(msr), "=r"(scratch) : "r"(vpn_hi), "r"(vpn_lo), "r"(32), "r"(1)
	    : "memory");
	intr_restore(intr);
#endif

	/* No barriers or special ops -- taken care of by ptesync above */
	if (need_lock)
		tlbie_lock = 0;
}