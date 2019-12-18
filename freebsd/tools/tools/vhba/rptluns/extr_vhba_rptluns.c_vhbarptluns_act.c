#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* rpbitmap; char* disk; TYPE_2__* vhba; } ;
typedef  TYPE_3__ vhbarptluns_t ;
typedef  int uint8_t ;
typedef  size_t uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {scalar_t__ target_id; int target_lun; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int* cdb_bytes; } ;
struct ccb_scsiio {char sense_data; unsigned int dxfer_len; char* data_ptr; int resid; scalar_t__ scsi_status; TYPE_6__ ccb_h; TYPE_1__ cdb_io; } ;
typedef  size_t last_blk ;
typedef  int /*<<< orphan*/  junk ;
struct TYPE_10__ {int /*<<< orphan*/  tqe; } ;
struct TYPE_8__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_AUTOSNS_VALID ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  CAM_SEL_TIMEOUT ; 
 int /*<<< orphan*/  CAM_STATUS_MASK ; 
 int DISK_NBLKS ; 
 int DISK_SHIFT ; 
 int INQUIRY ; 
 int MAX_LUN ; 
 scalar_t__ MAX_TGT ; 
#define  MODE_SENSE 143 
#define  MODE_SENSE_10 142 
 int PSEUDO_HDS ; 
 int PSEUDO_SPC ; 
 int PSEUDO_SPT ; 
#define  READ_10 141 
#define  READ_12 140 
#define  READ_16 139 
#define  READ_6 138 
#define  READ_CAPACITY 137 
 int REPORT_LUNS ; 
 int REQUEST_SENSE ; 
 scalar_t__ SCSI_STATUS_CHECK_COND ; 
 scalar_t__ SCSI_STATUS_OK ; 
#define  SMS_ALL_PAGES_PAGE 136 
#define  SMS_CACHE_PAGE 135 
#define  SMS_CONTROL_MODE_PAGE 134 
 int SMS_DBD ; 
#define  SMS_FORMAT_DEVICE_PAGE 133 
#define  SMS_GEOMETRY_PAGE 132 
 int SMS_PAGE_CODE ; 
 int SMS_PAGE_CTRL_CHANGEABLE ; 
 int SMS_PAGE_CTRL_MASK ; 
 int /*<<< orphan*/  SSD_KEY_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SSD_KEY_UNIT_ATTENTION ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int min (int,unsigned int) ; 
 TYPE_5__ sim_links ; 
 int /*<<< orphan*/  vhba_default_cmd (struct ccb_scsiio*,int,int*) ; 
 int /*<<< orphan*/  vhba_fill_sense (struct ccb_scsiio*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vhba_rwparm (int*,size_t*,int*,int,int) ; 

__attribute__((used)) static void
vhbarptluns_act(vhbarptluns_t *vhbas, struct ccb_scsiio *csio)
{
	char junk[128];
	uint8_t *cdb, *ptr, status;
	uint32_t data_len;
	uint64_t off;
	int i, attached_lun = 0;
	    
	data_len = 0;
	status = SCSI_STATUS_OK;

	memset(&csio->sense_data, 0, sizeof (csio->sense_data));
	cdb = csio->cdb_io.cdb_bytes;

	if (csio->ccb_h.target_id >= MAX_TGT) {
		csio->ccb_h.status = CAM_SEL_TIMEOUT;
		TAILQ_INSERT_TAIL(&vhbas->vhba->done, &csio->ccb_h, sim_links.tqe);
		return;
	}

	if (csio->ccb_h.target_lun < MAX_LUN) {
		i = csio->ccb_h.target_lun & 0x7;
		if (vhbas->rpbitmap[csio->ccb_h.target_lun >> 3] & (1 << i)) {
			attached_lun = 1;
		}
	}
	if (attached_lun == 0 && cdb[0] != INQUIRY && cdb[0] != REPORT_LUNS && cdb[0] != REQUEST_SENSE) {
		vhba_fill_sense(csio, SSD_KEY_ILLEGAL_REQUEST, 0x25, 0x0);
		TAILQ_INSERT_TAIL(&vhbas->vhba->done, &csio->ccb_h, sim_links.tqe);
		return;
	}

	switch (cdb[0]) {
	case MODE_SENSE:
	case MODE_SENSE_10:
	{
		unsigned int nbyte;
		uint8_t page = cdb[2] & SMS_PAGE_CODE;
		uint8_t pgctl = cdb[2] & SMS_PAGE_CTRL_MASK;

		switch (page) {
		case SMS_FORMAT_DEVICE_PAGE:
		case SMS_GEOMETRY_PAGE:
		case SMS_CACHE_PAGE:
		case SMS_CONTROL_MODE_PAGE:
		case SMS_ALL_PAGES_PAGE:
			break;
		default:
			vhba_fill_sense(csio, SSD_KEY_ILLEGAL_REQUEST, 0x24, 0x0);
			TAILQ_INSERT_TAIL(&vhbas->vhba->done, &csio->ccb_h, sim_links.tqe);
			return;
		}
		memset(junk, 0, sizeof (junk));
		if (cdb[1] & SMS_DBD) {
			ptr = &junk[4];
		} else {
			ptr = junk;
			ptr[3] = 8;
			ptr[4] = ((1 << DISK_SHIFT) >> 24) & 0xff;
			ptr[5] = ((1 << DISK_SHIFT) >> 16) & 0xff;
			ptr[6] = ((1 << DISK_SHIFT) >>  8) & 0xff;
			ptr[7] = ((1 << DISK_SHIFT)) & 0xff;

			ptr[8] = (DISK_NBLKS >> 24) & 0xff;
			ptr[9] = (DISK_NBLKS >> 16) & 0xff;
			ptr[10] = (DISK_NBLKS >> 8) & 0xff;
			ptr[11] = DISK_NBLKS & 0xff;
			ptr += 12;
		}

		if (page == SMS_ALL_PAGES_PAGE || page == SMS_FORMAT_DEVICE_PAGE) {
			ptr[0] = SMS_FORMAT_DEVICE_PAGE;
			ptr[1] = 24;
			if (pgctl != SMS_PAGE_CTRL_CHANGEABLE) {
				/* tracks per zone */
				/* ptr[2] = 0; */
				/* ptr[3] = 0; */
				/* alternate sectors per zone */
				/* ptr[4] = 0; */
				/* ptr[5] = 0; */
				/* alternate tracks per zone */
				/* ptr[6] = 0; */
				/* ptr[7] = 0; */
				/* alternate tracks per logical unit */
				/* ptr[8] = 0; */
				/* ptr[9] = 0; */
				/* sectors per track */
				ptr[10] = (PSEUDO_SPT >> 8) & 0xff;
				ptr[11] = PSEUDO_SPT & 0xff;
				/* data bytes per physical sector */
				ptr[12] = ((1 << DISK_SHIFT) >> 8) & 0xff;
				ptr[13] = (1 << DISK_SHIFT) & 0xff;
				/* interleave */
				/* ptr[14] = 0; */
				/* ptr[15] = 1; */
				/* track skew factor */
				/* ptr[16] = 0; */
				/* ptr[17] = 0; */
				/* cylinder skew factor */
				/* ptr[18] = 0; */
				/* ptr[19] = 0; */
				/* SSRC, HSEC, RMB, SURF */
			}
			ptr += 26;
		}

		if (page == SMS_ALL_PAGES_PAGE || page == SMS_GEOMETRY_PAGE) {
			ptr[0] = SMS_GEOMETRY_PAGE;
			ptr[1] = 24;
			if (pgctl != SMS_PAGE_CTRL_CHANGEABLE) {
				uint32_t cyl = (DISK_NBLKS + ((PSEUDO_SPC - 1))) / PSEUDO_SPC;
				/* number of cylinders */
				ptr[2] = (cyl >> 24) & 0xff;
				ptr[3] = (cyl >> 16) & 0xff;
				ptr[4] = cyl & 0xff;
				/* number of heads */
				ptr[5] = PSEUDO_HDS;
				/* starting cylinder- write precompensation */
				/* ptr[6] = 0; */
				/* ptr[7] = 0; */
				/* ptr[8] = 0; */
				/* starting cylinder- reduced write current */
				/* ptr[9] = 0; */
				/* ptr[10] = 0; */
				/* ptr[11] = 0; */
				/* drive step rate */
				/* ptr[12] = 0; */
				/* ptr[13] = 0; */
				/* landing zone cylinder */
				/* ptr[14] = 0; */
				/* ptr[15] = 0; */
				/* ptr[16] = 0; */
				/* RPL */
				/* ptr[17] = 0; */
				/* rotational offset */
				/* ptr[18] = 0; */
				/* medium rotation rate -  7200 RPM */
				ptr[20] = 0x1c;
				ptr[21] = 0x20;
			}
			ptr += 26;
		}

		if (page == SMS_ALL_PAGES_PAGE || page == SMS_CACHE_PAGE) {
			ptr[0] = SMS_CACHE_PAGE;
			ptr[1] = 18;
			ptr[2] = 1 << 2;
			ptr += 20;
		}

		if (page == SMS_ALL_PAGES_PAGE || page == SMS_CONTROL_MODE_PAGE) {
			ptr[0] = SMS_CONTROL_MODE_PAGE;
			ptr[1] = 10;
			if (pgctl != SMS_PAGE_CTRL_CHANGEABLE) {
				ptr[3] = 1 << 4; /* unrestricted reordering allowed */
				ptr[8] = 0x75;   /* 30000 ms */
				ptr[9] = 0x30;
			}
			ptr += 12;
		}
		nbyte = (char *)ptr - &junk[0];
		ptr[0] = nbyte - 4;

		if (cdb[0] == MODE_SENSE) {
			data_len = min(cdb[4], csio->dxfer_len);
		} else {
			uint16_t tw = (cdb[7] << 8) | cdb[8];
			data_len = min(tw, csio->dxfer_len);
		}
		data_len = min(data_len, nbyte);
		if (data_len) {
			memcpy(csio->data_ptr, junk, data_len);
		}
		csio->resid = csio->dxfer_len - data_len;
		break;
	}
	case READ_6:
	case READ_10:
	case READ_12:
	case READ_16:
	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
	case WRITE_16:
		if (vhba_rwparm(cdb, &off, &data_len, DISK_NBLKS, DISK_SHIFT)) {
			vhba_fill_sense(csio, SSD_KEY_ILLEGAL_REQUEST, 0x24, 0x0);
			break;
		}
		if (data_len) {
			if ((cdb[0] & 0xf) == 8) {
				memcpy(csio->data_ptr, &vhbas->disk[off], data_len);
			} else {
				memcpy(&vhbas->disk[off], csio->data_ptr, data_len);
			}
			csio->resid = csio->dxfer_len - data_len;
		} else {
			csio->resid = csio->dxfer_len;
		}
		break;
		break;

	case READ_CAPACITY:
		if (cdb[2] || cdb[3] || cdb[4] || cdb[5]) {
			vhba_fill_sense(csio, SSD_KEY_UNIT_ATTENTION, 0x24, 0x0);
			break;
		}
		if (cdb[8] & 0x1) { /* PMI */
			csio->data_ptr[0] = 0xff;
			csio->data_ptr[1] = 0xff;
			csio->data_ptr[2] = 0xff;
			csio->data_ptr[3] = 0xff;
		} else {
			uint64_t last_blk = DISK_NBLKS - 1;
			if (last_blk < 0xffffffffULL) {
			    csio->data_ptr[0] = (last_blk >> 24) & 0xff;
			    csio->data_ptr[1] = (last_blk >> 16) & 0xff;
			    csio->data_ptr[2] = (last_blk >>  8) & 0xff;
			    csio->data_ptr[3] = (last_blk) & 0xff;
			} else {
			    csio->data_ptr[0] = 0xff;
			    csio->data_ptr[1] = 0xff;
			    csio->data_ptr[2] = 0xff;
			    csio->data_ptr[3] = 0xff;
			}
		}
		csio->data_ptr[4] = ((1 << DISK_SHIFT) >> 24) & 0xff;
		csio->data_ptr[5] = ((1 << DISK_SHIFT) >> 16) & 0xff;
		csio->data_ptr[6] = ((1 << DISK_SHIFT) >>  8) & 0xff;
		csio->data_ptr[7] = ((1 << DISK_SHIFT)) & 0xff;
		break;

	default:
		vhba_default_cmd(csio, MAX_LUN, vhbas->rpbitmap);
		break;
	}
	csio->ccb_h.status &= ~CAM_STATUS_MASK;
	if (csio->scsi_status != SCSI_STATUS_OK) {
		csio->ccb_h.status |= CAM_SCSI_STATUS_ERROR;
		if (csio->scsi_status == SCSI_STATUS_CHECK_COND) {
			csio->ccb_h.status |= CAM_AUTOSNS_VALID;
		}
	} else {
		csio->scsi_status = SCSI_STATUS_OK;
		csio->ccb_h.status |= CAM_REQ_CMP;
	}
	TAILQ_INSERT_TAIL(&vhbas->vhba->done, &csio->ccb_h, sim_links.tqe);
}