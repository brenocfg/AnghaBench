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
struct vtnet_txq {struct virtqueue* vtntx_vq; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {scalar_t__ vtnet_tx_intr_thresh; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 scalar_t__ virtqueue_nfree (struct virtqueue*) ; 

__attribute__((used)) static int
vtnet_txq_below_threshold(struct vtnet_txq *txq)
{
	struct vtnet_softc *sc;
	struct virtqueue *vq;

	sc = txq->vtntx_sc;
	vq = txq->vtntx_vq;

	return (virtqueue_nfree(vq) <= sc->vtnet_tx_intr_thresh);
}