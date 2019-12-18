#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_qp {int dummy; } ;
struct qlnxr_dev {int gsi_ll2_handle; TYPE_3__* ha; int /*<<< orphan*/  rdma_ctx; } ;
struct ib_qp_init_attr {int dummy; } ;
struct ecore_ll2_cbs {struct qlnxr_dev* cookie; void* tx_release_cb; int /*<<< orphan*/  rx_release_cb; void* tx_comp_cb; int /*<<< orphan*/  rx_comp_cb; } ;
struct TYPE_6__ {int rx_num_desc; int rx_drop_ttl0_flg; int tx_num_desc; int gsi_enable; void* ai_err_no_buf; void* ai_err_packet_too_big; int /*<<< orphan*/  tx_dest; scalar_t__ tx_tc; scalar_t__ rx_vlan_removal_en; int /*<<< orphan*/  mtu; int /*<<< orphan*/  conn_type; } ;
struct ecore_ll2_acquire_data {int* p_connection_handle; struct ecore_ll2_cbs* cbs; TYPE_2__ input; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_7__ {int /*<<< orphan*/  primary_mac; TYPE_1__* ifp; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_mtu; } ;

/* Variables and functions */
 void* ECORE_LL2_DROP_PACKET ; 
 int /*<<< orphan*/  ECORE_LL2_TX_DEST_NW ; 
 int /*<<< orphan*/  ECORE_LL2_TYPE_ROCE ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_3__*,char*,...) ; 
 int ecore_ll2_acquire_connection (int /*<<< orphan*/ ,struct ecore_ll2_acquire_data*) ; 
 int ecore_ll2_establish_connection (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_ll2_release_connection (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_ll2_terminate_connection (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ecore_ll2_acquire_data*,int /*<<< orphan*/ ,int) ; 
 int qlnx_rdma_ll2_set_mac_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_ll2_complete_rx_packet ; 
 void* qlnxr_ll2_complete_tx_packet ; 
 int /*<<< orphan*/  qlnxr_ll2_release_rx_packet ; 

int qlnxr_ll2_start(struct qlnxr_dev *dev,
		   struct ib_qp_init_attr *attrs,
		   struct qlnxr_qp *qp)
{
	struct ecore_ll2_acquire_data data;
	struct ecore_ll2_cbs cbs;
	int rc;

	QL_DPRINT12(dev->ha, "enter\n");

	/* configure and start LL2 */
	cbs.rx_comp_cb = qlnxr_ll2_complete_rx_packet;
	cbs.tx_comp_cb = qlnxr_ll2_complete_tx_packet;
	cbs.rx_release_cb = qlnxr_ll2_release_rx_packet;
	cbs.tx_release_cb = qlnxr_ll2_complete_tx_packet;
	cbs.cookie = dev;
	dev->gsi_ll2_handle = 0xFF;

	memset(&data, 0, sizeof(data));
	data.input.conn_type = ECORE_LL2_TYPE_ROCE;
	data.input.mtu = dev->ha->ifp->if_mtu;
	data.input.rx_num_desc = 8 * 1024;
	data.input.rx_drop_ttl0_flg = 1;
	data.input.rx_vlan_removal_en = 0;
	data.input.tx_num_desc = 8 * 1024;
	data.input.tx_tc = 0;
	data.input.tx_dest = ECORE_LL2_TX_DEST_NW;
	data.input.ai_err_packet_too_big = ECORE_LL2_DROP_PACKET;
	data.input.ai_err_no_buf = ECORE_LL2_DROP_PACKET;
	data.input.gsi_enable = 1;
	data.p_connection_handle = &dev->gsi_ll2_handle;
	data.cbs = &cbs;

	rc = ecore_ll2_acquire_connection(dev->rdma_ctx, &data);

	if (rc) {
		QL_DPRINT11(dev->ha,
			"ecore_ll2_acquire_connection failed: %d\n",
			rc);
		return rc;
	}

	QL_DPRINT11(dev->ha,
		"ll2 connection acquired successfully\n");
	rc = ecore_ll2_establish_connection(dev->rdma_ctx,
		dev->gsi_ll2_handle);

	if (rc) {
		QL_DPRINT11(dev->ha,
			"ecore_ll2_establish_connection failed\n", rc);
		goto err1;
	}

	QL_DPRINT11(dev->ha,
		"ll2 connection established successfully\n");
	rc = qlnx_rdma_ll2_set_mac_filter(dev->rdma_ctx, NULL,
			dev->ha->primary_mac);
	if (rc) {
		QL_DPRINT11(dev->ha, "qlnx_rdma_ll2_set_mac_filter failed\n", rc);
		goto err2;
	}

	QL_DPRINT12(dev->ha, "exit rc = %d\n", rc);
	return 0;

err2:
	ecore_ll2_terminate_connection(dev->rdma_ctx, dev->gsi_ll2_handle);
err1:
	ecore_ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	QL_DPRINT12(dev->ha, "exit rc = %d\n", rc);
	return rc;
}