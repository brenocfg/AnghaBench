#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  blk_size; } ;
typedef  TYPE_1__ ocs_scsi_dif_info_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_1024 ; 
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_2048 ; 
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_4096 ; 
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_4104 ; 
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_512 ; 
 int /*<<< orphan*/  OCS_SCSI_DIF_BK_SIZE_520 ; 

int32_t
ocs_scsi_dif_set_blocksize(ocs_scsi_dif_info_t *dif_info, uint32_t blocksize)
{
	int32_t rc = 0;

	switch(blocksize) {
	case 512:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_512; break;
	case 1024:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_1024; break;
	case 2048:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_2048; break;
	case 4096:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_4096; break;
	case 520:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_520; break;
	case 4104:	dif_info->blk_size = OCS_SCSI_DIF_BK_SIZE_4104; break;
	default:
		rc = -1;
		break;
	}
	return rc;

}