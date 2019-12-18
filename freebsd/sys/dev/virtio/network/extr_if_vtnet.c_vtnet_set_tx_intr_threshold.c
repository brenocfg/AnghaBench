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
struct vtnet_softc {int vtnet_flags; int vtnet_tx_nsegs; int vtnet_tx_intr_thresh; TYPE_1__* vtnet_txqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  vtntx_vq; } ;

/* Variables and functions */
 int VTNET_FLAG_INDIRECT ; 
 int virtqueue_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtnet_set_tx_intr_threshold(struct vtnet_softc *sc)
{
	int size, thresh;

	size = virtqueue_size(sc->vtnet_txqs[0].vtntx_vq);

	/*
	 * The Tx interrupt is disabled until the queue free count falls
	 * below our threshold. Completed frames are drained from the Tx
	 * virtqueue before transmitting new frames and in the watchdog
	 * callout, so the frequency of Tx interrupts is greatly reduced,
	 * at the cost of not freeing mbufs as quickly as they otherwise
	 * would be.
	 *
	 * N.B. We assume all the Tx queues are the same size.
	 */
	thresh = size / 4;

	/*
	 * Without indirect descriptors, leave enough room for the most
	 * segments we handle.
	 */
	if ((sc->vtnet_flags & VTNET_FLAG_INDIRECT) == 0 &&
	    thresh < sc->vtnet_tx_nsegs)
		thresh = sc->vtnet_tx_nsegs;

	sc->vtnet_tx_intr_thresh = thresh;
}