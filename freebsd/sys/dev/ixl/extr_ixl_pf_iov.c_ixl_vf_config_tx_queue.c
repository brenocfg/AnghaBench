#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  txq ;
struct virtchnl_txq_info {int dma_ring_addr; int /*<<< orphan*/  queue_id; int /*<<< orphan*/  ring_len; int /*<<< orphan*/  dma_headwb_addr; int /*<<< orphan*/  headwb_enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/ * qs_handle; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct ixl_vf {int vf_num; int /*<<< orphan*/  qtag; TYPE_3__ vsi; } ;
struct TYPE_4__ {int vf_base_id; } ;
struct i40e_hw {int pf_id; TYPE_1__ func_caps; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
struct i40e_hmc_obj_txq {int base; scalar_t__ rdylist_act; int /*<<< orphan*/  rdylist; int /*<<< orphan*/  qlen; int /*<<< orphan*/  head_wb_addr; int /*<<< orphan*/  head_wb_ena; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  DDPRINTF (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  I40E_QTX_CTL (int) ; 
 int I40E_QTX_CTL_PF_INDX_SHIFT ; 
 int I40E_QTX_CTL_VFVM_INDX_SHIFT ; 
 int I40E_QTX_CTL_VF_QUEUE ; 
 int I40E_SUCCESS ; 
 int IXL_TX_CTX_BASE_UNITS ; 
 int /*<<< orphan*/  bzero (struct i40e_hmc_obj_txq*,int) ; 
 int i40e_clear_lan_tx_queue_context (struct i40e_hw*,int) ; 
 int i40e_set_lan_tx_queue_context (struct i40e_hw*,int,struct i40e_hmc_obj_txq*) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_pf_qidx_from_vsi_qidx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_mark_queue_configured (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ixl_vf_config_tx_queue(struct ixl_pf *pf, struct ixl_vf *vf,
    struct virtchnl_txq_info *info)
{
	struct i40e_hw *hw;
	struct i40e_hmc_obj_txq txq;
	uint16_t global_queue_num, global_vf_num;
	enum i40e_status_code status;
	uint32_t qtx_ctl;

	hw = &pf->hw;
	global_queue_num = ixl_pf_qidx_from_vsi_qidx(&vf->qtag, info->queue_id);
	global_vf_num = hw->func_caps.vf_base_id + vf->vf_num;
	bzero(&txq, sizeof(txq));

	DDPRINTF(pf->dev, "VF %d: PF TX queue %d / VF TX queue %d (Global VF %d)\n",
	    vf->vf_num, global_queue_num, info->queue_id, global_vf_num);

	status = i40e_clear_lan_tx_queue_context(hw, global_queue_num);
	if (status != I40E_SUCCESS)
		return (EINVAL);

	txq.base = info->dma_ring_addr / IXL_TX_CTX_BASE_UNITS;

	txq.head_wb_ena = info->headwb_enabled;
	txq.head_wb_addr = info->dma_headwb_addr;
	txq.qlen = info->ring_len;
	txq.rdylist = le16_to_cpu(vf->vsi.info.qs_handle[0]);
	txq.rdylist_act = 0;

	status = i40e_set_lan_tx_queue_context(hw, global_queue_num, &txq);
	if (status != I40E_SUCCESS)
		return (EINVAL);

	qtx_ctl = I40E_QTX_CTL_VF_QUEUE |
	    (hw->pf_id << I40E_QTX_CTL_PF_INDX_SHIFT) |
	    (global_vf_num << I40E_QTX_CTL_VFVM_INDX_SHIFT);
	wr32(hw, I40E_QTX_CTL(global_queue_num), qtx_ctl);
	ixl_flush(hw);

	ixl_pf_qmgr_mark_queue_configured(&vf->qtag, info->queue_id, true);

	return (0);
}