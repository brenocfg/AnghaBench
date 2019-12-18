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
struct vmxnet3_txring {int /*<<< orphan*/  vxtxr_ndesc; } ;
struct vmxnet3_comp_ring {int /*<<< orphan*/  vxcr_ndesc; } ;
struct vmxnet3_txqueue {int vxtxq_id; struct vmxnet3_softc* vxtxq_sc; int /*<<< orphan*/  vxtxq_name; struct vmxnet3_txring vxtxq_cmd_ring; struct vmxnet3_comp_ring vxtxq_comp_ring; } ;
struct vmxnet3_softc {int /*<<< orphan*/  vmx_dev; TYPE_1__* vmx_scctx; struct vmxnet3_txqueue* vmx_txq; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {int /*<<< orphan*/ * isc_ntxd; } ;

/* Variables and functions */
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static void
vmxnet3_init_txq(struct vmxnet3_softc *sc, int q)
{
	struct vmxnet3_txqueue *txq;
	struct vmxnet3_comp_ring *txc;
	struct vmxnet3_txring *txr;
	if_softc_ctx_t scctx;
	
	txq = &sc->vmx_txq[q];
	txc = &txq->vxtxq_comp_ring;
	txr = &txq->vxtxq_cmd_ring;
	scctx = sc->vmx_scctx;

	snprintf(txq->vxtxq_name, sizeof(txq->vxtxq_name), "%s-tx%d",
	    device_get_nameunit(sc->vmx_dev), q);

	txq->vxtxq_sc = sc;
	txq->vxtxq_id = q;
	txc->vxcr_ndesc = scctx->isc_ntxd[0];
	txr->vxtxr_ndesc = scctx->isc_ntxd[1];
}