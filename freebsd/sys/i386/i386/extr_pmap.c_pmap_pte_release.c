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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PADDR2 ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PMAP2mutex ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline void
pmap_pte_release(pt_entry_t *pte)
{

	if ((pt_entry_t *)((vm_offset_t)pte & ~PAGE_MASK) == PADDR2)
		mtx_unlock(&PMAP2mutex);
}