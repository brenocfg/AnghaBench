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
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_kenter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  qmap_mtx ; 

vm_offset_t
pmap_quick_enter_page(vm_page_t m)
{
	/*
	 * Don't bother with a PCPU pageframe, since we don't support
	 * SMP for anything pre-armv7.  Use pmap_kenter() to ensure
	 * caching is handled correctly for multiple mappings of the
	 * same physical page.
	 */

	mtx_assert(&qmap_mtx, MA_NOTOWNED);
	mtx_lock(&qmap_mtx);

	pmap_kenter(qmap_addr, VM_PAGE_TO_PHYS(m));

	return (qmap_addr);
}