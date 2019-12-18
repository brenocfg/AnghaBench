#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct dmar_domain {int flags; int /*<<< orphan*/ * pgtbl_obj; TYPE_1__* dmar; } ;
struct TYPE_7__ {scalar_t__ ref_count; } ;
struct TYPE_6__ {int hw_ecap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_ASSERT_PGLOCKED (struct dmar_domain*) ; 
 int DMAR_DOMAIN_IDMAP ; 
 int DMAR_ECAP_PT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_idmap_pgtbl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 TYPE_2__* vm_page_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* vm_page_next (TYPE_2__*) ; 

void
domain_free_pgtbl(struct dmar_domain *domain)
{
	vm_object_t obj;
	vm_page_t m;

	obj = domain->pgtbl_obj;
	if (obj == NULL) {
		KASSERT((domain->dmar->hw_ecap & DMAR_ECAP_PT) != 0 &&
		    (domain->flags & DMAR_DOMAIN_IDMAP) != 0,
		    ("lost pagetable object domain %p", domain));
		return;
	}
	DMAR_DOMAIN_ASSERT_PGLOCKED(domain);
	domain->pgtbl_obj = NULL;

	if ((domain->flags & DMAR_DOMAIN_IDMAP) != 0) {
		put_idmap_pgtbl(obj);
		domain->flags &= ~DMAR_DOMAIN_IDMAP;
		return;
	}

	/* Obliterate ref_counts */
	VM_OBJECT_ASSERT_WLOCKED(obj);
	for (m = vm_page_lookup(obj, 0); m != NULL; m = vm_page_next(m))
		m->ref_count = 0;
	VM_OBJECT_WUNLOCK(obj);
	vm_object_deallocate(obj);
}