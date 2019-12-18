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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  KENTER_CACHE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kenter_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_wb_page (int /*<<< orphan*/ ) ; 

void
pmap_qenter(vm_offset_t va, vm_page_t *m, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		pmap_wb_page(m[i]);
		pmap_kenter_internal(va, VM_PAGE_TO_PHYS(m[i]),
		    KENTER_CACHE);
		va += PAGE_SIZE;
	}
}