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
struct dmar_unit {int dummy; } ;
struct dmar_ctx {TYPE_1__* domain; } ;
struct TYPE_2__ {struct dmar_unit* dmar; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_free_ctx_locked (struct dmar_unit*,struct dmar_ctx*) ; 

void
dmar_free_ctx(struct dmar_ctx *ctx)
{
	struct dmar_unit *dmar;

	dmar = ctx->domain->dmar;
	DMAR_LOCK(dmar);
	dmar_free_ctx_locked(dmar, ctx);
}