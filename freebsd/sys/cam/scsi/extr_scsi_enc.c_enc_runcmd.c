#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cdb_bytes; } ;
struct TYPE_10__ {int resid; TYPE_1__ cdb_io; } ;
struct TYPE_11__ {int resid; } ;
struct TYPE_8__ {scalar_t__ func_code; } ;
union ccb {TYPE_4__ csio; TYPE_5__ ataio; TYPE_2__ ccb_h; } ;
struct scsi_sense_data {int dummy; } ;
struct enc_softc {scalar_t__ enc_type; TYPE_3__* periph; } ;
typedef  int /*<<< orphan*/  ccb_flags ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SEP_ATTN ; 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_SUBTRACE ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int /*<<< orphan*/  CAM_DIR_NONE ; 
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  ENC_CFLAGS ; 
 int /*<<< orphan*/  ENC_FLAGS ; 
 scalar_t__ ENC_SEMB_SAFT ; 
 scalar_t__ ENC_SEMB_SES ; 
 int IOCDBLEN ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 char READ_BUFFER ; 
 char RECEIVE_DIAGNOSTIC ; 
 char SEND_DIAGNOSTIC ; 
 scalar_t__ XPT_ATA_IO ; 
 int /*<<< orphan*/  ata_28bit_cmd (TYPE_5__*,int /*<<< orphan*/ ,char,int,int) ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cam_fill_ataio (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  cam_fill_csio (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 union ccb* cam_periph_getccb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enc_error ; 
 int min (int,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

int
enc_runcmd(struct enc_softc *enc, char *cdb, int cdbl, char *dptr, int *dlenp)
{
	int error, dlen, tdlen;
	ccb_flags ddf;
	union ccb *ccb;

	CAM_DEBUG(enc->periph->path, CAM_DEBUG_TRACE,
	    ("entering enc_runcmd\n"));
	if (dptr) {
		if ((dlen = *dlenp) < 0) {
			dlen = -dlen;
			ddf = CAM_DIR_OUT;
		} else {
			ddf = CAM_DIR_IN;
		}
	} else {
		dlen = 0;
		ddf = CAM_DIR_NONE;
	}

	if (cdbl > IOCDBLEN) {
		cdbl = IOCDBLEN;
	}

	ccb = cam_periph_getccb(enc->periph, CAM_PRIORITY_NORMAL);
	if (enc->enc_type == ENC_SEMB_SES || enc->enc_type == ENC_SEMB_SAFT) {
		tdlen = min(dlen, 1020);
		tdlen = (tdlen + 3) & ~3;
		cam_fill_ataio(&ccb->ataio, 0, NULL, ddf, 0, dptr, tdlen,
		    30 * 1000);
		if (cdb[0] == RECEIVE_DIAGNOSTIC)
			ata_28bit_cmd(&ccb->ataio,
			    ATA_SEP_ATTN, cdb[2], 0x02, tdlen / 4);
		else if (cdb[0] == SEND_DIAGNOSTIC)
			ata_28bit_cmd(&ccb->ataio,
			    ATA_SEP_ATTN, dlen > 0 ? dptr[0] : 0,
			    0x82, tdlen / 4);
		else if (cdb[0] == READ_BUFFER)
			ata_28bit_cmd(&ccb->ataio,
			    ATA_SEP_ATTN, cdb[2], 0x00, tdlen / 4);
		else
			ata_28bit_cmd(&ccb->ataio,
			    ATA_SEP_ATTN, dlen > 0 ? dptr[0] : 0,
			    0x80, tdlen / 4);
	} else {
		tdlen = dlen;
		cam_fill_csio(&ccb->csio, 0, NULL, ddf, MSG_SIMPLE_Q_TAG,
		    dptr, dlen, sizeof (struct scsi_sense_data), cdbl,
		    60 * 1000);
		bcopy(cdb, ccb->csio.cdb_io.cdb_bytes, cdbl);
	}

	error = cam_periph_runccb(ccb, enc_error, ENC_CFLAGS, ENC_FLAGS, NULL);
	if (error) {
		if (dptr) {
			*dlenp = dlen;
		}
	} else {
		if (dptr) {
			if (ccb->ccb_h.func_code == XPT_ATA_IO)
				*dlenp = ccb->ataio.resid;
			else
				*dlenp = ccb->csio.resid;
			*dlenp += tdlen - dlen;
		}
	}
	xpt_release_ccb(ccb);
	CAM_DEBUG(enc->periph->path, CAM_DEBUG_SUBTRACE,
	    ("exiting enc_runcmd: *dlenp = %d\n", *dlenp));
	return (error);
}