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
struct TYPE_5__ {int flags; unsigned int pindex; } ;

/* Variables and functions */
 int PG_ZERO ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_FREELIST_DIRECT ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 TYPE_1__* vm_page_alloc_freelist (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static vm_page_t
pmap_alloc_direct_page(unsigned int index, int req)
{
	vm_page_t m;

	m = vm_page_alloc_freelist(VM_FREELIST_DIRECT, req | VM_ALLOC_WIRED |
	    VM_ALLOC_ZERO);
	if (m == NULL)
		return (NULL);

	if ((m->flags & PG_ZERO) == 0)
		pmap_zero_page(m);

	m->pindex = index;
	return (m);
}