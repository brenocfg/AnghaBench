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
struct pvo_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  mps3_pte_synch_locked (struct pvo_entry*) ; 
 int /*<<< orphan*/  mps3_table_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t
mps3_pte_synch(mmu_t mmu, struct pvo_entry *pvo)
{
	int64_t retval;

	mtx_lock(&mps3_table_lock);
	retval = mps3_pte_synch_locked(pvo);
	mtx_unlock(&mps3_table_lock);

	return (retval);
}