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
typedef  int /*<<< orphan*/  uint16_t ;
struct virtchnl_rxq_info {int databuffer_size; scalar_t__ max_pkt_size; int hdr_size; int rx_split_pos; int dma_ring_addr; int /*<<< orphan*/  queue_id; int /*<<< orphan*/  ring_len; scalar_t__ splithdr_enabled; } ;
struct ixl_vf {int /*<<< orphan*/  qtag; int /*<<< orphan*/  vf_num; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
struct i40e_hmc_obj_rxq {int hsplit_0; int hbuff; int dtype; int base; int dbuff; int dsize; int crcstrip; int l2tsel; scalar_t__ rxmax; int tphrdesc_ena; int tphwdesc_ena; int tphdata_ena; int tphhead_ena; int lrxqthresh; int prefena; int /*<<< orphan*/  qlen; } ;
typedef  int /*<<< orphan*/  rxq ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ ETHER_MIN_LEN ; 
 int I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_IP ; 
 int I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_L2 ; 
 int I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_SCTP ; 
 int I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_TCP_UDP ; 
 int I40E_RXQ_CTX_DBUFF_SHIFT ; 
 int I40E_RXQ_CTX_HBUFF_SHIFT ; 
 int I40E_SUCCESS ; 
 int IXL_RX_CTX_BASE_UNITS ; 
 int IXL_VF_MAX_BUFFER ; 
 scalar_t__ IXL_VF_MAX_FRAME ; 
 int IXL_VF_MAX_HDR_BUFFER ; 
 int /*<<< orphan*/  bzero (struct i40e_hmc_obj_rxq*,int) ; 
 int i40e_clear_lan_rx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int i40e_set_lan_rx_queue_context (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_hmc_obj_rxq*) ; 
 int /*<<< orphan*/  ixl_pf_qidx_from_vsi_qidx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_mark_queue_configured (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixl_vf_config_rx_queue(struct ixl_pf *pf, struct ixl_vf *vf,
    struct virtchnl_rxq_info *info)
{
	struct i40e_hw *hw;
	struct i40e_hmc_obj_rxq rxq;
	uint16_t global_queue_num;
	enum i40e_status_code status;

	hw = &pf->hw;
	global_queue_num = ixl_pf_qidx_from_vsi_qidx(&vf->qtag, info->queue_id);
	bzero(&rxq, sizeof(rxq));

	DDPRINTF(pf->dev, "VF %d: PF RX queue %d / VF RX queue %d\n",
	    vf->vf_num, global_queue_num, info->queue_id);

	if (info->databuffer_size > IXL_VF_MAX_BUFFER)
		return (EINVAL);

	if (info->max_pkt_size > IXL_VF_MAX_FRAME ||
	    info->max_pkt_size < ETHER_MIN_LEN)
		return (EINVAL);

	if (info->splithdr_enabled) {
		if (info->hdr_size > IXL_VF_MAX_HDR_BUFFER)
			return (EINVAL);

		rxq.hsplit_0 = info->rx_split_pos &
		    (I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_L2 |
		     I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_IP |
		     I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_TCP_UDP |
		     I40E_HMC_OBJ_RX_HSPLIT_0_SPLIT_SCTP);
		rxq.hbuff = info->hdr_size >> I40E_RXQ_CTX_HBUFF_SHIFT;

		rxq.dtype = 2;
	}

	status = i40e_clear_lan_rx_queue_context(hw, global_queue_num);
	if (status != I40E_SUCCESS)
		return (EINVAL);

	rxq.base = info->dma_ring_addr / IXL_RX_CTX_BASE_UNITS;
	rxq.qlen = info->ring_len;

	rxq.dbuff = info->databuffer_size >> I40E_RXQ_CTX_DBUFF_SHIFT;

	rxq.dsize = 1;
	rxq.crcstrip = 1;
	rxq.l2tsel = 1;

	rxq.rxmax = info->max_pkt_size;
	rxq.tphrdesc_ena = 1;
	rxq.tphwdesc_ena = 1;
	rxq.tphdata_ena = 1;
	rxq.tphhead_ena = 1;
	rxq.lrxqthresh = 1;
	rxq.prefena = 1;

	status = i40e_set_lan_rx_queue_context(hw, global_queue_num, &rxq);
	if (status != I40E_SUCCESS)
		return (EINVAL);

	ixl_pf_qmgr_mark_queue_configured(&vf->qtag, info->queue_id, false);

	return (0);
}