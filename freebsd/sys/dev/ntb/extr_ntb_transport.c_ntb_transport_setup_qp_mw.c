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
struct ntb_transport_qp {size_t rx_max_frame; size_t rx_max_entry; scalar_t__ tx_index; scalar_t__ tx_pkts; scalar_t__ rx_pkts; int /*<<< orphan*/ * rx_buff; TYPE_1__* remote_rx_info; scalar_t__ rx_index; } ;
struct ntb_transport_mw {unsigned int rx_size; int /*<<< orphan*/ * virt_addr; } ;
struct ntb_transport_ctx {unsigned int mw_count; unsigned int qp_count; struct ntb_transport_mw* mw_vec; struct ntb_transport_qp* qp_vec; } ;
struct ntb_rx_info {int dummy; } ;
struct ntb_payload_header {int dummy; } ;
typedef  int ntb_q_idx_t ;
struct TYPE_2__ {int entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int QP_TO_MW (struct ntb_transport_ctx*,unsigned int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 size_t qmin (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  transport_mtu ; 

__attribute__((used)) static int
ntb_transport_setup_qp_mw(struct ntb_transport_ctx *nt, unsigned int qp_num)
{
	struct ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	struct ntb_transport_mw *mw;
	void *offset;
	ntb_q_idx_t i;
	size_t rx_size;
	unsigned num_qps_mw, mw_num, mw_count;

	mw_count = nt->mw_count;
	mw_num = QP_TO_MW(nt, qp_num);
	mw = &nt->mw_vec[mw_num];

	if (mw->virt_addr == NULL)
		return (ENOMEM);

	if (mw_num < nt->qp_count % mw_count)
		num_qps_mw = nt->qp_count / mw_count + 1;
	else
		num_qps_mw = nt->qp_count / mw_count;

	rx_size = mw->rx_size / num_qps_mw;
	qp->rx_buff = mw->virt_addr + rx_size * (qp_num / mw_count);
	rx_size -= sizeof(struct ntb_rx_info);

	qp->remote_rx_info = (void*)(qp->rx_buff + rx_size);

	/* Due to house-keeping, there must be at least 2 buffs */
	qp->rx_max_frame = qmin(transport_mtu, rx_size / 2);
	qp->rx_max_entry = rx_size / qp->rx_max_frame;
	qp->rx_index = 0;

	qp->remote_rx_info->entry = qp->rx_max_entry - 1;

	/* Set up the hdr offsets with 0s */
	for (i = 0; i < qp->rx_max_entry; i++) {
		offset = (void *)(qp->rx_buff + qp->rx_max_frame * (i + 1) -
		    sizeof(struct ntb_payload_header));
		memset(offset, 0, sizeof(struct ntb_payload_header));
	}

	qp->rx_pkts = 0;
	qp->tx_pkts = 0;
	qp->tx_index = 0;

	return (0);
}