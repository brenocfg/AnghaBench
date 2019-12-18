#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int n_io; int n_sgl; int topology; int dif_seed; int dif_mode; int rq_default_buffer_size; int auto_xfer_rdy_xri_cnt; int auto_xfer_rdy_size; int auto_xfer_rdy_blk_size_chip; int auto_xfer_rdy_t10_enable; int auto_xfer_rdy_p_type; int auto_xfer_rdy_ref_tag_is_lba; int auto_xfer_rdy_app_tag_valid; int auto_xfer_rdy_app_tag_value; int esoc; int i_only_aab; int emulate_tgt_wqe_timeout; int bounce; int rq_selection_policy; int rr_quanta; int /*<<< orphan*/  speed; } ;
struct TYPE_10__ {int hw_rq_count; int eth_license; int /*<<< orphan*/  os; TYPE_3__ config; int /*<<< orphan*/  sli; TYPE_1__* cq; TYPE_5__** hw_rq; } ;
typedef  TYPE_4__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_property_e ;
struct TYPE_11__ {TYPE_2__* cq; } ;
typedef  TYPE_5__ hw_rq_t ;
struct TYPE_8__ {size_t instance; } ;
struct TYPE_7__ {int proc_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_LINK_SPEED_10G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_16G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_2G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_32G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_4G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_8G ; 
 int /*<<< orphan*/  FC_LINK_SPEED_AUTO_16_8_4 ; 
#define  OCS_ESOC 157 
#define  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID 156 
#define  OCS_HW_AUTO_XFER_RDY_APP_TAG_VALUE 155 
#define  OCS_HW_AUTO_XFER_RDY_BLK_SIZE 154 
#define  OCS_HW_AUTO_XFER_RDY_P_TYPE 153 
#define  OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA 152 
#define  OCS_HW_AUTO_XFER_RDY_SIZE 151 
#define  OCS_HW_AUTO_XFER_RDY_T10_ENABLE 150 
#define  OCS_HW_AUTO_XFER_RDY_XRI_CNT 149 
#define  OCS_HW_BOUNCE 148 
#define  OCS_HW_DIF_MODE 147 
#define  OCS_HW_DIF_MODE_INLINE 146 
#define  OCS_HW_DIF_MODE_SEPARATE 145 
#define  OCS_HW_DIF_SEED 144 
#define  OCS_HW_EMULATE_I_ONLY_AAB 143 
#define  OCS_HW_EMULATE_TARGET_WQE_TIMEOUT 142 
#define  OCS_HW_ETH_LICENSE 141 
#define  OCS_HW_HIGH_LOGIN_MODE 140 
#define  OCS_HW_LINK_SPEED 139 
#define  OCS_HW_N_IO 138 
#define  OCS_HW_N_SGL 137 
#define  OCS_HW_PREREGISTER_SGL 136 
#define  OCS_HW_RQ_DEFAULT_BUFFER_SIZE 135 
#define  OCS_HW_RQ_PROCESS_LIMIT 134 
#define  OCS_HW_RQ_SELECTION_POLICY 133 
#define  OCS_HW_RR_QUANTA 132 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
#define  OCS_HW_TOPOLOGY 131 
#define  OCS_HW_TOPOLOGY_AUTO 130 
#define  OCS_HW_TOPOLOGY_LOOP 129 
#define  OCS_HW_TOPOLOGY_NPORT 128 
 int /*<<< orphan*/  SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  SLI4_READ_CFG_TOPO_FC ; 
 int /*<<< orphan*/  SLI4_READ_CFG_TOPO_FCOE ; 
 int /*<<< orphan*/  SLI4_READ_CFG_TOPO_FC_AL ; 
 int /*<<< orphan*/  SLI4_READ_CFG_TOPO_FC_DA ; 
 int SLI4_SGE_MAX_RESERVED ; 
 int /*<<< orphan*/  SLI_LINK_MEDIUM_FC ; 
 int /*<<< orphan*/  SLI_RSRC_FCOE_XRI ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sli_get_if_type (int /*<<< orphan*/ *) ; 
 int sli_get_max_rsrc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sli_get_max_sgl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_get_medium (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_is_dif_inline_capable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_is_dif_separate_capable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_set_hlm (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sli_set_sgl_preregister (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sli_set_topology (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_set(ocs_hw_t *hw, ocs_hw_property_e prop, uint32_t value)
{
	ocs_hw_rtn_e		rc = OCS_HW_RTN_SUCCESS;

	switch (prop) {
	case OCS_HW_N_IO:
		if (value > sli_get_max_rsrc(&hw->sli, SLI_RSRC_FCOE_XRI) ||
		    value == 0) {
			ocs_log_test(hw->os, "IO value out of range %d vs %d\n",
					value, sli_get_max_rsrc(&hw->sli, SLI_RSRC_FCOE_XRI));
			rc = OCS_HW_RTN_ERROR;
		} else {
			hw->config.n_io = value;
		}
		break;
	case OCS_HW_N_SGL:
		value += SLI4_SGE_MAX_RESERVED;
		if (value > sli_get_max_sgl(&hw->sli)) {
			ocs_log_test(hw->os, "SGL value out of range %d vs %d\n",
					value, sli_get_max_sgl(&hw->sli));
			rc = OCS_HW_RTN_ERROR;
		} else {
			hw->config.n_sgl = value;
		}
		break;
	case OCS_HW_TOPOLOGY:
		if ((sli_get_medium(&hw->sli) != SLI_LINK_MEDIUM_FC) &&
				(value != OCS_HW_TOPOLOGY_AUTO)) {
			ocs_log_test(hw->os, "unsupported topology=%#x medium=%#x\n",
					value, sli_get_medium(&hw->sli));
			rc = OCS_HW_RTN_ERROR;
			break;
		}

		switch (value) {
		case OCS_HW_TOPOLOGY_AUTO:
			if (sli_get_medium(&hw->sli) == SLI_LINK_MEDIUM_FC) {
				sli_set_topology(&hw->sli, SLI4_READ_CFG_TOPO_FC);
			} else {
				sli_set_topology(&hw->sli, SLI4_READ_CFG_TOPO_FCOE);
			}
			break;
		case OCS_HW_TOPOLOGY_NPORT:
			sli_set_topology(&hw->sli, SLI4_READ_CFG_TOPO_FC_DA);
			break;
		case OCS_HW_TOPOLOGY_LOOP:
			sli_set_topology(&hw->sli, SLI4_READ_CFG_TOPO_FC_AL);
			break;
		default:
			ocs_log_test(hw->os, "unsupported topology %#x\n", value);
			rc = OCS_HW_RTN_ERROR;
		}
		hw->config.topology = value;
		break;
	case OCS_HW_LINK_SPEED:
		if (sli_get_medium(&hw->sli) != SLI_LINK_MEDIUM_FC) {
			switch (value) {
			case 0: 	/* Auto-speed negotiation */
			case 10000:	/* FCoE speed */
				hw->config.speed = FC_LINK_SPEED_10G;
				break;
			default:
				ocs_log_test(hw->os, "unsupported speed=%#x medium=%#x\n",
						value, sli_get_medium(&hw->sli));
				rc = OCS_HW_RTN_ERROR;
			}
			break;
		}

		switch (value) {
		case 0:		/* Auto-speed negotiation */
			hw->config.speed = FC_LINK_SPEED_AUTO_16_8_4;
			break;
		case 2000:	/* FC speeds */
			hw->config.speed = FC_LINK_SPEED_2G;
			break;
		case 4000:
			hw->config.speed = FC_LINK_SPEED_4G;
			break;
		case 8000:
			hw->config.speed = FC_LINK_SPEED_8G;
			break;
		case 16000:
			hw->config.speed = FC_LINK_SPEED_16G;
			break;
		case 32000:
			hw->config.speed = FC_LINK_SPEED_32G;
			break;
		default:
			ocs_log_test(hw->os, "unsupported speed %d\n", value);
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_DIF_SEED:
		/* Set the DIF seed - only for lancer right now */
		if (SLI4_IF_TYPE_LANCER_FC_ETH != sli_get_if_type(&hw->sli)) {
			ocs_log_test(hw->os, "DIF seed not supported for this device\n");
			rc = OCS_HW_RTN_ERROR;
		} else {
			hw->config.dif_seed = value;
		}
		break;
	case OCS_HW_DIF_MODE:
		switch (value) {
		case OCS_HW_DIF_MODE_INLINE:
			/*
			 *  Make sure we support inline DIF.
			 *
			 * Note: Having both bits clear means that we have old
			 *	FW that doesn't set the bits.
			 */
			if (sli_is_dif_inline_capable(&hw->sli)) {
				hw->config.dif_mode = value;
			} else {
				ocs_log_test(hw->os, "chip does not support DIF inline\n");
				rc = OCS_HW_RTN_ERROR;
			}
			break;
		case OCS_HW_DIF_MODE_SEPARATE:
			/* Make sure we support DIF separates. */
			if (sli_is_dif_separate_capable(&hw->sli)) {
				hw->config.dif_mode = value;
			} else {
				ocs_log_test(hw->os, "chip does not support DIF separate\n");
				rc = OCS_HW_RTN_ERROR;
			}
		}
		break;
	case OCS_HW_RQ_PROCESS_LIMIT: {
		hw_rq_t *rq;
		uint32_t i;

		/* For each hw_rq object, set its parent CQ limit value */
		for (i = 0; i < hw->hw_rq_count; i++) {
			rq = hw->hw_rq[i];
			hw->cq[rq->cq->instance].proc_limit = value;
		}
		break;
	}
	case OCS_HW_RQ_DEFAULT_BUFFER_SIZE:
		hw->config.rq_default_buffer_size = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_XRI_CNT:
		hw->config.auto_xfer_rdy_xri_cnt = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_SIZE:
		hw->config.auto_xfer_rdy_size = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_BLK_SIZE:
		switch (value) {
		case 512:
			hw->config.auto_xfer_rdy_blk_size_chip = 0;
			break;
		case 1024:
			hw->config.auto_xfer_rdy_blk_size_chip = 1;
			break;
		case 2048:
			hw->config.auto_xfer_rdy_blk_size_chip = 2;
			break;
		case 4096:
			hw->config.auto_xfer_rdy_blk_size_chip = 3;
			break;
		case 520:
			hw->config.auto_xfer_rdy_blk_size_chip = 4;
			break;
		default:
			ocs_log_err(hw->os, "Invalid block size %d\n",
				    value);
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_AUTO_XFER_RDY_T10_ENABLE:
		hw->config.auto_xfer_rdy_t10_enable = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_P_TYPE:
		hw->config.auto_xfer_rdy_p_type = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_REF_TAG_IS_LBA:
		hw->config.auto_xfer_rdy_ref_tag_is_lba = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_APP_TAG_VALID:
		hw->config.auto_xfer_rdy_app_tag_valid = value;
		break;
	case OCS_HW_AUTO_XFER_RDY_APP_TAG_VALUE:
		hw->config.auto_xfer_rdy_app_tag_value = value;
		break;
	case OCS_ESOC:
		hw->config.esoc = value;
		break;
	case OCS_HW_HIGH_LOGIN_MODE:
		rc = sli_set_hlm(&hw->sli, value);
		break;
	case OCS_HW_PREREGISTER_SGL:
		rc = sli_set_sgl_preregister(&hw->sli, value);
		break;
	case OCS_HW_ETH_LICENSE:
		hw->eth_license = value;
		break;
	case OCS_HW_EMULATE_I_ONLY_AAB:
		hw->config.i_only_aab = value;
		break;
	case OCS_HW_EMULATE_TARGET_WQE_TIMEOUT:
		hw->config.emulate_tgt_wqe_timeout = value;
		break;
	case OCS_HW_BOUNCE:
		hw->config.bounce = value;
		break;
	case OCS_HW_RQ_SELECTION_POLICY:
		hw->config.rq_selection_policy = value;
		break;
	case OCS_HW_RR_QUANTA:
		hw->config.rr_quanta = value;
		break;
	default:
		ocs_log_test(hw->os, "unsupported property %#x\n", prop);
		rc = OCS_HW_RTN_ERROR;
	}

	return rc;
}