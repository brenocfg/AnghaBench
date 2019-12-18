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
struct dmar_domain {scalar_t__ refs; scalar_t__ ctx_cnt; int /*<<< orphan*/  contexts; int /*<<< orphan*/  dmar; } ;
struct dmar_ctx {struct dmar_domain* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dmar_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
dmar_ctx_link(struct dmar_ctx *ctx)
{
	struct dmar_domain *domain;

	domain = ctx->domain;
	DMAR_ASSERT_LOCKED(domain->dmar);
	KASSERT(domain->refs >= domain->ctx_cnt,
	    ("dom %p ref underflow %d %d", domain, domain->refs,
	    domain->ctx_cnt));
	domain->refs++;
	domain->ctx_cnt++;
	LIST_INSERT_HEAD(&domain->contexts, ctx, link);
}