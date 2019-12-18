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
struct ccb_scsiio {int dummy; } ;
union ccb {struct ccb_scsiio csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int /*<<< orphan*/  CD_MSF ; 
 scalar_t__ CD_MSF_FORMAT ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 scalar_t__ SF_RETRY_UA ; 
 int /*<<< orphan*/  SRTOC_FORMAT_TOC ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scsi_read_toc (struct ccb_scsiio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdreadtoc(struct cam_periph *periph, u_int32_t mode, u_int32_t start,
	  u_int8_t *data, u_int32_t len, u_int32_t sense_flags)
{
	u_int32_t ntoc;
        struct ccb_scsiio *csio;
	union ccb *ccb;
	int error;

	ntoc = len;
	error = 0;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	csio = &ccb->csio;

	scsi_read_toc(csio,
		      /* retries */ cd_retry_count,
		      /* cbfcnp */ NULL,
		      /* tag_action */ MSG_SIMPLE_Q_TAG,
		      /* byte1_flags */ (mode == CD_MSF_FORMAT) ? CD_MSF : 0,
		      /* format */ SRTOC_FORMAT_TOC,
		      /* track*/ start,
		      /* data_ptr */ data,
		      /* dxfer_len */ len,
		      /* sense_len */ SSD_FULL_SIZE,
		      /* timeout */ 50000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA | sense_flags);

	xpt_release_ccb(ccb);

	return(error);
}