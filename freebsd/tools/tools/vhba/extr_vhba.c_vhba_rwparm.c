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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u_int32_t ;

/* Variables and functions */
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 

int
vhba_rwparm(uint8_t *cdb, uint64_t *offset, uint32_t *tl, uint64_t nblks, uint32_t blk_shift)
{
	uint32_t cnt;
	uint64_t lba;

	switch (cdb[0]) {
	case WRITE_16:
	case READ_16:
		cnt =	(((uint32_t)cdb[10]) <<  24) |
			(((uint32_t)cdb[11]) <<  16) |
			(((uint32_t)cdb[12]) <<   8) |
			((uint32_t)cdb[13]);

		lba =	(((uint64_t)cdb[2]) << 56) |
			(((uint64_t)cdb[3]) << 48) |
			(((uint64_t)cdb[4]) << 40) |
			(((uint64_t)cdb[5]) << 32) |
			(((uint64_t)cdb[6]) << 24) |
			(((uint64_t)cdb[7]) << 16) |
			(((uint64_t)cdb[8]) <<  8) |
			((uint64_t)cdb[9]);
		break;
	case WRITE_12:
	case READ_12:
		cnt =	(((uint32_t)cdb[6]) <<  16) |
			(((uint32_t)cdb[7]) <<   8) |
			((u_int32_t)cdb[8]);

		lba =	(((uint32_t)cdb[2]) << 24) |
			(((uint32_t)cdb[3]) << 16) |
			(((uint32_t)cdb[4]) <<  8) |
			((uint32_t)cdb[5]);
		break;
	case WRITE_10:
	case READ_10:
		cnt =	(((uint32_t)cdb[7]) <<  8) |
			((u_int32_t)cdb[8]);

		lba =	(((uint32_t)cdb[2]) << 24) |
			(((uint32_t)cdb[3]) << 16) |
			(((uint32_t)cdb[4]) <<  8) |
			((uint32_t)cdb[5]);
		break;
	case WRITE_6:
	case READ_6:
		cnt = cdb[4];
		if (cnt == 0) {
			cnt = 256;
		}
		lba =	(((uint32_t)cdb[1] & 0x1f) << 16) |
			(((uint32_t)cdb[2]) << 8) |
			((uint32_t)cdb[3]);
		break;
	default:
		return (-1);
	}

	if (lba + cnt > nblks) {
		return (-1);
	}
	*tl = cnt << blk_shift;
	*offset = lba << blk_shift;
	return (0);
}