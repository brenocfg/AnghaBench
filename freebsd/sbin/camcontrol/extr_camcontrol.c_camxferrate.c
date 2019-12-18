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
struct ccb_trans_settings_scsi {int valid; int flags; } ;
struct TYPE_5__ {struct ccb_trans_settings_scsi scsi; } ;
struct ccb_trans_settings_sata {int valid; int revision; scalar_t__ atapi; int bytecount; int /*<<< orphan*/  mode; } ;
struct ccb_trans_settings_pata {int valid; scalar_t__ atapi; int bytecount; int /*<<< orphan*/  mode; } ;
struct ccb_trans_settings_spi {int valid; int bus_width; int sync_offset; int /*<<< orphan*/  sync_period; } ;
struct ccb_trans_settings_sas {int valid; int bitrate; } ;
struct ccb_trans_settings_fc {int valid; int bitrate; } ;
struct TYPE_7__ {struct ccb_trans_settings_sata sata; struct ccb_trans_settings_pata ata; struct ccb_trans_settings_spi spi; struct ccb_trans_settings_sas sas; struct ccb_trans_settings_fc fc; } ;
struct TYPE_8__ {scalar_t__ transport; scalar_t__ protocol; TYPE_1__ proto_specific; TYPE_3__ xport_specific; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int status; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_4__ cts; TYPE_2__ ccb_h; } ;
typedef  int u_int32_t ;
typedef  int u_int ;
struct ccb_pathinq {int base_transfer_speed; } ;
struct cam_device {char* device_name; int dev_unit_num; } ;

/* Variables and functions */
 int CAM_ARG_VERBOSE ; 
 int /*<<< orphan*/  CAM_EPF_ALL ; 
 int /*<<< orphan*/  CAM_ESF_ALL ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CCB_CLEAR_ALL_EXCEPT_HDR (TYPE_4__*) ; 
 int CTS_ATA_VALID_ATAPI ; 
 int CTS_ATA_VALID_BYTECOUNT ; 
 int CTS_ATA_VALID_MODE ; 
 int CTS_FC_VALID_SPEED ; 
 int CTS_SAS_VALID_SPEED ; 
 int CTS_SATA_VALID_ATAPI ; 
 int CTS_SATA_VALID_BYTECOUNT ; 
 int CTS_SATA_VALID_MODE ; 
 int CTS_SATA_VALID_REVISION ; 
 int CTS_SCSI_FLAGS_TAG_ENB ; 
 int CTS_SCSI_VALID_TQ ; 
 int CTS_SPI_VALID_BUS_WIDTH ; 
 int CTS_SPI_VALID_SYNC_OFFSET ; 
 int CTS_SPI_VALID_SYNC_RATE ; 
 int /*<<< orphan*/  CTS_TYPE_CURRENT_SETTINGS ; 
 scalar_t__ PROTO_SCSI ; 
 scalar_t__ XPORT_ATA ; 
 scalar_t__ XPORT_FC ; 
 scalar_t__ XPORT_SAS ; 
 scalar_t__ XPORT_SATA ; 
 scalar_t__ XPORT_SPI ; 
 int /*<<< orphan*/  XPT_GET_TRAN_SETTINGS ; 
 int arglist ; 
 int ata_mode2speed (int /*<<< orphan*/ ) ; 
 char* ata_mode2string (int /*<<< orphan*/ ) ; 
 int ata_revision2speed (int) ; 
 int /*<<< orphan*/  cam_error_print (struct cam_device*,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_cpi (struct cam_device*,struct ccb_pathinq*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scsi_calc_syncsrate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char const*) ; 
 int /*<<< orphan*/  warnx (char const*) ; 

int
camxferrate(struct cam_device *device)
{
	struct ccb_pathinq cpi;
	u_int32_t freq = 0;
	u_int32_t speed = 0;
	union ccb *ccb;
	u_int mb;
	int retval = 0;

	if ((retval = get_cpi(device, &cpi)) != 0)
		return (1);

	ccb = cam_getccb(device);

	if (ccb == NULL) {
		warnx("couldn't allocate CCB");
		return (1);
	}

	CCB_CLEAR_ALL_EXCEPT_HDR(&ccb->cts);

	ccb->ccb_h.func_code = XPT_GET_TRAN_SETTINGS;
	ccb->cts.type = CTS_TYPE_CURRENT_SETTINGS;

	if (((retval = cam_send_ccb(device, ccb)) < 0)
	 || ((ccb->ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP)) {
		const char error_string[] = "error getting transfer settings";

		if (retval < 0)
			warn(error_string);
		else
			warnx(error_string);

		if (arglist & CAM_ARG_VERBOSE)
			cam_error_print(device, ccb, CAM_ESF_ALL,
					CAM_EPF_ALL, stderr);

		retval = 1;

		goto xferrate_bailout;

	}

	speed = cpi.base_transfer_speed;
	freq = 0;
	if (ccb->cts.transport == XPORT_SPI) {
		struct ccb_trans_settings_spi *spi =
		    &ccb->cts.xport_specific.spi;

		if ((spi->valid & CTS_SPI_VALID_SYNC_RATE) != 0) {
			freq = scsi_calc_syncsrate(spi->sync_period);
			speed = freq;
		}
		if ((spi->valid & CTS_SPI_VALID_BUS_WIDTH) != 0) {
			speed *= (0x01 << spi->bus_width);
		}
	} else if (ccb->cts.transport == XPORT_FC) {
		struct ccb_trans_settings_fc *fc =
		    &ccb->cts.xport_specific.fc;

		if (fc->valid & CTS_FC_VALID_SPEED)
			speed = fc->bitrate;
	} else if (ccb->cts.transport == XPORT_SAS) {
		struct ccb_trans_settings_sas *sas =
		    &ccb->cts.xport_specific.sas;

		if (sas->valid & CTS_SAS_VALID_SPEED)
			speed = sas->bitrate;
	} else if (ccb->cts.transport == XPORT_ATA) {
		struct ccb_trans_settings_pata *pata =
		    &ccb->cts.xport_specific.ata;

		if (pata->valid & CTS_ATA_VALID_MODE)
			speed = ata_mode2speed(pata->mode);
	} else if (ccb->cts.transport == XPORT_SATA) {
		struct	ccb_trans_settings_sata *sata =
		    &ccb->cts.xport_specific.sata;

		if (sata->valid & CTS_SATA_VALID_REVISION)
			speed = ata_revision2speed(sata->revision);
	}

	mb = speed / 1000;
	if (mb > 0) {
		fprintf(stdout, "%s%d: %d.%03dMB/s transfers",
			device->device_name, device->dev_unit_num,
			mb, speed % 1000);
	} else {
		fprintf(stdout, "%s%d: %dKB/s transfers",
			device->device_name, device->dev_unit_num,
			speed);
	}

	if (ccb->cts.transport == XPORT_SPI) {
		struct ccb_trans_settings_spi *spi =
		    &ccb->cts.xport_specific.spi;

		if (((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) != 0)
		 && (spi->sync_offset != 0))
			fprintf(stdout, " (%d.%03dMHz, offset %d", freq / 1000,
				freq % 1000, spi->sync_offset);

		if (((spi->valid & CTS_SPI_VALID_BUS_WIDTH) != 0)
		 && (spi->bus_width > 0)) {
			if (((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) != 0)
			 && (spi->sync_offset != 0)) {
				fprintf(stdout, ", ");
			} else {
				fprintf(stdout, " (");
			}
			fprintf(stdout, "%dbit)", 8 * (0x01 << spi->bus_width));
		} else if (((spi->valid & CTS_SPI_VALID_SYNC_OFFSET) != 0)
		 && (spi->sync_offset != 0)) {
			fprintf(stdout, ")");
		}
	} else if (ccb->cts.transport == XPORT_ATA) {
		struct ccb_trans_settings_pata *pata =
		    &ccb->cts.xport_specific.ata;

		printf(" (");
		if (pata->valid & CTS_ATA_VALID_MODE)
			printf("%s, ", ata_mode2string(pata->mode));
		if ((pata->valid & CTS_ATA_VALID_ATAPI) && pata->atapi != 0)
			printf("ATAPI %dbytes, ", pata->atapi);
		if (pata->valid & CTS_ATA_VALID_BYTECOUNT)
			printf("PIO %dbytes", pata->bytecount);
		printf(")");
	} else if (ccb->cts.transport == XPORT_SATA) {
		struct ccb_trans_settings_sata *sata =
		    &ccb->cts.xport_specific.sata;

		printf(" (");
		if (sata->valid & CTS_SATA_VALID_REVISION)
			printf("SATA %d.x, ", sata->revision);
		else
			printf("SATA, ");
		if (sata->valid & CTS_SATA_VALID_MODE)
			printf("%s, ", ata_mode2string(sata->mode));
		if ((sata->valid & CTS_SATA_VALID_ATAPI) && sata->atapi != 0)
			printf("ATAPI %dbytes, ", sata->atapi);
		if (sata->valid & CTS_SATA_VALID_BYTECOUNT)
			printf("PIO %dbytes", sata->bytecount);
		printf(")");
	}

	if (ccb->cts.protocol == PROTO_SCSI) {
		struct ccb_trans_settings_scsi *scsi =
		    &ccb->cts.proto_specific.scsi;
		if (scsi->valid & CTS_SCSI_VALID_TQ) {
			if (scsi->flags & CTS_SCSI_FLAGS_TAG_ENB) {
				fprintf(stdout, ", Command Queueing Enabled");
			}
		}
	}

	fprintf(stdout, "\n");

xferrate_bailout:

	cam_freeccb(ccb);

	return (retval);
}