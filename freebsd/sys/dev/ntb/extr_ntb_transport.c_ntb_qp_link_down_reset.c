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
struct ntb_transport_qp {int link_is_up; unsigned long long qp_num; scalar_t__ rx_err_ver; scalar_t__ rx_err_oflow; scalar_t__ tx_err_no_buf; scalar_t__ rx_err_no_buf; scalar_t__ tx_ring_full; scalar_t__ rx_ring_empty; scalar_t__ rx_pkts; scalar_t__ tx_pkts; scalar_t__ rx_bytes; scalar_t__ tx_bytes; scalar_t__ rx_index; scalar_t__ tx_index; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_db_set_mask (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void
ntb_qp_link_down_reset(struct ntb_transport_qp *qp)
{

	qp->link_is_up = false;
	ntb_db_set_mask(qp->dev, 1ull << qp->qp_num);

	qp->tx_index = qp->rx_index = 0;
	qp->tx_bytes = qp->rx_bytes = 0;
	qp->tx_pkts = qp->rx_pkts = 0;

	qp->rx_ring_empty = 0;
	qp->tx_ring_full = 0;

	qp->rx_err_no_buf = qp->tx_err_no_buf = 0;
	qp->rx_err_oflow = qp->rx_err_ver = 0;
}