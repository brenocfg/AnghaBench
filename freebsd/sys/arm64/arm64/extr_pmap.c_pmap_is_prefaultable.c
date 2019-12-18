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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ pmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

boolean_t
pmap_is_prefaultable(pmap_t pmap, vm_offset_t addr)
{
	pt_entry_t *pte;
	boolean_t rv;
	int lvl;

	rv = FALSE;
	PMAP_LOCK(pmap);
	pte = pmap_pte(pmap, addr, &lvl);
	if (pte != NULL && pmap_load(pte) != 0) {
		rv = TRUE;
	}
	PMAP_UNLOCK(pmap);
	return (rv);
}