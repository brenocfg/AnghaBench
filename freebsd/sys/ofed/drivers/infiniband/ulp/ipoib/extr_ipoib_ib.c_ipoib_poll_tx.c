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
struct ipoib_dev_priv {int /*<<< orphan*/  dev; struct ib_wc* send_wc; int /*<<< orphan*/  send_cq; } ;
struct ib_wc {int wr_id; } ;

/* Variables and functions */
 int IPOIB_OP_CM ; 
 int MAX_SEND_CQE ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 int /*<<< orphan*/  ipoib_cm_handle_tx_wc (struct ipoib_dev_priv*,struct ib_wc*) ; 
 int /*<<< orphan*/  ipoib_ib_handle_tx_wc (struct ipoib_dev_priv*,struct ib_wc*) ; 
 int /*<<< orphan*/  ipoib_start_locked (int /*<<< orphan*/ ,struct ipoib_dev_priv*) ; 

int
ipoib_poll_tx(struct ipoib_dev_priv *priv, bool do_start)
{
	int n, i;

	n = ib_poll_cq(priv->send_cq, MAX_SEND_CQE, priv->send_wc);
	for (i = 0; i < n; ++i) {
		struct ib_wc *wc = priv->send_wc + i;
		if (wc->wr_id & IPOIB_OP_CM)
			ipoib_cm_handle_tx_wc(priv, wc);
		else
			ipoib_ib_handle_tx_wc(priv, wc);
	}

	if (do_start && n != 0)
		ipoib_start_locked(priv->dev, priv);

	return n == MAX_SEND_CQE;
}