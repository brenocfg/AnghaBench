#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dmar_domain {scalar_t__ ctx_cnt; scalar_t__ refs; int flags; int /*<<< orphan*/  domain; TYPE_1__* dmar; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pgtbl_obj; int /*<<< orphan*/  contexts; int /*<<< orphan*/  unload_entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  domids; } ;

/* Variables and functions */
 int DMAR_DOMAIN_GAS_INITED ; 
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_PGLOCK (struct dmar_domain*) ; 
 int DMAR_DOMAIN_PGTBL_INITED ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DMAR_DOMAIN ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_gas_fini_domain (struct dmar_domain*) ; 
 int /*<<< orphan*/  domain_free_pgtbl (struct dmar_domain*) ; 
 int /*<<< orphan*/  free (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmar_domain_destroy(struct dmar_domain *domain)
{

	KASSERT(TAILQ_EMPTY(&domain->unload_entries),
	    ("unfinished unloads %p", domain));
	KASSERT(LIST_EMPTY(&domain->contexts),
	    ("destroying dom %p with contexts", domain));
	KASSERT(domain->ctx_cnt == 0,
	    ("destroying dom %p with ctx_cnt %d", domain, domain->ctx_cnt));
	KASSERT(domain->refs == 0,
	    ("destroying dom %p with refs %d", domain, domain->refs));
	if ((domain->flags & DMAR_DOMAIN_GAS_INITED) != 0) {
		DMAR_DOMAIN_LOCK(domain);
		dmar_gas_fini_domain(domain);
		DMAR_DOMAIN_UNLOCK(domain);
	}
	if ((domain->flags & DMAR_DOMAIN_PGTBL_INITED) != 0) {
		if (domain->pgtbl_obj != NULL)
			DMAR_DOMAIN_PGLOCK(domain);
		domain_free_pgtbl(domain);
	}
	mtx_destroy(&domain->lock);
	free_unr(domain->dmar->domids, domain->domain);
	free(domain, M_DMAR_DOMAIN);
}