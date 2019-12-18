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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; } ;
struct lpte {int /*<<< orphan*/  pte_lo; int /*<<< orphan*/  pte_hi; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_write_htab_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pte_from_pvo (struct pvo_entry*,struct lpte*) ; 
 int /*<<< orphan*/  mps3_pte_synch_locked (struct pvo_entry*) ; 
 int /*<<< orphan*/  mps3_table_lock ; 
 int /*<<< orphan*/  mps3_vas_id ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
mps3_pte_clear(mmu_t mmu, struct pvo_entry *pvo, uint64_t ptebit)
{
	int64_t refchg;
	struct lpte pte;

	mtx_lock(&mps3_table_lock);

	refchg = mps3_pte_synch_locked(pvo);
	if (refchg < 0) {
		mtx_unlock(&mps3_table_lock);
		return (refchg);
	}

	moea64_pte_from_pvo(pvo, &pte);

	pte.pte_lo |= refchg;
	pte.pte_lo &= ~ptebit;
	/* XXX: race on RC bits between write and sync. Anything to do? */
	lv1_write_htab_entry(mps3_vas_id, pvo->pvo_pte.slot, pte.pte_hi,
	    pte.pte_lo);
	mtx_unlock(&mps3_table_lock);

	return (refchg);
}