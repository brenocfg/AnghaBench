#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_3__ sli4_sge_t ;
struct TYPE_15__ {void* dif_op_tx; void* dif_op_rx; int /*<<< orphan*/  new_ref_tag; int /*<<< orphan*/  check_crc; int /*<<< orphan*/  check_ref_tag; int /*<<< orphan*/  check_app_tag; int /*<<< orphan*/  auto_incr_ref_tag; int /*<<< orphan*/  dif_blk_size; int /*<<< orphan*/  app_tag_cmp; int /*<<< orphan*/  sge_type; int /*<<< orphan*/  at; int /*<<< orphan*/  atrt; int /*<<< orphan*/  repl_app_tag; int /*<<< orphan*/  app_tag_repl; int /*<<< orphan*/  ref_tag_repl; int /*<<< orphan*/  ref_tag_cmp; } ;
typedef  TYPE_4__ sli4_diseed_sge_t ;
struct TYPE_13__ {scalar_t__ if_type; } ;
struct TYPE_16__ {int /*<<< orphan*/ * os; TYPE_2__ sli; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_17__ {scalar_t__ type; scalar_t__ n_sge; TYPE_1__* sgl; } ;
typedef  TYPE_6__ ocs_hw_io_t ;
struct TYPE_18__ {int dif_oper; int /*<<< orphan*/  repl_ref_tag; int /*<<< orphan*/  check_guard; int /*<<< orphan*/  check_ref_tag; int /*<<< orphan*/  check_app_tag; int /*<<< orphan*/  auto_incr_ref_tag; int /*<<< orphan*/  blk_size; int /*<<< orphan*/  app_tag_cmp; scalar_t__ dif_separate; int /*<<< orphan*/  disable_app_ffff; int /*<<< orphan*/  disable_app_ref_ffff; int /*<<< orphan*/  repl_app_tag; int /*<<< orphan*/  app_tag_repl; int /*<<< orphan*/  ref_tag_repl; int /*<<< orphan*/  ref_tag_cmp; } ;
typedef  TYPE_7__ ocs_hw_dif_info_t ;
struct TYPE_12__ {TYPE_3__* virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int OCS_HW_DIF_OPER_DISABLED ; 
 scalar_t__ OCS_HW_IO_INITIATOR_READ ; 
 scalar_t__ OCS_HW_IO_TARGET_WRITE ; 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
#define  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM 136 
#define  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC 135 
#define  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF 134 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM 133 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC 132 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF 131 
#define  OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM 130 
#define  OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC 129 
#define  OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW 128 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 void* SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM ; 
 void* SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CRC ; 
 void* SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF ; 
 void* SLI4_SGE_DIF_OP_IN_CRC_OUT_CHKSUM ; 
 void* SLI4_SGE_DIF_OP_IN_CRC_OUT_CRC ; 
 void* SLI4_SGE_DIF_OP_IN_CRC_OUT_NODIF ; 
 void* SLI4_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM ; 
 void* SLI4_SGE_DIF_OP_IN_NODIF_OUT_CRC ; 
 void* SLI4_SGE_DIF_OP_IN_RAW_OUT_RAW ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_DISEED ; 
 int /*<<< orphan*/  SLI4_SGE_TYPE_SKIP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

ocs_hw_rtn_e
ocs_hw_io_add_seed_sge(ocs_hw_t *hw, ocs_hw_io_t *io, ocs_hw_dif_info_t *dif_info)
{
	sli4_sge_t	*data = NULL;
	sli4_diseed_sge_t *dif_seed;

	/* If no dif_info, or dif_oper is disabled, then just return success */
	if ((dif_info == NULL) || (dif_info->dif_oper == OCS_HW_DIF_OPER_DISABLED)) {
		return OCS_HW_RTN_SUCCESS;
	}

	if (!hw || !io) {
		ocs_log_err(hw ? hw->os : NULL, "bad parameter hw=%p io=%p dif_info=%p\n",
			    hw, io, dif_info);
		return OCS_HW_RTN_ERROR;
	}

	data = io->sgl->virt;
	data += io->n_sge;

	/* If we are doing T10 DIF add the DIF Seed SGE */
	ocs_memset(data, 0, sizeof(sli4_diseed_sge_t));
	dif_seed = (sli4_diseed_sge_t *)data;
	dif_seed->ref_tag_cmp = dif_info->ref_tag_cmp;
	dif_seed->ref_tag_repl = dif_info->ref_tag_repl;
	dif_seed->app_tag_repl = dif_info->app_tag_repl;
	dif_seed->repl_app_tag = dif_info->repl_app_tag;
	if (SLI4_IF_TYPE_LANCER_FC_ETH != hw->sli.if_type) {
		dif_seed->atrt = dif_info->disable_app_ref_ffff;
		dif_seed->at = dif_info->disable_app_ffff;
	}
	dif_seed->sge_type = SLI4_SGE_TYPE_DISEED;
	/* Workaround for SKH (BZ157233) */
	if (((io->type == OCS_HW_IO_TARGET_WRITE) || (io->type == OCS_HW_IO_INITIATOR_READ)) &&
		(SLI4_IF_TYPE_LANCER_FC_ETH != hw->sli.if_type) && dif_info->dif_separate) {
		dif_seed->sge_type = SLI4_SGE_TYPE_SKIP;
	}

	dif_seed->app_tag_cmp = dif_info->app_tag_cmp;
	dif_seed->dif_blk_size = dif_info->blk_size;
	dif_seed->auto_incr_ref_tag = dif_info->auto_incr_ref_tag;
	dif_seed->check_app_tag = dif_info->check_app_tag;
	dif_seed->check_ref_tag = dif_info->check_ref_tag;
	dif_seed->check_crc = dif_info->check_guard;
	dif_seed->new_ref_tag = dif_info->repl_ref_tag;

	switch(dif_info->dif_oper) {
	case OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_NODIF_OUT_CRC;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_NODIF_OUT_CRC;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CRC_OUT_NODIF;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CRC_OUT_NODIF;
		break;
	case OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CRC_OUT_CRC;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CRC_OUT_CRC;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CRC_OUT_CHKSUM;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CRC_OUT_CHKSUM;
		break;
	case OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CRC;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_CHKSUM_OUT_CRC;
		break;
	case OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW:
		dif_seed->dif_op_rx = SLI4_SGE_DIF_OP_IN_RAW_OUT_RAW;
		dif_seed->dif_op_tx = SLI4_SGE_DIF_OP_IN_RAW_OUT_RAW;
		break;
	default:
		ocs_log_err(hw->os, "unsupported DIF operation %#x\n",
			    dif_info->dif_oper);
		return OCS_HW_RTN_ERROR;
	}

	/*
	 * Set last, clear previous last
	 */
	data->last = TRUE;
	if (io->n_sge) {
		data[-1].last = FALSE;
	}

	io->n_sge++;

	return OCS_HW_RTN_SUCCESS;
}