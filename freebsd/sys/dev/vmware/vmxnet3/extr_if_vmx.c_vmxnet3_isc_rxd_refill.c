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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct vmxnet3_softc {struct vmxnet3_rxqueue* vmx_rxq; } ;
struct vmxnet3_rxring {int vxrxr_gen; int vxrxr_ndesc; struct vmxnet3_rxdesc* vxrxr_rxd; } ;
struct vmxnet3_rxqueue {struct vmxnet3_rxring* vxrxq_cmd_ring; } ;
struct vmxnet3_rxdesc {int len; size_t btype; int gen; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__* if_rxd_update_t ;
struct TYPE_3__ {int iru_count; int iru_buf_size; int iru_pidx; size_t iru_flidx; size_t iru_qsidx; int /*<<< orphan*/ * iru_paddrs; } ;

/* Variables and functions */
 size_t VMXNET3_BTYPE_BODY ; 
 size_t VMXNET3_BTYPE_HEAD ; 

__attribute__((used)) static void
vmxnet3_isc_rxd_refill(void *vsc, if_rxd_update_t iru)
{
	struct vmxnet3_softc *sc;
	struct vmxnet3_rxqueue *rxq;
	struct vmxnet3_rxring *rxr;
	struct vmxnet3_rxdesc *rxd;
	uint64_t *paddrs;
	int count;
	int len;
	int pidx;
	int i;
	uint8_t flid;
	uint8_t btype;

	count = iru->iru_count;
	len = iru->iru_buf_size;
	pidx = iru->iru_pidx;
	flid = iru->iru_flidx;
	paddrs = iru->iru_paddrs;

	sc = vsc;
	rxq = &sc->vmx_rxq[iru->iru_qsidx];
	rxr = &rxq->vxrxq_cmd_ring[flid];
	rxd = rxr->vxrxr_rxd;

	/*
	 * Command ring 0 is filled with BTYPE_HEAD descriptors, and
	 * command ring 1 is filled with BTYPE_BODY descriptors.
	 */
	btype = (flid == 0) ? VMXNET3_BTYPE_HEAD : VMXNET3_BTYPE_BODY;
	for (i = 0; i < count; i++) {
		rxd[pidx].addr = paddrs[i];
		rxd[pidx].len = len;
		rxd[pidx].btype = btype;
		rxd[pidx].gen = rxr->vxrxr_gen;

		if (++pidx == rxr->vxrxr_ndesc) {
			pidx = 0;
			rxr->vxrxr_gen ^= 1;
		}
	}
}