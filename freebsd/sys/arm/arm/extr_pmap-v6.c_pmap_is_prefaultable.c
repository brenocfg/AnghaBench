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
typedef  int /*<<< orphan*/  pt2_entry_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pte1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt2map_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_load (int /*<<< orphan*/ ) ; 

boolean_t
pmap_is_prefaultable(pmap_t pmap, vm_offset_t addr)
{
	pt1_entry_t pte1;
	pt2_entry_t pte2;
	boolean_t rv;

	rv = FALSE;
	PMAP_LOCK(pmap);
	pte1 = pte1_load(pmap_pte1(pmap, addr));
	if (pte1_is_link(pte1)) {
		pte2 = pte2_load(pt2map_entry(addr));
		rv = !pte2_is_valid(pte2) ;
	}
	PMAP_UNLOCK(pmap);
	return (rv);
}