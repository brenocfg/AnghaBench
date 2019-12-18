#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int uint32_t ;
struct fsl_sata_channel {scalar_t__ aslots; TYPE_4__* slot; union ccb* frozen; int /*<<< orphan*/  r_mem; } ;
typedef  enum fsl_sata_err_type { ____Placeholder_fsl_sata_err_type } fsl_sata_err_type ;
struct TYPE_8__ {TYPE_3__* ccb; } ;
struct TYPE_6__ {int target_id; } ;
struct TYPE_7__ {TYPE_2__ ccb_h; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CAM_DEV_QFRZN ; 
 int CAM_RELEASE_SIMQ ; 
 int CAM_REQUEUE_REQ ; 
 int FSL_SATA_ERR_INVALID ; 
 int FSL_SATA_ERR_NONE ; 
 int FSL_SATA_ERR_SATA ; 
 int FSL_SATA_ERR_TFE ; 
 int FSL_SATA_MAX_SLOTS ; 
 int /*<<< orphan*/  FSL_SATA_P_CCR ; 
 int /*<<< orphan*/  FSL_SATA_P_CER ; 
 int /*<<< orphan*/  FSL_SATA_P_DER ; 
 int FSL_SATA_P_HSTS_DE ; 
 int FSL_SATA_P_HSTS_FE ; 
 int FSL_SATA_P_HSTS_PR ; 
 int FSL_SATA_P_HSTS_SNTFU ; 
 int /*<<< orphan*/  FSL_SATA_P_SERR ; 
 int /*<<< orphan*/  FSL_SATA_P_SNTF ; 
 int /*<<< orphan*/  fsl_sata_done (struct fsl_sata_channel*,union ccb*) ; 
 int /*<<< orphan*/  fsl_sata_end_transaction (TYPE_4__*,int) ; 
 int /*<<< orphan*/  fsl_sata_notify_events (struct fsl_sata_channel*,int) ; 
 int /*<<< orphan*/  fsl_sata_phy_check_events (struct fsl_sata_channel*,int) ; 
 int /*<<< orphan*/  xpt_freeze_devq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fsl_sata_intr_main(struct fsl_sata_channel *ch, uint32_t istatus)
{
	uint32_t cer, der, serr = 0, sntf = 0, ok, err;
	enum fsl_sata_err_type et;
	int i;

	/* Complete all successful commands. */
	ok = ATA_INL(ch->r_mem, FSL_SATA_P_CCR);
	/* Mark all commands complete, to complete the interrupt. */
	ATA_OUTL(ch->r_mem, FSL_SATA_P_CCR, ok);
	if (ch->aslots == 0 && ok != 0) {
		for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
			if (((ok >> i) & 1) && ch->slot[i].ccb != NULL)
				fsl_sata_end_transaction(&ch->slot[i],
				    FSL_SATA_ERR_NONE);
		}
	}
	/* Read command statuses. */
	if (istatus & FSL_SATA_P_HSTS_SNTFU)
		sntf = ATA_INL(ch->r_mem, FSL_SATA_P_SNTF);
	/* XXX: Process PHY events */
	serr = ATA_INL(ch->r_mem, FSL_SATA_P_SERR);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_SERR, serr);
	if (istatus & (FSL_SATA_P_HSTS_PR)) {
		if (serr) {
			fsl_sata_phy_check_events(ch, serr);
		}
	}
	/* Process command errors */
	err = (istatus & (FSL_SATA_P_HSTS_FE | FSL_SATA_P_HSTS_DE));
	cer = ATA_INL(ch->r_mem, FSL_SATA_P_CER);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_CER, cer);
	der = ATA_INL(ch->r_mem, FSL_SATA_P_DER);
	ATA_OUTL(ch->r_mem, FSL_SATA_P_DER, der);
	/* On error, complete the rest of commands with error statuses. */
	if (err) {
		if (ch->frozen) {
			union ccb *fccb = ch->frozen;
			ch->frozen = NULL;
			fccb->ccb_h.status = CAM_REQUEUE_REQ | CAM_RELEASE_SIMQ;
			if (!(fccb->ccb_h.status & CAM_DEV_QFRZN)) {
				xpt_freeze_devq(fccb->ccb_h.path, 1);
				fccb->ccb_h.status |= CAM_DEV_QFRZN;
			}
			fsl_sata_done(ch, fccb);
		}
		for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
			if (ch->slot[i].ccb == NULL)
				continue;
			if ((cer & (1 << i)) != 0)
				et = FSL_SATA_ERR_TFE;
			else if ((der & (1 << ch->slot[i].ccb->ccb_h.target_id)) != 0)
				et = FSL_SATA_ERR_SATA;
			else
				et = FSL_SATA_ERR_INVALID;
			fsl_sata_end_transaction(&ch->slot[i], et);
		}
	}
	/* Process NOTIFY events */
	if (sntf)
		fsl_sata_notify_events(ch, sntf);
}