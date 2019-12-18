#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_10__ {int dif_oper; int blk_size; int /*<<< orphan*/  disable_app_ref_ffff; int /*<<< orphan*/  disable_app_ffff; int /*<<< orphan*/  dif_separate; int /*<<< orphan*/  check_guard; int /*<<< orphan*/  check_app_tag; int /*<<< orphan*/  check_ref_tag; int /*<<< orphan*/  app_tag; int /*<<< orphan*/  ref_tag; } ;
typedef  TYPE_2__ ocs_scsi_dif_info_t ;
struct TYPE_11__ {scalar_t__ dif; int auto_incr_ref_tag; int /*<<< orphan*/  dif_seed; int /*<<< orphan*/  disable_app_ref_ffff; int /*<<< orphan*/  disable_app_ffff; int /*<<< orphan*/  dif_separate; int /*<<< orphan*/  check_guard; int /*<<< orphan*/  check_app_tag; int /*<<< orphan*/  check_ref_tag; int /*<<< orphan*/  app_tag_cmp; int /*<<< orphan*/  ref_tag_cmp; int /*<<< orphan*/  app_tag_repl; int /*<<< orphan*/  ref_tag_repl; int /*<<< orphan*/  blk_size; int /*<<< orphan*/  dif_oper; } ;
typedef  TYPE_3__ ocs_hw_dif_info_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_1024 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_2048 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_4096 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_4104 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_512 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_520 ; 
 int /*<<< orphan*/  OCS_HW_DIF_BK_SIZE_NA ; 
 int /*<<< orphan*/  OCS_HW_DIF_OPER_DISABLED ; 
 int /*<<< orphan*/  OCS_HW_DIF_SEED ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC ; 
 int /*<<< orphan*/  OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW ; 
#define  OCS_SCSI_DIF_BK_SIZE_1024 142 
#define  OCS_SCSI_DIF_BK_SIZE_2048 141 
#define  OCS_SCSI_DIF_BK_SIZE_4096 140 
#define  OCS_SCSI_DIF_BK_SIZE_4104 139 
#define  OCS_SCSI_DIF_BK_SIZE_512 138 
#define  OCS_SCSI_DIF_BK_SIZE_520 137 
#define  OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CHKSUM 136 
#define  OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CRC 135 
#define  OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_NODIF 134 
#define  OCS_SCSI_DIF_OPER_IN_CRC_OUT_CHKSUM 133 
#define  OCS_SCSI_DIF_OPER_IN_CRC_OUT_CRC 132 
#define  OCS_SCSI_DIF_OPER_IN_CRC_OUT_NODIF 131 
#define  OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CHKSUM 130 
#define  OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CRC 129 
#define  OCS_SCSI_DIF_OPER_IN_RAW_OUT_RAW 128 
 scalar_t__ SLI4_DIF_INSERT ; 
 void* SLI4_DIF_PASS_THROUGH ; 
 void* SLI4_DIF_STRIP ; 
 int /*<<< orphan*/  ocs_hw_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int32_t
ocs_scsi_convert_dif_info(ocs_t *ocs, ocs_scsi_dif_info_t *scsi_dif_info, ocs_hw_dif_info_t *hw_dif_info)
{
	uint32_t dif_seed;
	ocs_memset(hw_dif_info, 0, sizeof(ocs_hw_dif_info_t));

	if (scsi_dif_info == NULL) {
		hw_dif_info->dif_oper = OCS_HW_DIF_OPER_DISABLED;
		hw_dif_info->blk_size =  OCS_HW_DIF_BK_SIZE_NA;
		return 0;
	}

	/* Convert the DIF operation */
	switch(scsi_dif_info->dif_oper) {
	case OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CRC:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC;
		hw_dif_info->dif = SLI4_DIF_INSERT;
		break;
	case OCS_SCSI_DIF_OPER_IN_CRC_OUT_NODIF:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF;
		hw_dif_info->dif = SLI4_DIF_STRIP;
		break;
	case OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CHKSUM:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CHKSUM;
		hw_dif_info->dif = SLI4_DIF_INSERT;
		break;
	case OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_NODIF:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_NODIF;
		hw_dif_info->dif = SLI4_DIF_STRIP;
		break;
	case OCS_SCSI_DIF_OPER_IN_CRC_OUT_CRC:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC;
		hw_dif_info->dif = SLI4_DIF_PASS_THROUGH;
		break;
	case OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CHKSUM:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CHKSUM;
		hw_dif_info->dif = SLI4_DIF_PASS_THROUGH;
		break;
	case OCS_SCSI_DIF_OPER_IN_CRC_OUT_CHKSUM:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM;
		hw_dif_info->dif = SLI4_DIF_PASS_THROUGH;
		break;
	case OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CRC:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC;
		hw_dif_info->dif = SLI4_DIF_PASS_THROUGH;
		break;
	case OCS_SCSI_DIF_OPER_IN_RAW_OUT_RAW:
		hw_dif_info->dif_oper = OCS_HW_SGE_DIF_OP_IN_RAW_OUT_RAW;
		hw_dif_info->dif = SLI4_DIF_PASS_THROUGH;
		break;
	default:
		ocs_log_test(ocs, "unhandled SCSI DIF operation %d\n",
			     scsi_dif_info->dif_oper);
		return -1;
	}

	switch(scsi_dif_info->blk_size) {
	case OCS_SCSI_DIF_BK_SIZE_512:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_512;
		break;
	case OCS_SCSI_DIF_BK_SIZE_1024:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_1024;
		break;
	case OCS_SCSI_DIF_BK_SIZE_2048:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_2048;
		break;
	case OCS_SCSI_DIF_BK_SIZE_4096:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_4096;
		break;
	case OCS_SCSI_DIF_BK_SIZE_520:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_520;
		break;
	case OCS_SCSI_DIF_BK_SIZE_4104:
		hw_dif_info->blk_size = OCS_HW_DIF_BK_SIZE_4104;
		break;
	default:
		ocs_log_test(ocs, "unhandled SCSI DIF block size %d\n",
			     scsi_dif_info->blk_size);
		return -1;
	}

	/* If the operation is an INSERT the tags provided are the ones that should be
	 * inserted, otherwise they're the ones to be checked against. */
	if (hw_dif_info->dif == SLI4_DIF_INSERT ) {
		hw_dif_info->ref_tag_repl = scsi_dif_info->ref_tag;
		hw_dif_info->app_tag_repl = scsi_dif_info->app_tag;
	} else {
		hw_dif_info->ref_tag_cmp = scsi_dif_info->ref_tag;
		hw_dif_info->app_tag_cmp = scsi_dif_info->app_tag;
	}

	hw_dif_info->check_ref_tag = scsi_dif_info->check_ref_tag;
	hw_dif_info->check_app_tag = scsi_dif_info->check_app_tag;
	hw_dif_info->check_guard = scsi_dif_info->check_guard;
	hw_dif_info->auto_incr_ref_tag = 1;
	hw_dif_info->dif_separate = scsi_dif_info->dif_separate;
	hw_dif_info->disable_app_ffff = scsi_dif_info->disable_app_ffff;
	hw_dif_info->disable_app_ref_ffff = scsi_dif_info->disable_app_ref_ffff;

	ocs_hw_get(&ocs->hw, OCS_HW_DIF_SEED, &dif_seed);
	hw_dif_info->dif_seed = dif_seed;

	return 0;
}