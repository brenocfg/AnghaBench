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
typedef  int u8 ;
typedef  unsigned int u16 ;
struct scsi_cmnd {int* cmnd; int cmd_len; int /*<<< orphan*/  result; } ;
struct ata_queued_cmd {int /*<<< orphan*/  dev; struct scsi_cmnd* scsicmd; } ;
struct TYPE_3__ {int length; } ;

/* Variables and functions */
 int ALL_SUB_MPAGES ; 
#define  CACHE_MPAGE 129 
#define  CONTROL_MPAGE 128 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int const MODE_SELECT ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 int /*<<< orphan*/  ata_mselect_caching (struct ata_queued_cmd*,int const*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  ata_mselect_control (struct ata_queued_cmd*,int const*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  ata_scsi_set_invalid_field (int /*<<< orphan*/ ,struct scsi_cmnd*,unsigned int,int) ; 
 int /*<<< orphan*/  ata_scsi_set_invalid_parameter (int /*<<< orphan*/ ,struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  ata_scsi_set_sense (int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 TYPE_1__* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_page (TYPE_1__*) ; 

__attribute__((used)) static unsigned int ata_scsi_mode_select_xlat(struct ata_queued_cmd *qc)
{
	struct scsi_cmnd *scmd = qc->scsicmd;
	const u8 *cdb = scmd->cmnd;
	const u8 *p;
	u8 pg, spg;
	unsigned six_byte, pg_len, hdr_len, bd_len;
	int len;
	u16 fp = (u16)-1;
	u8 bp = 0xff;

	VPRINTK("ENTER\n");

	six_byte = (cdb[0] == MODE_SELECT);
	if (six_byte) {
		if (scmd->cmd_len < 5) {
			fp = 4;
			goto invalid_fld;
		}

		len = cdb[4];
		hdr_len = 4;
	} else {
		if (scmd->cmd_len < 9) {
			fp = 8;
			goto invalid_fld;
		}

		len = (cdb[7] << 8) + cdb[8];
		hdr_len = 8;
	}

	/* We only support PF=1, SP=0.  */
	if ((cdb[1] & 0x11) != 0x10) {
		fp = 1;
		bp = (cdb[1] & 0x01) ? 1 : 5;
		goto invalid_fld;
	}

	/* Test early for possible overrun.  */
	if (!scsi_sg_count(scmd) || scsi_sglist(scmd)->length < len)
		goto invalid_param_len;

	p = page_address(sg_page(scsi_sglist(scmd)));

	/* Move past header and block descriptors.  */
	if (len < hdr_len)
		goto invalid_param_len;

	if (six_byte)
		bd_len = p[3];
	else
		bd_len = (p[6] << 8) + p[7];

	len -= hdr_len;
	p += hdr_len;
	if (len < bd_len)
		goto invalid_param_len;
	if (bd_len != 0 && bd_len != 8) {
		fp = (six_byte) ? 3 : 6;
		fp += bd_len + hdr_len;
		goto invalid_param;
	}

	len -= bd_len;
	p += bd_len;
	if (len == 0)
		goto skip;

	/* Parse both possible formats for the mode page headers.  */
	pg = p[0] & 0x3f;
	if (p[0] & 0x40) {
		if (len < 4)
			goto invalid_param_len;

		spg = p[1];
		pg_len = (p[2] << 8) | p[3];
		p += 4;
		len -= 4;
	} else {
		if (len < 2)
			goto invalid_param_len;

		spg = 0;
		pg_len = p[1];
		p += 2;
		len -= 2;
	}

	/*
	 * No mode subpages supported (yet) but asking for _all_
	 * subpages may be valid
	 */
	if (spg && (spg != ALL_SUB_MPAGES)) {
		fp = (p[0] & 0x40) ? 1 : 0;
		fp += hdr_len + bd_len;
		goto invalid_param;
	}
	if (pg_len > len)
		goto invalid_param_len;

	switch (pg) {
	case CACHE_MPAGE:
		if (ata_mselect_caching(qc, p, pg_len, &fp) < 0) {
			fp += hdr_len + bd_len;
			goto invalid_param;
		}
		break;
	case CONTROL_MPAGE:
		if (ata_mselect_control(qc, p, pg_len, &fp) < 0) {
			fp += hdr_len + bd_len;
			goto invalid_param;
		} else {
			goto skip; /* No ATA command to send */
		}
		break;
	default:		/* invalid page code */
		fp = bd_len + hdr_len;
		goto invalid_param;
	}

	/*
	 * Only one page has changeable data, so we only support setting one
	 * page at a time.
	 */
	if (len > pg_len)
		goto invalid_param;

	return 0;

 invalid_fld:
	ata_scsi_set_invalid_field(qc->dev, scmd, fp, bp);
	return 1;

 invalid_param:
	ata_scsi_set_invalid_parameter(qc->dev, scmd, fp);
	return 1;

 invalid_param_len:
	/* "Parameter list length error" */
	ata_scsi_set_sense(qc->dev, scmd, ILLEGAL_REQUEST, 0x1a, 0x0);
	return 1;

 skip:
	scmd->result = SAM_STAT_GOOD;
	return 1;
}