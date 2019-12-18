#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int ooo_num_rx_bufs; } ;
struct ecore_rdma_start_in_params {int max_mtu; TYPE_2__ iwarp; int /*<<< orphan*/  mac_addr; } ;
struct ecore_ll2_cbs {int /*<<< orphan*/  slowpath_cb; int /*<<< orphan*/  rx_comp_cb; struct ecore_hwfn* cookie; int /*<<< orphan*/  tx_release_cb; int /*<<< orphan*/  tx_comp_cb; int /*<<< orphan*/  rx_release_cb; } ;
struct TYPE_8__ {int mtu; int rx_num_desc; int tx_num_desc; int tx_max_bds_per_packet; int rx_num_ooo_buffers; int secondary_queue; void* conn_type; int /*<<< orphan*/  tx_dest; int /*<<< orphan*/  tx_tc; } ;
struct ecore_ll2_acquire_data {TYPE_4__ input; struct ecore_ll2_cbs* cbs; void** p_connection_handle; } ;
struct ecore_iwarp_info {int max_mtu; int num_ooo_rx_bufs; int max_num_partial_fpdus; int /*<<< orphan*/  mpa_buf_list; TYPE_1__* mpa_bufs; int /*<<< orphan*/  mpa_buf_pending_list; void* mpa_intermediate_buf; void* partial_fpdus; void* ll2_mpa_handle; void* ll2_ooo_handle; void* ll2_syn_handle; int /*<<< orphan*/  mac_addr; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_3__* p_rdma_info; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_7__ {scalar_t__ num_qps; struct ecore_iwarp_info iwarp; } ;
struct TYPE_5__ {int /*<<< orphan*/  list_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 void* ECORE_IWARP_HANDLE_INVAL ; 
 int ECORE_IWARP_LL2_OOO_DEF_TX_SIZE ; 
 int ECORE_IWARP_LL2_OOO_MAX_RX_SIZE ; 
 int ECORE_IWARP_LL2_SYN_RX_SIZE ; 
 int ECORE_IWARP_LL2_SYN_TX_SIZE ; 
 int ECORE_IWARP_MAX_BDS_PER_FPDU ; 
 int ECORE_IWARP_MAX_BUF_SIZE (int) ; 
 int ECORE_IWARP_MAX_SYN_PKT_SIZE ; 
 int /*<<< orphan*/  ECORE_LL2_TX_DEST_LB ; 
 void* ECORE_LL2_TYPE_IWARP ; 
 void* ECORE_LL2_TYPE_OOO ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OSAL_LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_ll2_acquire_data*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PKT_LB_TC ; 
 int ecore_iwarp_ll2_alloc_buffers (struct ecore_hwfn*,int,int,void*) ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_comp_mpa_pkt ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_comp_syn_pkt ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_comp_tx_pkt ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_rel_rx_pkt ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_rel_tx_pkt ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_slowpath ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_stop (struct ecore_hwfn*) ; 
 int ecore_ll2_acquire_connection (struct ecore_hwfn*,struct ecore_ll2_acquire_data*) ; 
 int ecore_ll2_establish_connection (struct ecore_hwfn*,void*) ; 
 int ecore_llh_add_mac_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_llh_remove_mac_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ecore_iwarp_ll2_start(struct ecore_hwfn *p_hwfn,
		      struct ecore_rdma_start_in_params *params)
{
	struct ecore_iwarp_info *iwarp_info;
	struct ecore_ll2_acquire_data data;
	struct ecore_ll2_cbs cbs;
	u32 mpa_buff_size;
	int rc = ECORE_SUCCESS;
	u16 n_ooo_bufs;
	int i;

	iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	iwarp_info->ll2_syn_handle = ECORE_IWARP_HANDLE_INVAL;
	iwarp_info->ll2_ooo_handle = ECORE_IWARP_HANDLE_INVAL;
	iwarp_info->ll2_mpa_handle = ECORE_IWARP_HANDLE_INVAL;

	iwarp_info->max_mtu = params->max_mtu;

	OSAL_MEMCPY(p_hwfn->p_rdma_info->iwarp.mac_addr, params->mac_addr,
		    ETH_ALEN);

	rc = ecore_llh_add_mac_filter(p_hwfn->p_dev, 0, params->mac_addr);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Start SYN connection */
	cbs.rx_comp_cb = ecore_iwarp_ll2_comp_syn_pkt;
	cbs.rx_release_cb = ecore_iwarp_ll2_rel_rx_pkt;
	cbs.tx_comp_cb = ecore_iwarp_ll2_comp_tx_pkt;
	cbs.tx_release_cb = ecore_iwarp_ll2_rel_tx_pkt;
	cbs.cookie = p_hwfn;

	OSAL_MEMSET(&data, 0, sizeof(data));
	data.input.conn_type = ECORE_LL2_TYPE_IWARP;
	data.input.mtu = ECORE_IWARP_MAX_SYN_PKT_SIZE;
	data.input.rx_num_desc = ECORE_IWARP_LL2_SYN_RX_SIZE;
	data.input.tx_num_desc = ECORE_IWARP_LL2_SYN_TX_SIZE;
	data.input.tx_max_bds_per_packet = 1; /* will never be fragmented */
	data.input.tx_tc = PKT_LB_TC;
	data.input.tx_dest = ECORE_LL2_TX_DEST_LB;
	data.p_connection_handle = &iwarp_info->ll2_syn_handle;
	data.cbs = &cbs;

	rc = ecore_ll2_acquire_connection(p_hwfn, &data);
	if (rc) {
		DP_NOTICE(p_hwfn, false, "Failed to acquire LL2 connection\n");
		ecore_llh_remove_mac_filter(p_hwfn->p_dev, 0, params->mac_addr);
		return rc;
	}

	rc = ecore_ll2_establish_connection(p_hwfn, iwarp_info->ll2_syn_handle);
	if (rc) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to establish LL2 connection\n");
		goto err;
	}

	rc = ecore_iwarp_ll2_alloc_buffers(p_hwfn,
					   ECORE_IWARP_LL2_SYN_RX_SIZE,
					   ECORE_IWARP_MAX_SYN_PKT_SIZE,
					   iwarp_info->ll2_syn_handle);
	if (rc)
		goto err;

	/* Start OOO connection */
	data.input.conn_type = ECORE_LL2_TYPE_OOO;
	data.input.mtu = params->max_mtu;

	n_ooo_bufs = params->iwarp.ooo_num_rx_bufs;

	if (n_ooo_bufs > ECORE_IWARP_LL2_OOO_MAX_RX_SIZE)
		n_ooo_bufs = ECORE_IWARP_LL2_OOO_MAX_RX_SIZE;

	data.input.rx_num_desc = n_ooo_bufs;
	data.input.rx_num_ooo_buffers = n_ooo_bufs;

	p_hwfn->p_rdma_info->iwarp.num_ooo_rx_bufs = data.input.rx_num_desc;
	data.input.tx_max_bds_per_packet = 1; /* will never be fragmented */
	data.input.tx_num_desc = ECORE_IWARP_LL2_OOO_DEF_TX_SIZE;
	data.p_connection_handle = &iwarp_info->ll2_ooo_handle;
	data.input.secondary_queue = true;

	rc = ecore_ll2_acquire_connection(p_hwfn, &data);
	if (rc)
		goto err;

	rc = ecore_ll2_establish_connection(p_hwfn, iwarp_info->ll2_ooo_handle);
	if (rc)
		goto err;

	/* Start MPA connection */
	cbs.rx_comp_cb = ecore_iwarp_ll2_comp_mpa_pkt;
	cbs.slowpath_cb = ecore_iwarp_ll2_slowpath;

	OSAL_MEMSET(&data, 0, sizeof(data));
	data.input.conn_type = ECORE_LL2_TYPE_IWARP;
	data.input.mtu = params->max_mtu;
	data.input.rx_num_desc = n_ooo_bufs * 2;
	/* we allocate the same amount for TX to reduce the chance we
	 * run out of tx descriptors
	 */
	data.input.tx_num_desc = data.input.rx_num_desc;
	data.input.tx_max_bds_per_packet = ECORE_IWARP_MAX_BDS_PER_FPDU;
	data.p_connection_handle = &iwarp_info->ll2_mpa_handle;
	data.input.secondary_queue = true;
	data.cbs = &cbs;

	rc = ecore_ll2_acquire_connection(p_hwfn, &data);
	if (rc)
		goto err;

	rc = ecore_ll2_establish_connection(p_hwfn, iwarp_info->ll2_mpa_handle);
	if (rc)
		goto err;

	mpa_buff_size = ECORE_IWARP_MAX_BUF_SIZE(params->max_mtu);
	rc = ecore_iwarp_ll2_alloc_buffers(p_hwfn,
					   data.input.rx_num_desc,
					   mpa_buff_size,
					   iwarp_info->ll2_mpa_handle);
	if (rc)
		goto err;

	iwarp_info->partial_fpdus =
		OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
			    sizeof(*iwarp_info->partial_fpdus) *
			    (u16)p_hwfn->p_rdma_info->num_qps);

	if (!iwarp_info->partial_fpdus) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate ecore_iwarp_info(partial_fpdus)\n");
		goto err;
	}

	iwarp_info->max_num_partial_fpdus = (u16)p_hwfn->p_rdma_info->num_qps;

	/* The mpa_bufs array serves for pending RX packets received on the
	 * mpa ll2 that don't have place on the tx ring and require later
	 * processing. We can't fail on allocation of such a struct therefore
	 * we allocate enough to take care of all rx packets
	 */
	iwarp_info->mpa_bufs =
		OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
			    sizeof(*iwarp_info->mpa_bufs) *
				   data.input.rx_num_desc);

	if (!iwarp_info->mpa_bufs) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate mpa_bufs array mem_size=%d\n",
			  (u32)(sizeof(*iwarp_info->mpa_bufs) *
				data.input.rx_num_desc));
		goto err;
	}

	iwarp_info->mpa_intermediate_buf =
		OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, mpa_buff_size);
	if (!iwarp_info->mpa_intermediate_buf) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate mpa_intermediate_buf mem_size=%d\n",
			  mpa_buff_size);
		goto err;
	}

	OSAL_LIST_INIT(&iwarp_info->mpa_buf_pending_list);
	OSAL_LIST_INIT(&iwarp_info->mpa_buf_list);
	for (i = 0; i < data.input.rx_num_desc; i++) {
		OSAL_LIST_PUSH_TAIL(&iwarp_info->mpa_bufs[i].list_entry,
				    &iwarp_info->mpa_buf_list);
	}

	return rc;

err:
	ecore_iwarp_ll2_stop(p_hwfn);

	return rc;
}