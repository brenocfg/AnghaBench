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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BE16 (int*) ; 
 int GET_BE32 (int*) ; 
 int /*<<< orphan*/  GET_BE64 (int*) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
#define  SCMD_READ_10 135 
#define  SCMD_READ_12 134 
#define  SCMD_READ_16 133 
#define  SCMD_READ_6 132 
#define  SCMD_WRITE_10 131 
#define  SCMD_WRITE_12 130 
#define  SCMD_WRITE_16 129 
#define  SCMD_WRITE_6 128 

int check_for_scsi_opcode(uint8_t *cdb, boolean_t *is_write, uint64_t *fst_blk,
				uint32_t *blk_cnt) {
	
	switch (cdb[0]) {
	case SCMD_WRITE_6:
		*is_write = true;
	case SCMD_READ_6:
		*fst_blk = (uint64_t)(((cdb[1] & 0x1F) << 16) |
				(cdb[2] << 8) | cdb[3]);
		*blk_cnt = (uint32_t)cdb[4];
		if (*blk_cnt == 0)
			*blk_cnt = 256;
		break;
	case SCMD_WRITE_10:
		*is_write = true;
	case SCMD_READ_10:
		*fst_blk = (uint64_t)GET_BE32(&cdb[2]);
		*blk_cnt = (uint32_t)GET_BE16(&cdb[7]);
		break;
	case SCMD_WRITE_12:
		*is_write = true;
	case SCMD_READ_12:
		*fst_blk = (uint64_t)GET_BE32(&cdb[2]);
		*blk_cnt = GET_BE32(&cdb[6]);
		break;
	case SCMD_WRITE_16:
		*is_write = true;
	case SCMD_READ_16:
		*fst_blk = GET_BE64(&cdb[2]);
		*blk_cnt = GET_BE32(&cdb[10]);
		break;
	default:
		/* Process via normal I/O path. */
		return PQI_STATUS_FAILURE;
	}
	return PQI_STATUS_SUCCESS;
}