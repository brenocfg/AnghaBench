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
struct pte {int pte_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int PTE_CHG ; 
 int PTE_REF ; 
 int /*<<< orphan*/  moea_table_mutex ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
moea_pte_synch(struct pte *pt, struct pte *pvo_pt)
{

	mtx_assert(&moea_table_mutex, MA_OWNED);
	pvo_pt->pte_lo |= pt->pte_lo & (PTE_REF | PTE_CHG);
}