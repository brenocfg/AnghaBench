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
struct dmar_unit {int /*<<< orphan*/  delayed_taskqueue; int /*<<< orphan*/  unit; } ;
struct dmar_domain {int refs; int ctx_cnt; int flags; int /*<<< orphan*/  unload_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_DOMAIN_RMRR ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct dmar_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_domain_destroy (struct dmar_domain*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmar_unref_domain_locked(struct dmar_unit *dmar, struct dmar_domain *domain)
{

	DMAR_ASSERT_LOCKED(dmar);
	KASSERT(domain->refs >= 1,
	    ("dmar %d domain %p refs %u", dmar->unit, domain, domain->refs));
	KASSERT(domain->refs > domain->ctx_cnt,
	    ("dmar %d domain %p refs %d ctx_cnt %d", dmar->unit, domain,
	    domain->refs, domain->ctx_cnt));

	if (domain->refs > 1) {
		domain->refs--;
		DMAR_UNLOCK(dmar);
		return;
	}

	KASSERT((domain->flags & DMAR_DOMAIN_RMRR) == 0,
	    ("lost ref on RMRR domain %p", domain));

	LIST_REMOVE(domain, link);
	DMAR_UNLOCK(dmar);

	taskqueue_drain(dmar->delayed_taskqueue, &domain->unload_task);
	dmar_domain_destroy(domain);
}