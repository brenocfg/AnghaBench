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
typedef  int u_int32_t ;
struct scsi_mode_header_6 {int data_length; } ;
struct scsi_mode_header_10 {int /*<<< orphan*/  data_length; } ;
struct cd_softc {int minimum_command_size; int /*<<< orphan*/  mode_queue; } ;
struct cd_mode_params {int cdb_size; int alloc_len; scalar_t__ mode_buf; } ;
struct cd_mode_data_10 {int dummy; } ;
struct cd_mode_data {int dummy; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SMS_PAGE_CTRL_CURRENT ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cd_mode_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct cd_mode_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_mode_params ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int min (int,int) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_mode_sense_len (struct ccb_scsiio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdgetmode(struct cam_periph *periph, struct cd_mode_params *data,
	  u_int32_t page)
{
	struct ccb_scsiio *csio;
	struct cd_softc *softc;
	union ccb *ccb;
	int param_len;
	int error;

	softc = (struct cd_softc *)periph->softc;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	csio = &ccb->csio;

	data->cdb_size = softc->minimum_command_size;
	if (data->cdb_size < 10)
		param_len = sizeof(struct cd_mode_data);
	else
		param_len = sizeof(struct cd_mode_data_10);

	/* Don't say we've got more room than we actually allocated */
	param_len = min(param_len, data->alloc_len);

	scsi_mode_sense_len(csio,
			    /* retries */ cd_retry_count,
			    /* cbfcnp */ NULL,
			    /* tag_action */ MSG_SIMPLE_Q_TAG,
			    /* dbd */ 0,
			    /* page_code */ SMS_PAGE_CTRL_CURRENT,
			    /* page */ page,
			    /* param_buf */ data->mode_buf,
			    /* param_len */ param_len,
			    /* minimum_cmd_size */ softc->minimum_command_size,
			    /* sense_len */ SSD_FULL_SIZE,
			    /* timeout */ 50000);

	/*
	 * It would be nice not to have to do this, but there's no
	 * available pointer in the CCB that would allow us to stuff the
	 * mode params structure in there and retrieve it in
	 * cd6byteworkaround(), so we can set the cdb size.  The cdb size
	 * lets the caller know what CDB size we ended up using, so they
	 * can find the actual mode page offset.
	 */
	STAILQ_INSERT_TAIL(&softc->mode_queue, data, links);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA);

	xpt_release_ccb(ccb);

	STAILQ_REMOVE(&softc->mode_queue, data, cd_mode_params, links);

	/*
	 * This is a bit of belt-and-suspenders checking, but if we run
	 * into a situation where the target sends back multiple block
	 * descriptors, we might not have enough space in the buffer to
	 * see the whole mode page.  Better to return an error than
	 * potentially access memory beyond our malloced region.
	 */
	if (error == 0) {
		u_int32_t data_len;

		if (data->cdb_size == 10) {
			struct scsi_mode_header_10 *hdr10;

			hdr10 = (struct scsi_mode_header_10 *)data->mode_buf;
			data_len = scsi_2btoul(hdr10->data_length);
			data_len += sizeof(hdr10->data_length);
		} else {
			struct scsi_mode_header_6 *hdr6;

			hdr6 = (struct scsi_mode_header_6 *)data->mode_buf;
			data_len = hdr6->data_length;
			data_len += sizeof(hdr6->data_length);
		}

		/*
		 * Complain if there is more mode data available than we
		 * allocated space for.  This could potentially happen if
		 * we miscalculated the page length for some reason, if the
		 * drive returns multiple block descriptors, or if it sets
		 * the data length incorrectly.
		 */
		if (data_len > data->alloc_len) {
			xpt_print(periph->path, "allocated modepage %d length "
			    "%d < returned length %d\n", page, data->alloc_len,
			    data_len);
			error = ENOSPC;
		}
	}
	return (error);
}