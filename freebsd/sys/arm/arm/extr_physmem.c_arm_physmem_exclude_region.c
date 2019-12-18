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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ excnt ; 
 int /*<<< orphan*/  exregions ; 
 scalar_t__ insert_region (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

void
arm_physmem_exclude_region(vm_paddr_t pa, vm_size_t sz, uint32_t exflags)
{
	vm_offset_t adj;

	/*
	 * Truncate the starting address down to a page boundary, and round the
	 * ending page up to a page boundary.
	 */
	adj = pa - trunc_page(pa);
	pa  = trunc_page(pa);
	sz  = round_page(sz + adj);

	if (excnt >= nitems(exregions))
		panic("failed to exclude region %#jx-%#jx", (uintmax_t)pa,
		    (uintmax_t)(pa + sz));
	excnt = insert_region(exregions, excnt, pa, sz, exflags);
}