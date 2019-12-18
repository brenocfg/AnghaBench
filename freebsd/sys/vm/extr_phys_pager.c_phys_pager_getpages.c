#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct TYPE_7__ {int flags; scalar_t__ dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int VM_PAGER_OK ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int vm_page_all_valid (TYPE_1__*) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_1__*) ; 

__attribute__((used)) static int
phys_pager_getpages(vm_object_t object, vm_page_t *m, int count, int *rbehind,
    int *rahead)
{
	int i;

	VM_OBJECT_ASSERT_WLOCKED(object);
	for (i = 0; i < count; i++) {
		if (vm_page_none_valid(m[i])) {
			if ((m[i]->flags & PG_ZERO) == 0)
				pmap_zero_page(m[i]);
			vm_page_valid(m[i]);
		}
		KASSERT(vm_page_all_valid(m[i]),
		    ("phys_pager_getpages: partially valid page %p", m[i]));
		KASSERT(m[i]->dirty == 0,
		    ("phys_pager_getpages: dirty page %p", m[i]));
	}
	if (rbehind)
		*rbehind = 0;
	if (rahead)
		*rahead = 0;
	return (VM_PAGER_OK);
}