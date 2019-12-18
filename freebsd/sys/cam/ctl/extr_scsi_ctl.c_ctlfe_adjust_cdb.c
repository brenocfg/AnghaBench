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
struct scsi_rw_6 {int length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_16 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_12 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct scsi_rw_10 {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ccb_accept_tio {int dummy; } ;

/* Variables and functions */
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int* atio_cdb_ptr (struct ccb_accept_tio*) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_3btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 int scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_u64to8b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctlfe_adjust_cdb(struct ccb_accept_tio *atio, uint32_t offset)
{
	uint64_t lba;
	uint32_t num_blocks, nbc;
	uint8_t *cmdbyt = atio_cdb_ptr(atio);

	nbc = offset >> 9;	/* ASSUMING 512 BYTE BLOCKS */

	switch (cmdbyt[0]) {
	case READ_6:
	case WRITE_6:
	{
		struct scsi_rw_6 *cdb = (struct scsi_rw_6 *)cmdbyt;
		lba = scsi_3btoul(cdb->addr);
		lba &= 0x1fffff;
		num_blocks = cdb->length;
		if (num_blocks == 0)
			num_blocks = 256;
		lba += nbc;
		num_blocks -= nbc;
		scsi_ulto3b(lba, cdb->addr);
		cdb->length = num_blocks;
		break;
	}
	case READ_10:
	case WRITE_10:
	{
		struct scsi_rw_10 *cdb = (struct scsi_rw_10 *)cmdbyt;
		lba = scsi_4btoul(cdb->addr);
		num_blocks = scsi_2btoul(cdb->length);
		lba += nbc;
		num_blocks -= nbc;
		scsi_ulto4b(lba, cdb->addr);
		scsi_ulto2b(num_blocks, cdb->length);
		break;
	}
	case READ_12:
	case WRITE_12:
	{
		struct scsi_rw_12 *cdb = (struct scsi_rw_12 *)cmdbyt;
		lba = scsi_4btoul(cdb->addr);
		num_blocks = scsi_4btoul(cdb->length);
		lba += nbc;
		num_blocks -= nbc;
		scsi_ulto4b(lba, cdb->addr);
		scsi_ulto4b(num_blocks, cdb->length);
		break;
	}
	case READ_16:
	case WRITE_16:
	{
		struct scsi_rw_16 *cdb = (struct scsi_rw_16 *)cmdbyt;
		lba = scsi_8btou64(cdb->addr);
		num_blocks = scsi_4btoul(cdb->length);
		lba += nbc;
		num_blocks -= nbc;
		scsi_u64to8b(lba, cdb->addr);
		scsi_ulto4b(num_blocks, cdb->length);
		break;
	}
	default:
		return -1;
	}
	return (0);
}