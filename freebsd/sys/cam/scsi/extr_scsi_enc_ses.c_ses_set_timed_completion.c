#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status; } ;
union ccb {TYPE_1__ ccb_h; int /*<<< orphan*/  csio; } ;
typedef  int uint8_t ;
struct ses_mgmt_mode_page {int byte5; int /*<<< orphan*/  max_comp_time; } ;
struct cam_periph {int dummy; } ;
struct TYPE_8__ {int ses_flags; } ;
typedef  TYPE_2__ ses_softc_t ;
struct TYPE_9__ {TYPE_2__* enc_private; struct cam_periph* periph; } ;
typedef  TYPE_3__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  ENC_CFLAGS ; 
 int ENC_FLAGS ; 
 int /*<<< orphan*/  ENC_FREE (int*) ; 
 int /*<<< orphan*/  ENC_LOG (TYPE_3__*,char*) ; 
 int* ENC_MALLOCZ (size_t) ; 
 int /*<<< orphan*/  ENC_VLOG (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int SES_FLAG_TIMEDCOMP ; 
 int /*<<< orphan*/  SES_MGMT_MODE_PAGE_CODE ; 
 int SES_MGMT_TIMED_COMP_EN ; 
 int SF_QUIET_IR ; 
 int /*<<< orphan*/  SMS_PAGE_CTRL_CURRENT ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enc_error ; 
 int /*<<< orphan*/  scsi_mode_select (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_mode_sense (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
ses_set_timed_completion(enc_softc_t *enc, uint8_t tc_en)
{
	union ccb *ccb;
	struct cam_periph *periph;
	struct ses_mgmt_mode_page *mgmt;
	uint8_t *mode_buf;
	size_t mode_buf_len;
	ses_softc_t *ses;

	periph = enc->periph;
	ses = enc->enc_private;
	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	mode_buf_len = sizeof(struct ses_mgmt_mode_page);
	mode_buf = ENC_MALLOCZ(mode_buf_len);
	if (mode_buf == NULL)
		goto out;

	scsi_mode_sense(&ccb->csio, /*retries*/4, NULL, MSG_SIMPLE_Q_TAG,
	    /*dbd*/FALSE, SMS_PAGE_CTRL_CURRENT, SES_MGMT_MODE_PAGE_CODE,
	    mode_buf, mode_buf_len, SSD_FULL_SIZE, /*timeout*/60 * 1000);

	/*
	 * Ignore illegal request errors, as they are quite common and we
	 * will print something out in that case anyway.
	 */
	cam_periph_runccb(ccb, enc_error, ENC_CFLAGS,
	    ENC_FLAGS|SF_QUIET_IR, NULL);
	if (ccb->ccb_h.status != CAM_REQ_CMP) {
		ENC_VLOG(enc, "Timed Completion Unsupported\n");
		goto release;
	}

	/* Skip the mode select if the desired value is already set */
	mgmt = (struct ses_mgmt_mode_page *)mode_buf;
	if ((mgmt->byte5 & SES_MGMT_TIMED_COMP_EN) == tc_en)
		goto done;

	/* Value is not what we wanted, set it */
	if (tc_en)
		mgmt->byte5 |= SES_MGMT_TIMED_COMP_EN;
	else
		mgmt->byte5 &= ~SES_MGMT_TIMED_COMP_EN;
	/* SES2r20: a completion time of zero means as long as possible */
	bzero(&mgmt->max_comp_time, sizeof(mgmt->max_comp_time));

	scsi_mode_select(&ccb->csio, 5, NULL, MSG_SIMPLE_Q_TAG,
	    /*page_fmt*/FALSE, /*save_pages*/TRUE, mode_buf, mode_buf_len,
	    SSD_FULL_SIZE, /*timeout*/60 * 1000);

	cam_periph_runccb(ccb, enc_error, ENC_CFLAGS, ENC_FLAGS, NULL);
	if (ccb->ccb_h.status != CAM_REQ_CMP) {
		ENC_VLOG(enc, "Timed Completion Set Failed\n");
		goto release;
	}

done:
	if ((mgmt->byte5 & SES_MGMT_TIMED_COMP_EN) != 0) {
		ENC_LOG(enc, "Timed Completion Enabled\n");
		ses->ses_flags |= SES_FLAG_TIMEDCOMP;
	} else {
		ENC_LOG(enc, "Timed Completion Disabled\n");
		ses->ses_flags &= ~SES_FLAG_TIMEDCOMP;
	}
release:
	ENC_FREE(mode_buf);
	xpt_release_ccb(ccb);
out:
	return (ses->ses_flags & SES_FLAG_TIMEDCOMP);
}