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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int u_int ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  pmap_preboot_get_pages (int) ; 
 int /*<<< orphan*/  pmap_preboot_map_pages (int /*<<< orphan*/ ,int,int) ; 
 int virtual_avail ; 

vm_offset_t
pmap_preboot_get_vpages(u_int num)
{
	vm_paddr_t  pa;
	vm_offset_t va;

	/* Allocate physical page(s). */
	pa = pmap_preboot_get_pages(num);

	/* Allocate virtual space. */
	va = virtual_avail;
	virtual_avail += num * PAGE_SIZE;

	/* Map and zero all. */
	pmap_preboot_map_pages(pa, va, num);
	bzero((void *)va, num * PAGE_SIZE);

	return (va);
}