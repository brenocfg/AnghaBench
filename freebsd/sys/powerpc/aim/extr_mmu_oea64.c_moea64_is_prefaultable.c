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
struct pvo_entry {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int ADDR_POFF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct pvo_entry* moea64_pvo_find_va (int /*<<< orphan*/ ,int) ; 

boolean_t
moea64_is_prefaultable(mmu_t mmu, pmap_t pmap, vm_offset_t va)
{
	struct pvo_entry *pvo;
	boolean_t rv = TRUE;

	PMAP_LOCK(pmap);
	pvo = moea64_pvo_find_va(pmap, va & ~ADDR_POFF);
	if (pvo != NULL)
		rv = FALSE;
	PMAP_UNLOCK(pmap);
	return (rv);
}