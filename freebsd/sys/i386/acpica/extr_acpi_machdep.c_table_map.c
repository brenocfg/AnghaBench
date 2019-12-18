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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  invlpg (int) ; 
 int /*<<< orphan*/  pmap_kenter (int,int) ; 
 scalar_t__ pmap_kenter_temporary (int,int) ; 
 int pmap_pg_frame (int) ; 
 int round_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
table_map(vm_paddr_t pa, int offset, vm_offset_t length)
{
	vm_offset_t va, off;
	void *data;

	off = pa & PAGE_MASK;
	length = round_page(length + off);
	pa = pmap_pg_frame(pa);
	va = (vm_offset_t)pmap_kenter_temporary(pa, offset) +
	    (offset * PAGE_SIZE);
	data = (void *)(va + off);
	length -= PAGE_SIZE;
	while (length > 0) {
		va += PAGE_SIZE;
		pa += PAGE_SIZE;
		length -= PAGE_SIZE;
		pmap_kenter(va, pa);
		invlpg(va);
	}
	return (data);
}