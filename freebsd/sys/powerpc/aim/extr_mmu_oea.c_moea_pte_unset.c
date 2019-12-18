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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pte {int /*<<< orphan*/  pte_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PTE_VALID ; 
 int /*<<< orphan*/  moea_pte_synch (struct pte*,struct pte*) ; 
 int /*<<< orphan*/  moea_pte_valid ; 
 int /*<<< orphan*/  moea_table_mutex ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_sync () ; 
 int /*<<< orphan*/  tlbie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
moea_pte_unset(struct pte *pt, struct pte *pvo_pt, vm_offset_t va)
{

	mtx_assert(&moea_table_mutex, MA_OWNED);
	pvo_pt->pte_hi &= ~PTE_VALID;

	/*
	 * Force the reg & chg bits back into the PTEs.
	 */
	powerpc_sync();

	/*
	 * Invalidate the pte.
	 */
	pt->pte_hi &= ~PTE_VALID;

	tlbie(va);

	/*
	 * Save the reg & chg bits.
	 */
	moea_pte_synch(pt, pvo_pt);
	moea_pte_valid--;
}