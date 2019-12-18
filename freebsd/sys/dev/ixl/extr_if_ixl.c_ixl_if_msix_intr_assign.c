#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {int num_rx_queues; struct ixl_tx_queue* rx_queues; int /*<<< orphan*/  irq; TYPE_3__* shared; struct ixl_tx_queue* tx_queues; } ;
struct TYPE_5__ {int /*<<< orphan*/  me; } ;
struct TYPE_4__ {int /*<<< orphan*/  me; } ;
struct ixl_tx_queue {int msix; int /*<<< orphan*/  que_irq; TYPE_2__ txr; TYPE_1__ rxr; struct ixl_vsi vsi; } ;
struct ixl_rx_queue {int msix; int /*<<< orphan*/  que_irq; TYPE_2__ txr; TYPE_1__ rxr; struct ixl_vsi vsi; } ;
struct ixl_pf {int msix; int /*<<< orphan*/  que_irq; TYPE_2__ txr; TYPE_1__ rxr; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int isc_nrxqsets; int isc_ntxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFLIB_INTR_ADMIN ; 
 int /*<<< orphan*/  IFLIB_INTR_IOV ; 
 int /*<<< orphan*/  IFLIB_INTR_RX ; 
 int /*<<< orphan*/  IFLIB_INTR_TX ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ixl_tx_queue* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_irq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ixl_tx_queue*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_softirq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ixl_tx_queue*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixl_msix_adminq ; 
 int /*<<< orphan*/  ixl_msix_que ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
ixl_if_msix_intr_assign(if_ctx_t ctx, int msix)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct ixl_rx_queue *rx_que = vsi->rx_queues;
	struct ixl_tx_queue *tx_que = vsi->tx_queues;
	int err, i, rid, vector = 0;
	char buf[16];

	MPASS(vsi->shared->isc_nrxqsets > 0);
	MPASS(vsi->shared->isc_ntxqsets > 0);

	/* Admin Que must use vector 0*/
	rid = vector + 1;
	err = iflib_irq_alloc_generic(ctx, &vsi->irq, rid, IFLIB_INTR_ADMIN,
	    ixl_msix_adminq, pf, 0, "aq");
	if (err) {
		iflib_irq_free(ctx, &vsi->irq);
		device_printf(iflib_get_dev(ctx),
		    "Failed to register Admin Que handler");
		return (err);
	}
	/* Create soft IRQ for handling VFLRs */
	iflib_softirq_alloc_generic(ctx, NULL, IFLIB_INTR_IOV, pf, 0, "iov");

	/* Now set up the stations */
	for (i = 0, vector = 1; i < vsi->shared->isc_nrxqsets; i++, vector++, rx_que++) {
		rid = vector + 1;

		snprintf(buf, sizeof(buf), "rxq%d", i);
		err = iflib_irq_alloc_generic(ctx, &rx_que->que_irq, rid,
		    IFLIB_INTR_RX, ixl_msix_que, rx_que, rx_que->rxr.me, buf);
		/* XXX: Does the driver work as expected if there are fewer num_rx_queues than
		 * what's expected in the iflib context? */
		if (err) {
			device_printf(iflib_get_dev(ctx),
			    "Failed to allocate queue RX int vector %d, err: %d\n", i, err);
			vsi->num_rx_queues = i + 1;
			goto fail;
		}
		rx_que->msix = vector;
	}

	bzero(buf, sizeof(buf));

	for (i = 0; i < vsi->shared->isc_ntxqsets; i++, tx_que++) {
		snprintf(buf, sizeof(buf), "txq%d", i);
		iflib_softirq_alloc_generic(ctx,
		    &vsi->rx_queues[i % vsi->shared->isc_nrxqsets].que_irq,
		    IFLIB_INTR_TX, tx_que, tx_que->txr.me, buf);

		/* TODO: Maybe call a strategy function for this to figure out which
		* interrupts to map Tx queues to. I don't know if there's an immediately
		* better way than this other than a user-supplied map, though. */
		tx_que->msix = (i % vsi->shared->isc_nrxqsets) + 1;
	}

	return (0);
fail:
	iflib_irq_free(ctx, &vsi->irq);
	rx_que = vsi->rx_queues;
	for (int i = 0; i < vsi->num_rx_queues; i++, rx_que++)
		iflib_irq_free(ctx, &rx_que->que_irq);
	return (err);
}