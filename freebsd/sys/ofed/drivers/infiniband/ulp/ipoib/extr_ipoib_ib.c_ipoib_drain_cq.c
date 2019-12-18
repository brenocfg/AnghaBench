#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  drain_lock; TYPE_1__* ibwc; int /*<<< orphan*/  recv_cq; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_4__ {scalar_t__ status; int wr_id; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 int IPOIB_NUM_WC ; 
 int IPOIB_OP_CM ; 
 int IPOIB_OP_RECV ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_cm_handle_rx_wc (struct ipoib_dev_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_ib_handle_rx_wc (struct ipoib_dev_priv*,TYPE_1__*) ; 
 scalar_t__ ipoib_poll_tx (struct ipoib_dev_priv*,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ipoib_drain_cq(struct ipoib_dev_priv *priv)
{
	int i, n;

	spin_lock(&priv->drain_lock);
	do {
		n = ib_poll_cq(priv->recv_cq, IPOIB_NUM_WC, priv->ibwc);
		for (i = 0; i < n; ++i) {
			/*
			 * Convert any successful completions to flush
			 * errors to avoid passing packets up the
			 * stack after bringing the device down.
			 */
			if (priv->ibwc[i].status == IB_WC_SUCCESS)
				priv->ibwc[i].status = IB_WC_WR_FLUSH_ERR;

			if ((priv->ibwc[i].wr_id & IPOIB_OP_RECV) == 0)
				panic("ipoib_drain_cq:  Bad wrid 0x%jX\n",
				    (intmax_t)priv->ibwc[i].wr_id);
			if (priv->ibwc[i].wr_id & IPOIB_OP_CM)
				ipoib_cm_handle_rx_wc(priv, priv->ibwc + i);
			else
				ipoib_ib_handle_rx_wc(priv, priv->ibwc + i);
		}
	} while (n == IPOIB_NUM_WC);
	spin_unlock(&priv->drain_lock);

	spin_lock(&priv->lock);
	while (ipoib_poll_tx(priv, true))
		; /* nothing */

	spin_unlock(&priv->lock);
}