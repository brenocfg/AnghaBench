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
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;
struct pvo_entry {TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int int64_t ;

/* Variables and functions */
 int LPTE_CHG ; 
 int LPTE_REF ; 
 int /*<<< orphan*/  STAT_MOEA64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lv1_write_htab_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_pte_overflow ; 
 int /*<<< orphan*/  moea64_pte_valid ; 
 int mps3_pte_synch_locked (struct pvo_entry*) ; 
 int /*<<< orphan*/  mps3_table_lock ; 
 int /*<<< orphan*/  mps3_vas_id ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
mps3_pte_unset(mmu_t mmu, struct pvo_entry *pvo)
{
	int64_t refchg;

	mtx_lock(&mps3_table_lock);
	refchg = mps3_pte_synch_locked(pvo);
	if (refchg < 0) {
		STAT_MOEA64(moea64_pte_overflow--);
		mtx_unlock(&mps3_table_lock);
		return (-1);
	}
	/* XXX: race on RC bits between unset and sync. Anything to do? */
	lv1_write_htab_entry(mps3_vas_id, pvo->pvo_pte.slot, 0, 0);
	mtx_unlock(&mps3_table_lock);
	STAT_MOEA64(moea64_pte_valid--);

	return (refchg & (LPTE_REF | LPTE_CHG));
}