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
struct vtnet_txq {int /*<<< orphan*/  vtntx_watchdog; struct virtqueue* vtntx_vq; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTNET_TX_TIMEOUT ; 
 int /*<<< orphan*/  virtqueue_disable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 
 scalar_t__ vtnet_txq_below_threshold (struct vtnet_txq*) ; 
 scalar_t__ vtnet_txq_enable_intr (struct vtnet_txq*) ; 
 scalar_t__ vtnet_txq_eof (struct vtnet_txq*) ; 

__attribute__((used)) static int
vtnet_txq_notify(struct vtnet_txq *txq)
{
	struct virtqueue *vq;

	vq = txq->vtntx_vq;

	txq->vtntx_watchdog = VTNET_TX_TIMEOUT;
	virtqueue_notify(vq);

	if (vtnet_txq_enable_intr(txq) == 0)
		return (0);

	/*
	 * Drain frames that were completed since last checked. If this
	 * causes the queue to go above the threshold, the caller should
	 * continue transmitting.
	 */
	if (vtnet_txq_eof(txq) != 0 && vtnet_txq_below_threshold(txq) == 0) {
		virtqueue_disable_intr(vq);
		return (1);
	}

	return (0);
}