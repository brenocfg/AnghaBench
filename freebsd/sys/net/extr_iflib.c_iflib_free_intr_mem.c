#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* if_ctx_t ;
struct TYPE_5__ {scalar_t__ isc_intr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ifc_msix_mem; int /*<<< orphan*/  ifc_dev; TYPE_1__ ifc_softc_ctx; int /*<<< orphan*/  ifc_legacy_irq; } ;

/* Variables and functions */
 scalar_t__ IFLIB_INTR_LEGACY ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_irq_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iflib_free_intr_mem(if_ctx_t ctx)
{

	if (ctx->ifc_softc_ctx.isc_intr != IFLIB_INTR_MSIX) {
		iflib_irq_free(ctx, &ctx->ifc_legacy_irq);
	}
	if (ctx->ifc_softc_ctx.isc_intr != IFLIB_INTR_LEGACY) {
		pci_release_msi(ctx->ifc_dev);
	}
	if (ctx->ifc_msix_mem != NULL) {
		bus_release_resource(ctx->ifc_dev, SYS_RES_MEMORY,
		    rman_get_rid(ctx->ifc_msix_mem), ctx->ifc_msix_mem);
		ctx->ifc_msix_mem = NULL;
	}
}