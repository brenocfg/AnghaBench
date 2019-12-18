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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_page_set_memattr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
ttm_vm_page_alloc_any(int req, vm_memattr_t memattr)
{
	vm_page_t p;

	while (1) {
		p = vm_page_alloc(NULL, 0, req);
		if (p != NULL)
			break;
		vm_wait(NULL);
	}
	pmap_page_set_memattr(p, memattr);
	return (p);
}