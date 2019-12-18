#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ resid; } ;
union ccb {TYPE_1__ csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct scsi_report_key_data_title {int byte0; int /*<<< orphan*/  title_key; } ;
struct scsi_report_key_data_rpc {int byte4; int /*<<< orphan*/  rpc_scheme1; int /*<<< orphan*/  region_mask; } ;
struct scsi_report_key_data_key1_key2 {int /*<<< orphan*/  key1; } ;
struct scsi_report_key_data_challenge {int /*<<< orphan*/  challenge_key; } ;
struct scsi_report_key_data_asf {int success; } ;
struct scsi_report_key_data_agid {int agid; } ;
struct dvd_authinfo {int agid; int cpm; int cp_sec; int cgms; int asf; int reg_type; int vend_rsts; int user_rsts; int /*<<< orphan*/  rpc_scheme; int /*<<< orphan*/  region; int /*<<< orphan*/  keychal; int /*<<< orphan*/  format; scalar_t__ lba; } ;
struct cam_periph {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
#define  DVD_INVALIDATE_AGID 134 
#define  DVD_REPORT_AGID 133 
#define  DVD_REPORT_ASF 132 
#define  DVD_REPORT_CHALLENGE 131 
#define  DVD_REPORT_KEY1 130 
#define  DVD_REPORT_RPC 129 
#define  DVD_REPORT_TITLE_KEY 128 
 int EINVAL ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int RKD_AGID_MASK ; 
 int RKD_AGID_SHIFT ; 
 int RKD_ASF_SUCCESS ; 
 int RKD_RPC_TYPE_MASK ; 
 int RKD_RPC_TYPE_SHIFT ; 
 int RKD_RPC_USER_RESET_MASK ; 
 int RKD_RPC_VENDOR_RESET_MASK ; 
 int RKD_RPC_VENDOR_RESET_SHIFT ; 
 int RKD_TITLE_CMGS_MASK ; 
 int RKD_TITLE_CMGS_SHIFT ; 
 int RKD_TITLE_CPM ; 
 int RKD_TITLE_CPM_SHIFT ; 
 int RKD_TITLE_CP_SEC ; 
 int RKD_TITLE_CP_SEC_SHIFT ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_report_key (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_print (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdreportkey(struct cam_periph *periph, struct dvd_authinfo *authinfo)
{
	union ccb *ccb;
	u_int8_t *databuf;
	u_int32_t lba;
	int error;
	int length;

	error = 0;
	databuf = NULL;
	lba = 0;

	switch (authinfo->format) {
	case DVD_REPORT_AGID:
		length = sizeof(struct scsi_report_key_data_agid);
		break;
	case DVD_REPORT_CHALLENGE:
		length = sizeof(struct scsi_report_key_data_challenge);
		break;
	case DVD_REPORT_KEY1:
		length = sizeof(struct scsi_report_key_data_key1_key2);
		break;
	case DVD_REPORT_TITLE_KEY:
		length = sizeof(struct scsi_report_key_data_title);
		/* The lba field is only set for the title key */
		lba = authinfo->lba;
		break;
	case DVD_REPORT_ASF:
		length = sizeof(struct scsi_report_key_data_asf);
		break;
	case DVD_REPORT_RPC:
		length = sizeof(struct scsi_report_key_data_rpc);
		break;
	case DVD_INVALIDATE_AGID:
		length = 0;
		break;
	default:
		return (EINVAL);
	}

	if (length != 0) {
		databuf = malloc(length, M_DEVBUF, M_WAITOK | M_ZERO);
	} else
		databuf = NULL;

	cam_periph_lock(periph);
	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_report_key(&ccb->csio,
			/* retries */ cd_retry_count,
			/* cbfcnp */ NULL,
			/* tag_action */ MSG_SIMPLE_Q_TAG,
			/* lba */ lba,
			/* agid */ authinfo->agid,
			/* key_format */ authinfo->format,
			/* data_ptr */ databuf,
			/* dxfer_len */ length,
			/* sense_len */ SSD_FULL_SIZE,
			/* timeout */ 50000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA);

	if (error != 0)
		goto bailout;

	if (ccb->csio.resid != 0) {
		xpt_print(periph->path, "warning, residual for report key "
		    "command is %d\n", ccb->csio.resid);
	}

	switch(authinfo->format) {
	case DVD_REPORT_AGID: {
		struct scsi_report_key_data_agid *agid_data;

		agid_data = (struct scsi_report_key_data_agid *)databuf;

		authinfo->agid = (agid_data->agid & RKD_AGID_MASK) >>
			RKD_AGID_SHIFT;
		break;
	}
	case DVD_REPORT_CHALLENGE: {
		struct scsi_report_key_data_challenge *chal_data;

		chal_data = (struct scsi_report_key_data_challenge *)databuf;

		bcopy(chal_data->challenge_key, authinfo->keychal,
		      min(sizeof(chal_data->challenge_key),
		          sizeof(authinfo->keychal)));
		break;
	}
	case DVD_REPORT_KEY1: {
		struct scsi_report_key_data_key1_key2 *key1_data;

		key1_data = (struct scsi_report_key_data_key1_key2 *)databuf;

		bcopy(key1_data->key1, authinfo->keychal,
		      min(sizeof(key1_data->key1), sizeof(authinfo->keychal)));
		break;
	}
	case DVD_REPORT_TITLE_KEY: {
		struct scsi_report_key_data_title *title_data;

		title_data = (struct scsi_report_key_data_title *)databuf;

		authinfo->cpm = (title_data->byte0 & RKD_TITLE_CPM) >>
			RKD_TITLE_CPM_SHIFT;
		authinfo->cp_sec = (title_data->byte0 & RKD_TITLE_CP_SEC) >>
			RKD_TITLE_CP_SEC_SHIFT;
		authinfo->cgms = (title_data->byte0 & RKD_TITLE_CMGS_MASK) >>
			RKD_TITLE_CMGS_SHIFT;
		bcopy(title_data->title_key, authinfo->keychal,
		      min(sizeof(title_data->title_key),
			  sizeof(authinfo->keychal)));
		break;
	}
	case DVD_REPORT_ASF: {
		struct scsi_report_key_data_asf *asf_data;

		asf_data = (struct scsi_report_key_data_asf *)databuf;

		authinfo->asf = asf_data->success & RKD_ASF_SUCCESS;
		break;
	}
	case DVD_REPORT_RPC: {
		struct scsi_report_key_data_rpc *rpc_data;

		rpc_data = (struct scsi_report_key_data_rpc *)databuf;

		authinfo->reg_type = (rpc_data->byte4 & RKD_RPC_TYPE_MASK) >>
			RKD_RPC_TYPE_SHIFT;
		authinfo->vend_rsts =
			(rpc_data->byte4 & RKD_RPC_VENDOR_RESET_MASK) >>
			RKD_RPC_VENDOR_RESET_SHIFT;
		authinfo->user_rsts = rpc_data->byte4 & RKD_RPC_USER_RESET_MASK;
		authinfo->region = rpc_data->region_mask;
		authinfo->rpc_scheme = rpc_data->rpc_scheme1;
		break;
	}
	case DVD_INVALIDATE_AGID:
		break;
	default:
		/* This should be impossible, since we checked above */
		error = EINVAL;
		goto bailout;
		break; /* NOTREACHED */
	}

bailout:
	xpt_release_ccb(ccb);
	cam_periph_unlock(periph);

	if (databuf != NULL)
		free(databuf, M_DEVBUF);

	return(error);
}