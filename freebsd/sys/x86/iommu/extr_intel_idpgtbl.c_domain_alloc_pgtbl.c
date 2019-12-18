#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct dmar_domain {int /*<<< orphan*/  dmar; int /*<<< orphan*/  flags; int /*<<< orphan*/ * pgtbl_obj; int /*<<< orphan*/  pglvl; } ;
struct TYPE_3__ {int ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_PGLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGTBL_INITED ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGUNLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_LOCK (int /*<<< orphan*/ ) ; 
 int DMAR_PGF_OBJL ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PGF_ZERO ; 
 int /*<<< orphan*/  DMAR_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDX_TO_OFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 TYPE_1__* dmar_pgalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pglvl_max_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
domain_alloc_pgtbl(struct dmar_domain *domain)
{
	vm_page_t m;

	KASSERT(domain->pgtbl_obj == NULL,
	    ("already initialized %p", domain));

	domain->pgtbl_obj = vm_pager_allocate(OBJT_PHYS, NULL,
	    IDX_TO_OFF(pglvl_max_pages(domain->pglvl)), 0, 0, NULL);
	DMAR_DOMAIN_PGLOCK(domain);
	m = dmar_pgalloc(domain->pgtbl_obj, 0, DMAR_PGF_WAITOK |
	    DMAR_PGF_ZERO | DMAR_PGF_OBJL);
	/* No implicit free of the top level page table page. */
	m->ref_count = 1;
	DMAR_DOMAIN_PGUNLOCK(domain);
	DMAR_LOCK(domain->dmar);
	domain->flags |= DMAR_DOMAIN_PGTBL_INITED;
	DMAR_UNLOCK(domain->dmar);
	return (0);
}