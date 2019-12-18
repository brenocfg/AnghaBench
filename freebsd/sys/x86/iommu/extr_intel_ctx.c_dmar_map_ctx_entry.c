#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sf_buf {int dummy; } ;
struct dmar_ctx {int rid; TYPE_2__* domain; } ;
typedef  int /*<<< orphan*/  dmar_ctx_entry_t ;
struct TYPE_4__ {TYPE_1__* dmar; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctx_obj; } ;

/* Variables and functions */
 int DMAR_PGF_NOALLOC ; 
 int DMAR_PGF_WAITOK ; 
 scalar_t__ PCI_RID2BUS (int) ; 
 int /*<<< orphan*/ * dmar_map_pgtbl (int /*<<< orphan*/ ,scalar_t__,int,struct sf_buf**) ; 

__attribute__((used)) static dmar_ctx_entry_t *
dmar_map_ctx_entry(struct dmar_ctx *ctx, struct sf_buf **sfp)
{
	dmar_ctx_entry_t *ctxp;

	ctxp = dmar_map_pgtbl(ctx->domain->dmar->ctx_obj, 1 +
	    PCI_RID2BUS(ctx->rid), DMAR_PGF_NOALLOC | DMAR_PGF_WAITOK, sfp);
	ctxp += ctx->rid & 0xff;
	return (ctxp);
}