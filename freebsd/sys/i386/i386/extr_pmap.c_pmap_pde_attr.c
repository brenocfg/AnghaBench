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
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int PG_PDE_CACHE ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 

__attribute__((used)) static __inline void
pmap_pde_attr(pd_entry_t *pde, int cache_bits)
{
	u_int opde, npde;

	/*
	 * The cache mode bits are all in the low 32-bits of the
	 * PDE, so we can just spin on updating the low 32-bits.
	 */
	do {
		opde = *(u_int *)pde;
		npde = opde & ~PG_PDE_CACHE;
		npde |= cache_bits;
	} while (npde != opde && !atomic_cmpset_int((u_int *)pde, opde, npde));
}