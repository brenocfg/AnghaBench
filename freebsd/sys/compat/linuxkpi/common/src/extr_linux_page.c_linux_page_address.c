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
struct page {scalar_t__ object; int /*<<< orphan*/  pindex; } ;

/* Variables and functions */
 scalar_t__ IDX_TO_OFF (int /*<<< orphan*/ ) ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 scalar_t__ PMAP_HAS_DMAP ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (struct page*) ; 
 scalar_t__ kernel_object ; 
 scalar_t__ kmem_object ; 

void *
linux_page_address(struct page *page)
{

	if (page->object != kmem_object && page->object != kernel_object) {
		return (PMAP_HAS_DMAP ?
		    ((void *)(uintptr_t)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(page))) :
		    NULL);
	}
	return ((void *)(uintptr_t)(VM_MIN_KERNEL_ADDRESS +
	    IDX_TO_OFF(page->pindex)));
}