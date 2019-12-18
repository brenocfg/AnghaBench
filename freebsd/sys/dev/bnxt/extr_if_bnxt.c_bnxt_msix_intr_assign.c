#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; TYPE_1__ ring; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct bnxt_softc {TYPE_4__ def_cp_ring; int /*<<< orphan*/  irq; struct bnxt_softc* rx_cp_rings; TYPE_3__* scctx; TYPE_2__ ring; } ;
typedef  int /*<<< orphan*/  irq_name ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_7__ {int isc_nrxqsets; int isc_ntxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLIB_INTR_ADMIN ; 
 int /*<<< orphan*/  IFLIB_INTR_RX ; 
 int /*<<< orphan*/  IFLIB_INTR_TX ; 
 int /*<<< orphan*/  bnxt_handle_def_cp ; 
 int /*<<< orphan*/  bnxt_handle_rx_cp ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_irq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bnxt_softc*,int,char*) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_softirq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
bnxt_msix_intr_assign(if_ctx_t ctx, int msix)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);
	int rc;
	int i;
	char irq_name[16];

	rc = iflib_irq_alloc_generic(ctx, &softc->def_cp_ring.irq,
	    softc->def_cp_ring.ring.id + 1, IFLIB_INTR_ADMIN,
	    bnxt_handle_def_cp, softc, 0, "def_cp");
	if (rc) {
		device_printf(iflib_get_dev(ctx),
		    "Failed to register default completion ring handler\n");
		return rc;
	}

	for (i=0; i<softc->scctx->isc_nrxqsets; i++) {
		snprintf(irq_name, sizeof(irq_name), "rxq%d", i);
		rc = iflib_irq_alloc_generic(ctx, &softc->rx_cp_rings[i].irq,
		    softc->rx_cp_rings[i].ring.id + 1, IFLIB_INTR_RX,
		    bnxt_handle_rx_cp, &softc->rx_cp_rings[i], i, irq_name);
		if (rc) {
			device_printf(iflib_get_dev(ctx),
			    "Failed to register RX completion ring handler\n");
			i--;
			goto fail;
		}
	}

	for (i=0; i<softc->scctx->isc_ntxqsets; i++)
		iflib_softirq_alloc_generic(ctx, NULL, IFLIB_INTR_TX, NULL, i, "tx_cp");

	return rc;

fail:
	for (; i>=0; i--)
		iflib_irq_free(ctx, &softc->rx_cp_rings[i].irq);
	iflib_irq_free(ctx, &softc->def_cp_ring.irq);
	return rc;
}