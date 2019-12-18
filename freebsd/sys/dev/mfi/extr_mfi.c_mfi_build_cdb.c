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
typedef  scalar_t__ uint8_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct scsi_rw_6 {int length; scalar_t__ control; int /*<<< orphan*/  addr; int /*<<< orphan*/  opcode; } ;
struct scsi_rw_16 {scalar_t__ control; int /*<<< orphan*/  length; scalar_t__ reserved; int /*<<< orphan*/  addr; scalar_t__ byte2; int /*<<< orphan*/  opcode; } ;
struct scsi_rw_12 {scalar_t__ control; int /*<<< orphan*/  length; scalar_t__ reserved; int /*<<< orphan*/  addr; scalar_t__ byte2; int /*<<< orphan*/  opcode; } ;
struct scsi_rw_10 {scalar_t__ control; int /*<<< orphan*/  length; scalar_t__ reserved; int /*<<< orphan*/  addr; scalar_t__ byte2; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_10 ; 
 int /*<<< orphan*/  READ_12 ; 
 int /*<<< orphan*/  READ_16 ; 
 int /*<<< orphan*/  READ_6 ; 
 int /*<<< orphan*/  WRITE_10 ; 
 int /*<<< orphan*/  WRITE_12 ; 
 int /*<<< orphan*/  WRITE_16 ; 
 int /*<<< orphan*/  WRITE_6 ; 
 int /*<<< orphan*/  scsi_u64to8b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto3b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_ulto4b (int,int /*<<< orphan*/ ) ; 

int
mfi_build_cdb(int readop, uint8_t byte2, u_int64_t lba, u_int32_t block_count, uint8_t *cdb)
{
	int cdb_len;

	if (((lba & 0x1fffff) == lba)
         && ((block_count & 0xff) == block_count)
         && (byte2 == 0)) {
		/* We can fit in a 6 byte cdb */
		struct scsi_rw_6 *scsi_cmd;

		scsi_cmd = (struct scsi_rw_6 *)cdb;
		scsi_cmd->opcode = readop ? READ_6 : WRITE_6;
		scsi_ulto3b(lba, scsi_cmd->addr);
		scsi_cmd->length = block_count & 0xff;
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);
	} else if (((block_count & 0xffff) == block_count) && ((lba & 0xffffffff) == lba)) {
		/* Need a 10 byte CDB */
		struct scsi_rw_10 *scsi_cmd;

		scsi_cmd = (struct scsi_rw_10 *)cdb;
		scsi_cmd->opcode = readop ? READ_10 : WRITE_10;
		scsi_cmd->byte2 = byte2;
		scsi_ulto4b(lba, scsi_cmd->addr);
		scsi_cmd->reserved = 0;
		scsi_ulto2b(block_count, scsi_cmd->length);
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);
	} else if (((block_count & 0xffffffff) == block_count) &&
	    ((lba & 0xffffffff) == lba)) {
		/* Block count is too big for 10 byte CDB use a 12 byte CDB */
		struct scsi_rw_12 *scsi_cmd;

		scsi_cmd = (struct scsi_rw_12 *)cdb;
		scsi_cmd->opcode = readop ? READ_12 : WRITE_12;
		scsi_cmd->byte2 = byte2;
		scsi_ulto4b(lba, scsi_cmd->addr);
		scsi_cmd->reserved = 0;
		scsi_ulto4b(block_count, scsi_cmd->length);
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);
	} else {
		/*
		 * 16 byte CDB.  We'll only get here if the LBA is larger
		 * than 2^32
		 */
		struct scsi_rw_16 *scsi_cmd;

		scsi_cmd = (struct scsi_rw_16 *)cdb;
		scsi_cmd->opcode = readop ? READ_16 : WRITE_16;
		scsi_cmd->byte2 = byte2;
		scsi_u64to8b(lba, scsi_cmd->addr);
		scsi_cmd->reserved = 0;
		scsi_ulto4b(block_count, scsi_cmd->length);
		scsi_cmd->control = 0;
		cdb_len = sizeof(*scsi_cmd);
	}

	return cdb_len;
}