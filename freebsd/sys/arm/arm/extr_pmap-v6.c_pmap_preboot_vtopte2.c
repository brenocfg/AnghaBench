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

/* Variables and functions */
 int /*<<< orphan*/ * kern_pte1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_preboot_pt2_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pt2map_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline pt2_entry_t*
pmap_preboot_vtopte2(vm_offset_t va)
{
	pt1_entry_t *pte1p;

	/* Setup PT2 if needed. */
	pte1p = kern_pte1(va);
	if (!pte1_is_valid(pte1_load(pte1p))) /* XXX - sections ?! */
		pmap_preboot_pt2_setup(va);

	return (pt2map_entry(va));
}