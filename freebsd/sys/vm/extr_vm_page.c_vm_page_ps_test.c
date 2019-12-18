#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_object_t ;
struct TYPE_5__ {scalar_t__ object; size_t psind; scalar_t__ dirty; scalar_t__ valid; } ;

/* Variables and functions */
 int PS_ALL_DIRTY ; 
 int PS_ALL_VALID ; 
 int PS_NONE_BUSY ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (scalar_t__) ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int atop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pagesizes ; 
 scalar_t__ vm_page_busied (TYPE_1__*) ; 

bool
vm_page_ps_test(vm_page_t m, int flags, vm_page_t skip_m)
{
	vm_object_t object;
	int i, npages;

	object = m->object;
	if (skip_m != NULL && skip_m->object != object)
		return (false);
	VM_OBJECT_ASSERT_LOCKED(object);
	npages = atop(pagesizes[m->psind]);

	/*
	 * The physically contiguous pages that make up a superpage, i.e., a
	 * page with a page size index ("psind") greater than zero, will
	 * occupy adjacent entries in vm_page_array[].
	 */
	for (i = 0; i < npages; i++) {
		/* Always test object consistency, including "skip_m". */
		if (m[i].object != object)
			return (false);
		if (&m[i] == skip_m)
			continue;
		if ((flags & PS_NONE_BUSY) != 0 && vm_page_busied(&m[i]))
			return (false);
		if ((flags & PS_ALL_DIRTY) != 0) {
			/*
			 * Calling vm_page_test_dirty() or pmap_is_modified()
			 * might stop this case from spuriously returning
			 * "false".  However, that would require a write lock
			 * on the object containing "m[i]".
			 */
			if (m[i].dirty != VM_PAGE_BITS_ALL)
				return (false);
		}
		if ((flags & PS_ALL_VALID) != 0 &&
		    m[i].valid != VM_PAGE_BITS_ALL)
			return (false);
	}
	return (true);
}