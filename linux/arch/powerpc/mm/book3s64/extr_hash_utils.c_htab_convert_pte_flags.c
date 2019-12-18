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
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_G ; 
 unsigned long HPTE_R_I ; 
 unsigned long HPTE_R_M ; 
 unsigned long HPTE_R_N ; 
 int HPTE_R_PP0 ; 
 unsigned long HPTE_R_R ; 
 unsigned long HPTE_R_W ; 
 int /*<<< orphan*/  MMU_FTR_KERNEL_RO ; 
 unsigned long _PAGE_CACHE_CTL ; 
 unsigned long _PAGE_DIRTY ; 
 unsigned long _PAGE_EXEC ; 
 unsigned long _PAGE_NON_IDEMPOTENT ; 
 unsigned long _PAGE_PRIVILEGED ; 
 unsigned long _PAGE_RWX ; 
 unsigned long _PAGE_SAO ; 
 unsigned long _PAGE_TOLERANT ; 
 unsigned long _PAGE_WRITE ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned long pte_to_hpte_pkey_bits (unsigned long) ; 

unsigned long htab_convert_pte_flags(unsigned long pteflags)
{
	unsigned long rflags = 0;

	/* _PAGE_EXEC -> NOEXEC */
	if ((pteflags & _PAGE_EXEC) == 0)
		rflags |= HPTE_R_N;
	/*
	 * PPP bits:
	 * Linux uses slb key 0 for kernel and 1 for user.
	 * kernel RW areas are mapped with PPP=0b000
	 * User area is mapped with PPP=0b010 for read/write
	 * or PPP=0b011 for read-only (including writeable but clean pages).
	 */
	if (pteflags & _PAGE_PRIVILEGED) {
		/*
		 * Kernel read only mapped with ppp bits 0b110
		 */
		if (!(pteflags & _PAGE_WRITE)) {
			if (mmu_has_feature(MMU_FTR_KERNEL_RO))
				rflags |= (HPTE_R_PP0 | 0x2);
			else
				rflags |= 0x3;
		}
	} else {
		if (pteflags & _PAGE_RWX)
			rflags |= 0x2;
		if (!((pteflags & _PAGE_WRITE) && (pteflags & _PAGE_DIRTY)))
			rflags |= 0x1;
	}
	/*
	 * We can't allow hardware to update hpte bits. Hence always
	 * set 'R' bit and set 'C' if it is a write fault
	 */
	rflags |=  HPTE_R_R;

	if (pteflags & _PAGE_DIRTY)
		rflags |= HPTE_R_C;
	/*
	 * Add in WIG bits
	 */

	if ((pteflags & _PAGE_CACHE_CTL) == _PAGE_TOLERANT)
		rflags |= HPTE_R_I;
	else if ((pteflags & _PAGE_CACHE_CTL) == _PAGE_NON_IDEMPOTENT)
		rflags |= (HPTE_R_I | HPTE_R_G);
	else if ((pteflags & _PAGE_CACHE_CTL) == _PAGE_SAO)
		rflags |= (HPTE_R_W | HPTE_R_I | HPTE_R_M);
	else
		/*
		 * Add memory coherence if cache inhibited is not set
		 */
		rflags |= HPTE_R_M;

	rflags |= pte_to_hpte_pkey_bits(pteflags);
	return rflags;
}