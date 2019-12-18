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
struct TYPE_2__ {int /*<<< orphan*/  resid; } ;
union ccb {TYPE_1__ csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct scsi_read_dvd_struct_data_spare_area {int dummy; } ;
struct scsi_read_dvd_struct_data_prot_discid {int dummy; } ;
struct scsi_read_dvd_struct_data_layer_desc {int book_type_version; int disc_size_max_rate; int layer_info; int density; int bca; int /*<<< orphan*/  end_sector_layer0; int /*<<< orphan*/  main_data_end; int /*<<< orphan*/  main_data_start; } ;
struct scsi_read_dvd_struct_data_physical {struct scsi_read_dvd_struct_data_layer_desc layer_desc; } ;
struct scsi_read_dvd_struct_data_medium_status {int dummy; } ;
struct scsi_read_dvd_struct_data_manufacturer {int dummy; } ;
struct scsi_read_dvd_struct_data_leadin {int dummy; } ;
struct scsi_read_dvd_struct_data_header {int dummy; } ;
struct scsi_read_dvd_struct_data_disc_key_blk {int dummy; } ;
struct scsi_read_dvd_struct_data_disc_key {int dummy; } ;
struct scsi_read_dvd_struct_data_disc_id {int dummy; } ;
struct scsi_read_dvd_struct_data_dds {int dummy; } ;
struct scsi_read_dvd_struct_data_copyright {int /*<<< orphan*/  region_info; int /*<<< orphan*/  cps_type; } ;
struct scsi_read_dvd_struct_data_bca {int dummy; } ;
struct dvd_struct {int length; int /*<<< orphan*/  data; int /*<<< orphan*/  rmi; int /*<<< orphan*/  cpst; int /*<<< orphan*/  format; int /*<<< orphan*/  agid; int /*<<< orphan*/  layer_num; } ;
struct dvd_layer {int book_type; int book_version; int disc_size; int max_rate; int nlayers; int track_path; int layer_type; int linear_density; int track_density; int bca; void* end_sector_l0; void* end_sector; void* start_sector; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
#define  DVD_STRUCT_BCA 144 
#define  DVD_STRUCT_CMI 143 
#define  DVD_STRUCT_COPYRIGHT 142 
#define  DVD_STRUCT_DCB 141 
#define  DVD_STRUCT_DDS 140 
#define  DVD_STRUCT_DISCKEY 139 
#define  DVD_STRUCT_DISCKEYBLOCK 138 
#define  DVD_STRUCT_LIST 137 
#define  DVD_STRUCT_MANUFACT 136 
#define  DVD_STRUCT_MEDIUM_STAT 135 
#define  DVD_STRUCT_PHYSICAL 134 
#define  DVD_STRUCT_PRERECORDED 133 
#define  DVD_STRUCT_PROTDISCID 132 
#define  DVD_STRUCT_RMD_LAST 131 
#define  DVD_STRUCT_RMD_RMA 130 
#define  DVD_STRUCT_SPARE_AREA 129 
#define  DVD_STRUCT_UNIQUEID 128 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int RDSD_BCA_MASK ; 
 int RDSD_BCA_SHIFT ; 
 int RDSD_BOOK_TYPE_MASK ; 
 int RDSD_BOOK_TYPE_SHIFT ; 
 int RDSD_BOOK_VERSION_MASK ; 
 int RDSD_DISC_SIZE_MASK ; 
 int RDSD_DISC_SIZE_SHIFT ; 
 int RDSD_LAYER_TYPE_MASK ; 
 int RDSD_LIN_DENSITY_MASK ; 
 int RDSD_LIN_DENSITY_SHIFT ; 
 int RDSD_MAX_RATE_MASK ; 
 int RDSD_NUM_LAYERS_MASK ; 
 int RDSD_NUM_LAYERS_SHIFT ; 
 int RDSD_TRACK_DENSITY_MASK ; 
 int RDSD_TRACK_PATH_MASK ; 
 int RDSD_TRACK_PATH_SHIFT ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  cd_retry_count ; 
 int /*<<< orphan*/  cderror ; 
 int cdrunccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 void* scsi_3btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_read_dvd_structure (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
cdreaddvdstructure(struct cam_periph *periph, struct dvd_struct *dvdstruct)
{
	union ccb *ccb;
	u_int8_t *databuf;
	u_int32_t address;
	int error;
	int length;

	error = 0;
	databuf = NULL;
	/* The address is reserved for many of the formats */
	address = 0;

	switch(dvdstruct->format) {
	case DVD_STRUCT_PHYSICAL:
		length = sizeof(struct scsi_read_dvd_struct_data_physical);
		break;
	case DVD_STRUCT_COPYRIGHT:
		length = sizeof(struct scsi_read_dvd_struct_data_copyright);
		break;
	case DVD_STRUCT_DISCKEY:
		length = sizeof(struct scsi_read_dvd_struct_data_disc_key);
		break;
	case DVD_STRUCT_BCA:
		length = sizeof(struct scsi_read_dvd_struct_data_bca);
		break;
	case DVD_STRUCT_MANUFACT:
		length = sizeof(struct scsi_read_dvd_struct_data_manufacturer);
		break;
	case DVD_STRUCT_CMI:
		return (ENODEV);
	case DVD_STRUCT_PROTDISCID:
		length = sizeof(struct scsi_read_dvd_struct_data_prot_discid);
		break;
	case DVD_STRUCT_DISCKEYBLOCK:
		length = sizeof(struct scsi_read_dvd_struct_data_disc_key_blk);
		break;
	case DVD_STRUCT_DDS:
		length = sizeof(struct scsi_read_dvd_struct_data_dds);
		break;
	case DVD_STRUCT_MEDIUM_STAT:
		length = sizeof(struct scsi_read_dvd_struct_data_medium_status);
		break;
	case DVD_STRUCT_SPARE_AREA:
		length = sizeof(struct scsi_read_dvd_struct_data_spare_area);
		break;
	case DVD_STRUCT_RMD_LAST:
		return (ENODEV);
	case DVD_STRUCT_RMD_RMA:
		return (ENODEV);
	case DVD_STRUCT_PRERECORDED:
		length = sizeof(struct scsi_read_dvd_struct_data_leadin);
		break;
	case DVD_STRUCT_UNIQUEID:
		length = sizeof(struct scsi_read_dvd_struct_data_disc_id);
		break;
	case DVD_STRUCT_DCB:
		return (ENODEV);
	case DVD_STRUCT_LIST:
		/*
		 * This is the maximum allocation length for the READ DVD
		 * STRUCTURE command.  There's nothing in the MMC3 spec
		 * that indicates a limit in the amount of data that can
		 * be returned from this call, other than the limits
		 * imposed by the 2-byte length variables.
		 */
		length = 65535;
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

	scsi_read_dvd_structure(&ccb->csio,
				/* retries */ cd_retry_count,
				/* cbfcnp */ NULL,
				/* tag_action */ MSG_SIMPLE_Q_TAG,
				/* lba */ address,
				/* layer_number */ dvdstruct->layer_num,
				/* key_format */ dvdstruct->format,
				/* agid */ dvdstruct->agid,
				/* data_ptr */ databuf,
				/* dxfer_len */ length,
				/* sense_len */ SSD_FULL_SIZE,
				/* timeout */ 50000);

	error = cdrunccb(ccb, cderror, /*cam_flags*/CAM_RETRY_SELTO,
			 /*sense_flags*/SF_RETRY_UA);

	if (error != 0)
		goto bailout;

	switch(dvdstruct->format) {
	case DVD_STRUCT_PHYSICAL: {
		struct scsi_read_dvd_struct_data_layer_desc *inlayer;
		struct dvd_layer *outlayer;
		struct scsi_read_dvd_struct_data_physical *phys_data;

		phys_data =
			(struct scsi_read_dvd_struct_data_physical *)databuf;
		inlayer = &phys_data->layer_desc;
		outlayer = (struct dvd_layer *)&dvdstruct->data;

		dvdstruct->length = sizeof(*inlayer);

		outlayer->book_type = (inlayer->book_type_version &
			RDSD_BOOK_TYPE_MASK) >> RDSD_BOOK_TYPE_SHIFT;
		outlayer->book_version = (inlayer->book_type_version &
			RDSD_BOOK_VERSION_MASK);
		outlayer->disc_size = (inlayer->disc_size_max_rate &
			RDSD_DISC_SIZE_MASK) >> RDSD_DISC_SIZE_SHIFT;
		outlayer->max_rate = (inlayer->disc_size_max_rate &
			RDSD_MAX_RATE_MASK);
		outlayer->nlayers = (inlayer->layer_info &
			RDSD_NUM_LAYERS_MASK) >> RDSD_NUM_LAYERS_SHIFT;
		outlayer->track_path = (inlayer->layer_info &
			RDSD_TRACK_PATH_MASK) >> RDSD_TRACK_PATH_SHIFT;
		outlayer->layer_type = (inlayer->layer_info &
			RDSD_LAYER_TYPE_MASK);
		outlayer->linear_density = (inlayer->density &
			RDSD_LIN_DENSITY_MASK) >> RDSD_LIN_DENSITY_SHIFT;
		outlayer->track_density = (inlayer->density &
			RDSD_TRACK_DENSITY_MASK);
		outlayer->bca = (inlayer->bca & RDSD_BCA_MASK) >>
			RDSD_BCA_SHIFT;
		outlayer->start_sector = scsi_3btoul(inlayer->main_data_start);
		outlayer->end_sector = scsi_3btoul(inlayer->main_data_end);
		outlayer->end_sector_l0 =
			scsi_3btoul(inlayer->end_sector_layer0);
		break;
	}
	case DVD_STRUCT_COPYRIGHT: {
		struct scsi_read_dvd_struct_data_copyright *copy_data;

		copy_data = (struct scsi_read_dvd_struct_data_copyright *)
			databuf;

		dvdstruct->cpst = copy_data->cps_type;
		dvdstruct->rmi = copy_data->region_info;
		dvdstruct->length = 0;

		break;
	}
	default:
		/*
		 * Tell the user what the overall length is, no matter
		 * what we can actually fit in the data buffer.
		 */
		dvdstruct->length = length - ccb->csio.resid -
			sizeof(struct scsi_read_dvd_struct_data_header);

		/*
		 * But only actually copy out the smaller of what we read
		 * in or what the structure can take.
		 */
		bcopy(databuf + sizeof(struct scsi_read_dvd_struct_data_header),
		      dvdstruct->data,
		      min(sizeof(dvdstruct->data), dvdstruct->length));
		break;
	}

bailout:
	xpt_release_ccb(ccb);
	cam_periph_unlock(periph);

	if (databuf != NULL)
		free(databuf, M_DEVBUF);

	return(error);
}