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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int dif_oper; } ;
typedef  TYPE_1__ ocs_hw_dif_info_t ;

/* Variables and functions */
 int FALSE ; 
#define  OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC 132 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM 131 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC 130 
#define  OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF 129 
#define  OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC 128 
 int TRUE ; 

__attribute__((used)) static int
ocs_scsi_dif_guard_is_crc(uint8_t direction, ocs_hw_dif_info_t *dif_info)
{
	int is_crc;

	if (direction) {
		/* For writes, check if operation is "OUT_CRC" or not */
		switch(dif_info->dif_oper) {
			case OCS_HW_SGE_DIF_OP_IN_NODIF_OUT_CRC:
			case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC:
			case OCS_HW_SGE_DIF_OP_IN_CHKSUM_OUT_CRC:
				is_crc = TRUE;
				break;
			default:
				is_crc = FALSE;
				break;
		}
	} else {
		/* For reads, check if operation is "IN_CRC" or not */
		switch(dif_info->dif_oper) {
			case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_NODIF:
			case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CRC:
			case OCS_HW_SGE_DIF_OP_IN_CRC_OUT_CHKSUM:
				is_crc = TRUE;
				break;
			default:
				is_crc = FALSE;
				break;
		}
	}

	return is_crc;
}