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
union ccb {int /*<<< orphan*/  csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct scsi_send_key_data_rpc {int /*<<< orphan*/  region_code; int /*<<< orphan*/  data_len; } ;
struct scsi_report_key_data_key1_key2 {int /*<<< orphan*/  key1; int /*<<< orphan*/  data_len; } ;
struct scsi_report_key_data_challenge {int /*<<< orphan*/  challenge_key; int /*<<< orphan*/  data_len; } ;
struct dvd_authinfo {int format; int /*<<< orphan*/  agid; int /*<<< orphan*/  region; int /*<<< orphan*/  keychal; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
#define  DVD_SEND_CHALLENGE 130 
#define  DVD_SEND_KEY2 129 
#define  DVD_SEND_RPC 128 
 int EINVAL ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
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
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  scsi_send_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_ulto2b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdsendkey(struct cam_periph *periph, struct dvd_authinfo *authinfo)
{
	union ccb *ccb;
	u_int8_t *databuf;
	int length;
	int error;

	error = 0;
	databuf = NULL;

	switch(authinfo->format) {
	case DVD_SEND_CHALLENGE: {
		struct scsi_report_key_data_challenge *challenge_data;

		length = sizeof(*challenge_data);

		challenge_data = malloc(length, M_DEVBUF, M_WAITOK | M_ZERO);

		databuf = (u_int8_t *)challenge_data;

		scsi_ulto2b(length - sizeof(challenge_data->data_len),
			    challenge_data->data_len);

		bcopy(authinfo->keychal, challenge_data->challenge_key,
		      min(sizeof(authinfo->keychal),
			  sizeof(challenge_data->challenge_key)));
		break;
	}
	case DVD_SEND_KEY2: {
		struct scsi_report_key_data_key1_key2 *key2_data;

		length = sizeof(*key2_data);

		key2_data = malloc(length, M_DEVBUF, M_WAITOK | M_ZERO);

		databuf = (u_int8_t *)key2_data;

		scsi_ulto2b(length - sizeof(key2_data->data_len),
			    key2_data->data_len);

		bcopy(authinfo->keychal, key2_data->key1,
		      min(sizeof(authinfo->keychal), sizeof(key2_data->key1)));

		break;
	}
	case DVD_SEND_RPC: {
		struct scsi_send_key_data_rpc *rpc_data;

		length = sizeof(*rpc_data);

		rpc_data = malloc(length, M_DEVBUF, M_WAITOK | M_ZERO);

		databuf = (u_int8_t *)rpc_data;

		scsi_ulto2b(length - sizeof(rpc_data->data_len),
			    rpc_data->data_len);

		rpc_data->region_code = authinfo->region;
		break;
	}
	default:
		return (EINVAL);
	}

	cam_periph_lock(periph);
	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_send_key(&ccb->csio,
		      /* retries */ cd_retry_count,
		      /* cbfcnp */ NULL,
		      /* tag_action */ MSG_SIMPLE_Q_TAG,
		      /* agid */ authinfo->agid,
		      /* key_format */ authinfo->format,
		      /* data_ptr */ databuf,
		      /* dxfer_len */ length,
		      /* sense_len */ SSD_FULL_SIZE,
		      /* timeout */ 50000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA);

	xpt_release_ccb(ccb);
	cam_periph_unlock(periph);

	if (databuf != NULL)
		free(databuf, M_DEVBUF);

	return(error);
}