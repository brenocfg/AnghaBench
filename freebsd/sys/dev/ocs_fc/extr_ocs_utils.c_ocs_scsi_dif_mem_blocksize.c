#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {size_t dif_oper; } ;
typedef  TYPE_1__ ocs_scsi_dif_info_t ;
typedef  int int32_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ DIF_SIZE ; 
 int /*<<< orphan*/  ocs_assert (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_scsi_dif_blocksize (TYPE_1__*) ; 

int32_t
ocs_scsi_dif_mem_blocksize(ocs_scsi_dif_info_t *dif_info, int wiretomem)
{
	uint32_t blocksize;
	uint8_t wiretomem_adj[] = {
		0,		/* OCS_SCSI_DIF_OPER_DISABLED, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CRC, */
		0,		/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_NODIF, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CHKSUM, */
		0,		/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_NODIF, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_CRC, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CHKSUM, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_CHKSUM, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CRC, */
		DIF_SIZE};	/* OCS_SCSI_DIF_OPER_IN_RAW_OUT_RAW, */
	uint8_t memtowire_adj[] = {
		0,		/* OCS_SCSI_DIF_OPER_DISABLED, */
		0,		/* OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CRC, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_NODIF, */
		0,		/* OCS_SCSI_DIF_OPER_IN_NODIF_OUT_CHKSUM, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_NODIF, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_CRC, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CHKSUM, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CRC_OUT_CHKSUM, */
		DIF_SIZE,	/* OCS_SCSI_DIF_OPER_IN_CHKSUM_OUT_CRC, */
		DIF_SIZE};	/* OCS_SCSI_DIF_OPER_IN_RAW_OUT_RAW, */

	blocksize = ocs_scsi_dif_blocksize(dif_info);
	if (blocksize == 0) {
		return -1;
	}

	if (wiretomem) {
		ocs_assert(dif_info->dif_oper < ARRAY_SIZE(wiretomem_adj), 0);
		blocksize += wiretomem_adj[dif_info->dif_oper];
	} else {	/* mem to wire */
		ocs_assert(dif_info->dif_oper < ARRAY_SIZE(memtowire_adj), 0);
		blocksize += memtowire_adj[dif_info->dif_oper];
	}
	return blocksize;
}