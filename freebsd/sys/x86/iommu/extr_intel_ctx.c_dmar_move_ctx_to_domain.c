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
struct sf_buf {int dummy; } ;
struct dmar_unit {int unit; } ;
struct dmar_domain {int domain; int flags; struct dmar_unit* dmar; } ;
struct dmar_ctx {int rid; struct dmar_domain* domain; } ;
typedef  int /*<<< orphan*/  dmar_ctx_entry_t ;

/* Variables and functions */
 int DMAR_DOMAIN_IDMAP ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TD_PINNED_ASSERT ; 
 int /*<<< orphan*/  TD_PREP_PINNED_ASSERT ; 
 int /*<<< orphan*/  ctx_id_entry_init (struct dmar_ctx*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmar_ctx_link (struct dmar_ctx*) ; 
 int /*<<< orphan*/  dmar_ctx_unlink (struct dmar_ctx*) ; 
 int dmar_flush_for_ctx_entry (struct dmar_unit*,int) ; 
 int /*<<< orphan*/ * dmar_map_ctx_entry (struct dmar_ctx*,struct sf_buf**) ; 
 int /*<<< orphan*/  dmar_unmap_pgtbl (struct sf_buf*) ; 
 int /*<<< orphan*/  dmar_unref_domain_locked (struct dmar_unit*,struct dmar_domain*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,char*) ; 

int
dmar_move_ctx_to_domain(struct dmar_domain *domain, struct dmar_ctx *ctx)
{
	struct dmar_unit *dmar;
	struct dmar_domain *old_domain;
	dmar_ctx_entry_t *ctxp;
	struct sf_buf *sf;
	int error;

	dmar = domain->dmar;
	old_domain = ctx->domain;
	if (domain == old_domain)
		return (0);
	KASSERT(old_domain->dmar == dmar,
	    ("domain %p %u moving between dmars %u %u", domain,
	    domain->domain, old_domain->dmar->unit, domain->dmar->unit));
	TD_PREP_PINNED_ASSERT;

	ctxp = dmar_map_ctx_entry(ctx, &sf);
	DMAR_LOCK(dmar);
	dmar_ctx_unlink(ctx);
	ctx->domain = domain;
	dmar_ctx_link(ctx);
	ctx_id_entry_init(ctx, ctxp, true);
	dmar_unmap_pgtbl(sf);
	error = dmar_flush_for_ctx_entry(dmar, true);
	/* If flush failed, rolling back would not work as well. */
	printf("dmar%d rid %x domain %d->%d %s-mapped\n",
	    dmar->unit, ctx->rid, old_domain->domain, domain->domain,
	    (domain->flags & DMAR_DOMAIN_IDMAP) != 0 ? "id" : "re");
	dmar_unref_domain_locked(dmar, old_domain);
	TD_PINNED_ASSERT;
	return (error);
}