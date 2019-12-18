#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; } ;
struct lpte {int pte_hi; int pte_lo; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int LPTE_AVPN_MASK ; 
 int be64toh (int) ; 
 int htobe64 (int) ; 
 int /*<<< orphan*/  moea64_eviction_lock ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int moea64_pte_replace_inval_native (int /*<<< orphan*/ ,struct pvo_entry*,struct lpte volatile*) ; 
 struct lpte* moea64_pteg_table ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
moea64_pte_replace_native(mmu_t mmu, struct pvo_entry *pvo, int flags)
{
	volatile struct lpte *pt = moea64_pteg_table + pvo->pvo_pte.slot;
	struct lpte properpt;
	int64_t ptelo;

	if (flags == 0) {
		/* Just some software bits changing. */
		moea64_pte_from_pvo(pvo, &properpt);

		rw_rlock(&moea64_eviction_lock);
		if ((be64toh(pt->pte_hi) & LPTE_AVPN_MASK) !=
		    (properpt.pte_hi & LPTE_AVPN_MASK)) {
			rw_runlock(&moea64_eviction_lock);
			return (-1);
		}
		pt->pte_hi = htobe64(properpt.pte_hi);
		ptelo = be64toh(pt->pte_lo);
		rw_runlock(&moea64_eviction_lock);
	} else {
		/* Otherwise, need reinsertion and deletion */
		ptelo = moea64_pte_replace_inval_native(mmu, pvo, pt);
	}

	return (ptelo);
}