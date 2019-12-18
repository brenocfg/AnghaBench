#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_4__ {int ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAP_TO_PHYS (uintptr_t) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_pti_free_page (TYPE_1__*) ; 
 int /*<<< orphan*/  pti_obj ; 

__attribute__((used)) static void
pmap_pti_unwire_pde(void *pde, bool only_ref)
{
	vm_page_t m;

	VM_OBJECT_ASSERT_WLOCKED(pti_obj);
	m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((uintptr_t)pde));
	MPASS(m->ref_count > 0);
	MPASS(only_ref || m->ref_count > 1);
	pmap_pti_free_page(m);
}