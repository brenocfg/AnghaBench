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
typedef  int u8 ;

/* Variables and functions */
#define  ABORTED_COMMAND 134 
 int ATA_BUSY ; 
#define  HARDWARE_ERROR 133 
#define  ILLEGAL_REQUEST 132 
#define  MEDIUM_ERROR 131 
#define  NOT_READY 130 
#define  RECOVERED_ERROR 129 
#define  UNIT_ATTENTION 128 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int,int,int,int,int) ; 

__attribute__((used)) static void ata_to_sense_error(unsigned id, u8 drv_stat, u8 drv_err, u8 *sk,
			       u8 *asc, u8 *ascq, int verbose)
{
	int i;

	/* Based on the 3ware driver translation table */
	static const unsigned char sense_table[][4] = {
		/* BBD|ECC|ID|MAR */
		{0xd1,		ABORTED_COMMAND, 0x00, 0x00},
			// Device busy                  Aborted command
		/* BBD|ECC|ID */
		{0xd0,		ABORTED_COMMAND, 0x00, 0x00},
			// Device busy                  Aborted command
		/* ECC|MC|MARK */
		{0x61,		HARDWARE_ERROR, 0x00, 0x00},
			// Device fault                 Hardware error
		/* ICRC|ABRT */		/* NB: ICRC & !ABRT is BBD */
		{0x84,		ABORTED_COMMAND, 0x47, 0x00},
			// Data CRC error               SCSI parity error
		/* MC|ID|ABRT|TRK0|MARK */
		{0x37,		NOT_READY, 0x04, 0x00},
			// Unit offline                 Not ready
		/* MCR|MARK */
		{0x09,		NOT_READY, 0x04, 0x00},
			// Unrecovered disk error       Not ready
		/*  Bad address mark */
		{0x01,		MEDIUM_ERROR, 0x13, 0x00},
			// Address mark not found for data field
		/* TRK0 - Track 0 not found */
		{0x02,		HARDWARE_ERROR, 0x00, 0x00},
			// Hardware error
		/* Abort: 0x04 is not translated here, see below */
		/* Media change request */
		{0x08,		NOT_READY, 0x04, 0x00},
			// FIXME: faking offline
		/* SRV/IDNF - ID not found */
		{0x10,		ILLEGAL_REQUEST, 0x21, 0x00},
			// Logical address out of range
		/* MC - Media Changed */
		{0x20,		UNIT_ATTENTION, 0x28, 0x00},
			// Not ready to ready change, medium may have changed
		/* ECC - Uncorrectable ECC error */
		{0x40,		MEDIUM_ERROR, 0x11, 0x04},
			// Unrecovered read error
		/* BBD - block marked bad */
		{0x80,		MEDIUM_ERROR, 0x11, 0x04},
			// Block marked bad	Medium error, unrecovered read error
		{0xFF, 0xFF, 0xFF, 0xFF}, // END mark
	};
	static const unsigned char stat_table[][4] = {
		/* Must be first because BUSY means no other bits valid */
		{0x80,		ABORTED_COMMAND, 0x47, 0x00},
		// Busy, fake parity for now
		{0x40,		ILLEGAL_REQUEST, 0x21, 0x04},
		// Device ready, unaligned write command
		{0x20,		HARDWARE_ERROR,  0x44, 0x00},
		// Device fault, internal target failure
		{0x08,		ABORTED_COMMAND, 0x47, 0x00},
		// Timed out in xfer, fake parity for now
		{0x04,		RECOVERED_ERROR, 0x11, 0x00},
		// Recovered ECC error	  Medium error, recovered
		{0xFF, 0xFF, 0xFF, 0xFF}, // END mark
	};

	/*
	 *	Is this an error we can process/parse
	 */
	if (drv_stat & ATA_BUSY) {
		drv_err = 0;	/* Ignore the err bits, they're invalid */
	}

	if (drv_err) {
		/* Look for drv_err */
		for (i = 0; sense_table[i][0] != 0xFF; i++) {
			/* Look for best matches first */
			if ((sense_table[i][0] & drv_err) ==
			    sense_table[i][0]) {
				*sk = sense_table[i][1];
				*asc = sense_table[i][2];
				*ascq = sense_table[i][3];
				goto translate_done;
			}
		}
	}

	/*
	 * Fall back to interpreting status bits.  Note that if the drv_err
	 * has only the ABRT bit set, we decode drv_stat.  ABRT by itself
	 * is not descriptive enough.
	 */
	for (i = 0; stat_table[i][0] != 0xFF; i++) {
		if (stat_table[i][0] & drv_stat) {
			*sk = stat_table[i][1];
			*asc = stat_table[i][2];
			*ascq = stat_table[i][3];
			goto translate_done;
		}
	}

	/*
	 * We need a sensible error return here, which is tricky, and one
	 * that won't cause people to do things like return a disk wrongly.
	 */
	*sk = ABORTED_COMMAND;
	*asc = 0x00;
	*ascq = 0x00;

 translate_done:
	if (verbose)
		pr_err("ata%u: translated ATA stat/err 0x%02x/%02x to SCSI SK/ASC/ASCQ 0x%x/%02x/%02x\n",
		       id, drv_stat, drv_err, *sk, *asc, *ascq);
	return;
}