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
typedef  int u_int ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int PG_PTE_CACHE ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 

__attribute__((used)) static __inline void
pmap_pte_attr(pt_entry_t *pte, int cache_bits)
{
	u_int opte, npte;

	/*
	 * The cache mode bits are all in the low 32-bits of the
	 * PTE, so we can just spin on updating the low 32-bits.
	 */
	do {
		opte = *(u_int *)pte;
		npte = opte & ~PG_PTE_CACHE;
		npte |= cache_bits;
	} while (npte != opte && !atomic_cmpset_int((u_int *)pte, opte, npte));
}