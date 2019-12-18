#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  tctx ;
struct tx_ring {int tx_paddr; } ;
struct rx_ring {scalar_t__ mbuf_sz; int rx_paddr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * qs_handle; } ;
struct ixl_vsi {int num_tx_queues; int num_rx_queues; struct i40e_hw* hw; int /*<<< orphan*/  ctx; scalar_t__ enable_head_writeback; TYPE_7__ info; scalar_t__ hw_filters_del; scalar_t__ hw_filters_add; int /*<<< orphan*/  vsi_num; int /*<<< orphan*/  ifp; int /*<<< orphan*/  seid; struct ixl_rx_queue* rx_queues; struct ixl_tx_queue* tx_queues; struct ixl_pf* back; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
struct ixl_rx_queue {struct rx_ring rxr; } ;
struct TYPE_10__ {int first_qidx; int /*<<< orphan*/  num_allocated; } ;
struct ixl_pf {scalar_t__ veb_seid; scalar_t__ iw_enabled; TYPE_3__ qtag; } ;
struct TYPE_12__ {int* tc_mapping; int /*<<< orphan*/  queueing_opt_flags; int /*<<< orphan*/  valid_sections; int /*<<< orphan*/  port_vlan_flags; scalar_t__* queue_mapping; int /*<<< orphan*/  mapping_flags; int /*<<< orphan*/  up_enable_bits; int /*<<< orphan*/  stat_counter_idx; } ;
struct i40e_vsi_context {scalar_t__ uplink_seid; int pf_num; int dbuff; int hbuff; int dsize; int base; int tphrdesc_ena; int tphwdesc_ena; int lrxqthresh; int crcstrip; int l2tsel; int showiv; int prefena; scalar_t__ fc_ena; scalar_t__ tphhead_ena; scalar_t__ tphdata_ena; int /*<<< orphan*/  qlen; scalar_t__ hsplit_0; scalar_t__ dtype; scalar_t__ rxmax; int /*<<< orphan*/  flags; TYPE_6__ info; int /*<<< orphan*/  vsi_number; int /*<<< orphan*/  vf_num; int /*<<< orphan*/  vsis_unallocated; int /*<<< orphan*/  vsis_allocated; int /*<<< orphan*/  seid; } ;
struct i40e_tx_desc {int dummy; } ;
struct TYPE_8__ {scalar_t__ rx_buf_chain_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {int pf_id; TYPE_1__ func_caps; TYPE_2__ aq; } ;
struct i40e_hmc_obj_txq {int new_context; int base; int qlen; int head_wb_ena; int head_wb_addr; scalar_t__ rdylist_act; int /*<<< orphan*/  rdylist; scalar_t__ fc_ena; } ;
struct i40e_hmc_obj_rxq {scalar_t__ uplink_seid; int pf_num; int dbuff; int hbuff; int dsize; int base; int tphrdesc_ena; int tphwdesc_ena; int lrxqthresh; int crcstrip; int l2tsel; int showiv; int prefena; scalar_t__ fc_ena; scalar_t__ tphhead_ena; scalar_t__ tphdata_ena; int /*<<< orphan*/  qlen; scalar_t__ hsplit_0; scalar_t__ dtype; scalar_t__ rxmax; int /*<<< orphan*/  flags; TYPE_6__ info; int /*<<< orphan*/  vsi_number; int /*<<< orphan*/  vf_num; int /*<<< orphan*/  vsis_unallocated; int /*<<< orphan*/  vsis_allocated; int /*<<< orphan*/  seid; } ;
typedef  TYPE_4__* if_softc_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ctxt ;
struct TYPE_11__ {int* isc_ntxd; scalar_t__ isc_max_frame_size; int /*<<< orphan*/ * isc_nrxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_QUEUE_MAP_VALID ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_QUEUE_OPT_VALID ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_VLAN_VALID ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PVLAN_EMOD_NOTHING ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PVLAN_MODE_ALL ; 
 int /*<<< orphan*/  I40E_AQ_VSI_QUE_MAP_CONTIG ; 
 int /*<<< orphan*/  I40E_AQ_VSI_QUE_OPT_TCP_ENA ; 
 int I40E_AQ_VSI_TC_QUE_NUMBER_MASK ; 
 int I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT ; 
 int I40E_AQ_VSI_TC_QUE_OFFSET_MASK ; 
 int I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT ; 
 int /*<<< orphan*/  I40E_AQ_VSI_TYPE_PF ; 
 int /*<<< orphan*/  I40E_QRX_TAIL (int) ; 
 int /*<<< orphan*/  I40E_QTX_CTL (int) ; 
 int I40E_QTX_CTL_PF_INDX_MASK ; 
 int I40E_QTX_CTL_PF_INDX_SHIFT ; 
 int I40E_QTX_CTL_PF_QUEUE ; 
 int I40E_RXQ_CTX_DBUFF_SHIFT ; 
 int I40E_RXQ_CTX_HBUFF_SHIFT ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int /*<<< orphan*/  IXL_DBG_SWITCH_INFO ; 
 int IXL_RX_CTX_BASE_UNITS ; 
 int IXL_TX_CTX_BASE_UNITS ; 
 int /*<<< orphan*/  bcopy (TYPE_6__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  bzero (struct i40e_hmc_obj_txq*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int fls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int i40e_aq_get_vsi_params (struct i40e_hw*,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int i40e_aq_update_vsi_params (struct i40e_hw*,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int i40e_clear_lan_rx_queue_context (struct i40e_hw*,int) ; 
 int i40e_clear_lan_tx_queue_context (struct i40e_hw*,int) ; 
 int i40e_set_lan_rx_queue_context (struct i40e_hw*,int,struct i40e_vsi_context*) ; 
 int i40e_set_lan_tx_queue_context (struct i40e_hw*,int,struct i40e_hmc_obj_txq*) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ iflib_get_rx_mbuf_sz (int /*<<< orphan*/ ) ; 
 TYPE_4__* iflib_get_softc_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixl_enable_iwarp ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_init_tx_ring (struct ixl_vsi*,struct ixl_tx_queue*) ; 
 int /*<<< orphan*/  ixl_vsi_reset_stats (struct ixl_vsi*) ; 
 int /*<<< orphan*/  memset (struct i40e_vsi_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

int
ixl_initialize_vsi(struct ixl_vsi *vsi)
{
	struct ixl_pf *pf = vsi->back;
	if_softc_ctx_t		scctx = iflib_get_softc_ctx(vsi->ctx);
	struct ixl_tx_queue	*tx_que = vsi->tx_queues;
	struct ixl_rx_queue	*rx_que = vsi->rx_queues;
	device_t		dev = iflib_get_dev(vsi->ctx);
	struct i40e_hw		*hw = vsi->hw;
	struct i40e_vsi_context	ctxt;
	int 			tc_queues;
	int			err = 0;

	memset(&ctxt, 0, sizeof(ctxt));
	ctxt.seid = vsi->seid;
	if (pf->veb_seid != 0)
		ctxt.uplink_seid = pf->veb_seid;
	ctxt.pf_num = hw->pf_id;
	err = i40e_aq_get_vsi_params(hw, &ctxt, NULL);
	if (err) {
		device_printf(dev, "i40e_aq_get_vsi_params() failed, error %d"
		    " aq_error %d\n", err, hw->aq.asq_last_status);
		return (err);
	}
	ixl_dbg(pf, IXL_DBG_SWITCH_INFO,
	    "get_vsi_params: seid: %d, uplinkseid: %d, vsi_number: %d, "
	    "vsis_allocated: %d, vsis_unallocated: %d, flags: 0x%x, "
	    "pfnum: %d, vfnum: %d, stat idx: %d, enabled: %d\n", ctxt.seid,
	    ctxt.uplink_seid, ctxt.vsi_number,
	    ctxt.vsis_allocated, ctxt.vsis_unallocated,
	    ctxt.flags, ctxt.pf_num, ctxt.vf_num,
	    ctxt.info.stat_counter_idx, ctxt.info.up_enable_bits);
	/*
	** Set the queue and traffic class bits
	**  - when multiple traffic classes are supported
	**    this will need to be more robust.
	*/
	ctxt.info.valid_sections = I40E_AQ_VSI_PROP_QUEUE_MAP_VALID;
	ctxt.info.mapping_flags |= I40E_AQ_VSI_QUE_MAP_CONTIG;
	/* In contig mode, que_mapping[0] is first queue index used by this VSI */
	ctxt.info.queue_mapping[0] = 0;
	/*
	 * This VSI will only use traffic class 0; start traffic class 0's
	 * queue allocation at queue 0, and assign it 2^tc_queues queues (though
	 * the driver may not use all of them).
	 */
	tc_queues = fls(pf->qtag.num_allocated) - 1;
	ctxt.info.tc_mapping[0] = ((pf->qtag.first_qidx << I40E_AQ_VSI_TC_QUE_OFFSET_SHIFT)
	    & I40E_AQ_VSI_TC_QUE_OFFSET_MASK) |
	    ((tc_queues << I40E_AQ_VSI_TC_QUE_NUMBER_SHIFT)
	    & I40E_AQ_VSI_TC_QUE_NUMBER_MASK);

	/* Set VLAN receive stripping mode */
	ctxt.info.valid_sections |= I40E_AQ_VSI_PROP_VLAN_VALID;
	ctxt.info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_ALL;
	if (if_getcapenable(vsi->ifp) & IFCAP_VLAN_HWTAGGING)
		ctxt.info.port_vlan_flags |= I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH;
	else
		ctxt.info.port_vlan_flags |= I40E_AQ_VSI_PVLAN_EMOD_NOTHING;

#ifdef IXL_IW
	/* Set TCP Enable for iWARP capable VSI */
	if (ixl_enable_iwarp && pf->iw_enabled) {
		ctxt.info.valid_sections |=
		    htole16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags |= I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	}
#endif
	/* Save VSI number and info for use later */
	vsi->vsi_num = ctxt.vsi_number;
	bcopy(&ctxt.info, &vsi->info, sizeof(vsi->info));

	/* Reset VSI statistics */
	ixl_vsi_reset_stats(vsi);
	vsi->hw_filters_add = 0;
	vsi->hw_filters_del = 0;

	ctxt.flags = htole16(I40E_AQ_VSI_TYPE_PF);

	err = i40e_aq_update_vsi_params(hw, &ctxt, NULL);
	if (err) {
		device_printf(dev, "i40e_aq_update_vsi_params() failed, error %d,"
		    " aq_error %d\n", err, hw->aq.asq_last_status);
		return (err);
	}

	for (int i = 0; i < vsi->num_tx_queues; i++, tx_que++) {
		struct tx_ring		*txr = &tx_que->txr;
		struct i40e_hmc_obj_txq tctx;
		u32			txctl;

		/* Setup the HMC TX Context  */
		bzero(&tctx, sizeof(tctx));
		tctx.new_context = 1;
		tctx.base = (txr->tx_paddr/IXL_TX_CTX_BASE_UNITS);
		tctx.qlen = scctx->isc_ntxd[0];
		tctx.fc_ena = 0;	/* Disable FCoE */
		/*
		 * This value needs to pulled from the VSI that this queue
		 * is assigned to. Index into array is traffic class.
		 */
		tctx.rdylist = vsi->info.qs_handle[0];
		/*
		 * Set these to enable Head Writeback
		 * - Address is last entry in TX ring (reserved for HWB index)
		 * Leave these as 0 for Descriptor Writeback
		 */
		if (vsi->enable_head_writeback) {
			tctx.head_wb_ena = 1;
			tctx.head_wb_addr = txr->tx_paddr +
			    (scctx->isc_ntxd[0] * sizeof(struct i40e_tx_desc));
		} else {
			tctx.head_wb_ena = 0;
			tctx.head_wb_addr = 0; 
		}
		tctx.rdylist_act = 0;
		err = i40e_clear_lan_tx_queue_context(hw, i);
		if (err) {
			device_printf(dev, "Unable to clear TX context\n");
			break;
		}
		err = i40e_set_lan_tx_queue_context(hw, i, &tctx);
		if (err) {
			device_printf(dev, "Unable to set TX context\n");
			break;
		}
		/* Associate the ring with this PF */
		txctl = I40E_QTX_CTL_PF_QUEUE;
		txctl |= ((hw->pf_id << I40E_QTX_CTL_PF_INDX_SHIFT) &
		    I40E_QTX_CTL_PF_INDX_MASK);
		wr32(hw, I40E_QTX_CTL(i), txctl);
		ixl_flush(hw);

		/* Do ring (re)init */
		ixl_init_tx_ring(vsi, tx_que);
	}
	for (int i = 0; i < vsi->num_rx_queues; i++, rx_que++) {
		struct rx_ring 		*rxr = &rx_que->rxr;
		struct i40e_hmc_obj_rxq rctx;

		/* Next setup the HMC RX Context  */
		rxr->mbuf_sz = iflib_get_rx_mbuf_sz(vsi->ctx);

		u16 max_rxmax = rxr->mbuf_sz * hw->func_caps.rx_buf_chain_len;

		/* Set up an RX context for the HMC */
		memset(&rctx, 0, sizeof(struct i40e_hmc_obj_rxq));
		rctx.dbuff = rxr->mbuf_sz >> I40E_RXQ_CTX_DBUFF_SHIFT;
		/* ignore header split for now */
		rctx.hbuff = 0 >> I40E_RXQ_CTX_HBUFF_SHIFT;
		rctx.rxmax = (scctx->isc_max_frame_size < max_rxmax) ?
		    scctx->isc_max_frame_size : max_rxmax;
		rctx.dtype = 0;
		rctx.dsize = 1;		/* do 32byte descriptors */
		rctx.hsplit_0 = 0;	/* no header split */
		rctx.base = (rxr->rx_paddr/IXL_RX_CTX_BASE_UNITS);
		rctx.qlen = scctx->isc_nrxd[0];
		rctx.tphrdesc_ena = 1;
		rctx.tphwdesc_ena = 1;
		rctx.tphdata_ena = 0;	/* Header Split related */
		rctx.tphhead_ena = 0;	/* Header Split related */
		rctx.lrxqthresh = 1;	/* Interrupt at <64 desc avail */
		rctx.crcstrip = 1;
		rctx.l2tsel = 1;
		rctx.showiv = 1;	/* Strip inner VLAN header */
		rctx.fc_ena = 0;	/* Disable FCoE */
		rctx.prefena = 1;	/* Prefetch descriptors */

		err = i40e_clear_lan_rx_queue_context(hw, i);
		if (err) {
			device_printf(dev,
			    "Unable to clear RX context %d\n", i);
			break;
		}
		err = i40e_set_lan_rx_queue_context(hw, i, &rctx);
		if (err) {
			device_printf(dev, "Unable to set RX context %d\n", i);
			break;
		}
		wr32(vsi->hw, I40E_QRX_TAIL(i), 0);
	}
	return (err);
}