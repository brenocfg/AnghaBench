#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_6__ {int pte_hi; int pte_lo; } ;
struct TYPE_7__ {TYPE_2__ pte; } ;
struct pvo_entry {TYPE_3__ pvo_pte; int /*<<< orphan*/  pvo_vaddr; TYPE_1__* pvo_pmap; } ;
struct pte {int pte_hi; int pte_lo; } ;
struct TYPE_8__ {struct pte* pt; } ;
struct TYPE_5__ {int /*<<< orphan*/  pm_sr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PTE_CHG ; 
 int PTE_REF ; 
 int PTE_VALID ; 
 scalar_t__ PVO_PTEGIDX_ISSET (struct pvo_entry const*) ; 
 TYPE_4__* moea_pteg_table ; 
 int moea_pvo_pte_index (struct pvo_entry const*,int) ; 
 int /*<<< orphan*/  moea_table_mutex ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct pvo_entry const*,...) ; 
 int va_to_pteg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_to_sr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pte *
moea_pvo_to_pte(const struct pvo_entry *pvo, int pteidx)
{
	struct	pte *pt;

	/*
	 * If we haven't been supplied the ptegidx, calculate it.
	 */
	if (pteidx == -1) {
		int	ptegidx;
		u_int	sr;

		sr = va_to_sr(pvo->pvo_pmap->pm_sr, pvo->pvo_vaddr);
		ptegidx = va_to_pteg(sr, pvo->pvo_vaddr);
		pteidx = moea_pvo_pte_index(pvo, ptegidx);
	}

	pt = &moea_pteg_table[pteidx >> 3].pt[pteidx & 7];
	mtx_lock(&moea_table_mutex);

	if ((pvo->pvo_pte.pte.pte_hi & PTE_VALID) && !PVO_PTEGIDX_ISSET(pvo)) {
		panic("moea_pvo_to_pte: pvo %p has valid pte in pvo but no "
		    "valid pte index", pvo);
	}

	if ((pvo->pvo_pte.pte.pte_hi & PTE_VALID) == 0 && PVO_PTEGIDX_ISSET(pvo)) {
		panic("moea_pvo_to_pte: pvo %p has valid pte index in pvo "
		    "pvo but no valid pte", pvo);
	}

	if ((pt->pte_hi ^ (pvo->pvo_pte.pte.pte_hi & ~PTE_VALID)) == PTE_VALID) {
		if ((pvo->pvo_pte.pte.pte_hi & PTE_VALID) == 0) {
			panic("moea_pvo_to_pte: pvo %p has valid pte in "
			    "moea_pteg_table %p but invalid in pvo", pvo, pt);
		}

		if (((pt->pte_lo ^ pvo->pvo_pte.pte.pte_lo) & ~(PTE_CHG|PTE_REF))
		    != 0) {
			panic("moea_pvo_to_pte: pvo %p pte does not match "
			    "pte %p in moea_pteg_table", pvo, pt);
		}

		mtx_assert(&moea_table_mutex, MA_OWNED);
		return (pt);
	}

	if (pvo->pvo_pte.pte.pte_hi & PTE_VALID) {
		panic("moea_pvo_to_pte: pvo %p has invalid pte %p in "
		    "moea_pteg_table but valid in pvo: %8x, %8x", pvo, pt, pvo->pvo_pte.pte.pte_hi, pt->pte_hi);
	}

	mtx_unlock(&moea_table_mutex);
	return (NULL);
}