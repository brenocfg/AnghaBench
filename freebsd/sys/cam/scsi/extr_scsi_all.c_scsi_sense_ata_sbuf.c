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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct scsi_sense_desc_header {int dummy; } ;
struct scsi_sense_data {int dummy; } ;
struct scsi_sense_ata_ret_desc {int status; int error; int flags; int /*<<< orphan*/  device; int /*<<< orphan*/  lba_7_0; int /*<<< orphan*/  lba_15_8; int /*<<< orphan*/  lba_23_16; int /*<<< orphan*/  count_7_0; int /*<<< orphan*/  lba_31_24; int /*<<< orphan*/  lba_39_32; int /*<<< orphan*/  lba_47_40; int /*<<< orphan*/  count_15_8; } ;
struct scsi_inquiry_data {int dummy; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int SSD_DESC_ATA_FLAG_EXTEND ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int,...) ; 

void
scsi_sense_ata_sbuf(struct sbuf *sb, struct scsi_sense_data *sense,
			 u_int sense_len, uint8_t *cdb, int cdb_len,
			 struct scsi_inquiry_data *inq_data,
			 struct scsi_sense_desc_header *header)
{
	struct scsi_sense_ata_ret_desc *res;

	res = (struct scsi_sense_ata_ret_desc *)header;

	sbuf_printf(sb, "ATA status: %02x (%s%s%s%s%s%s%s%s), ",
	    res->status,
	    (res->status & 0x80) ? "BSY " : "",
	    (res->status & 0x40) ? "DRDY " : "",
	    (res->status & 0x20) ? "DF " : "",
	    (res->status & 0x10) ? "SERV " : "",
	    (res->status & 0x08) ? "DRQ " : "",
	    (res->status & 0x04) ? "CORR " : "",
	    (res->status & 0x02) ? "IDX " : "",
	    (res->status & 0x01) ? "ERR" : "");
	if (res->status & 1) {
	    sbuf_printf(sb, "error: %02x (%s%s%s%s%s%s%s%s), ",
		res->error,
		(res->error & 0x80) ? "ICRC " : "",
		(res->error & 0x40) ? "UNC " : "",
		(res->error & 0x20) ? "MC " : "",
		(res->error & 0x10) ? "IDNF " : "",
		(res->error & 0x08) ? "MCR " : "",
		(res->error & 0x04) ? "ABRT " : "",
		(res->error & 0x02) ? "NM " : "",
		(res->error & 0x01) ? "ILI" : "");
	}

	if (res->flags & SSD_DESC_ATA_FLAG_EXTEND) {
		sbuf_printf(sb, "count: %02x%02x, ",
		    res->count_15_8, res->count_7_0);
		sbuf_printf(sb, "LBA: %02x%02x%02x%02x%02x%02x, ",
		    res->lba_47_40, res->lba_39_32, res->lba_31_24,
		    res->lba_23_16, res->lba_15_8, res->lba_7_0);
	} else {
		sbuf_printf(sb, "count: %02x, ", res->count_7_0);
		sbuf_printf(sb, "LBA: %02x%02x%02x, ",
		    res->lba_23_16, res->lba_15_8, res->lba_7_0);
	}
	sbuf_printf(sb, "device: %02x, ", res->device);
}