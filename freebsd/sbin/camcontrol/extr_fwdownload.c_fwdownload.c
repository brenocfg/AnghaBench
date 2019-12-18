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
typedef  union ccb {int dummy; } ccb ;
struct fw_vendor {scalar_t__ type; int timeout_ms; size_t timeout_type; } ;
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;
typedef  char ata_params ;
typedef  scalar_t__ camcontrol_devtype ;
struct TYPE_2__ {char* timeout_desc; } ;

/* Variables and functions */
 scalar_t__ CC_DT_ATA ; 
 scalar_t__ CC_DT_SATL ; 
 scalar_t__ CC_DT_SCSI ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 scalar_t__ VENDOR_UNKNOWN ; 
 scalar_t__ ata_do_identify (struct cam_device*,int,int,union ccb*,char**) ; 
 int /*<<< orphan*/  ata_print_ident (char*) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int /*<<< orphan*/  camxferrate (struct cam_device*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fw_download_img (struct cam_device*,struct fw_vendor*,char*,int,int,int,int,int,int,char*,scalar_t__) ; 
 int fw_get_timeout (struct cam_device*,struct fw_vendor*,int,int,int) ; 
 struct fw_vendor* fw_get_vendor (struct cam_device*,char*) ; 
 char* fw_read_img (struct cam_device*,int,int,int,char*,struct fw_vendor*,int*) ; 
 TYPE_1__* fw_timeout_desc_table ; 
 int /*<<< orphan*/  get_confirmation () ; 
 int get_device_type (struct cam_device*,int,int,int,scalar_t__*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsidoinquiry (struct cam_device*,int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
fwdownload(struct cam_device *device, int argc, char **argv,
    char *combinedopt, int printerrors, int task_attr, int retry_count,
    int timeout)
{
	union ccb *ccb = NULL;
	struct fw_vendor *vp;
	char *fw_img_path = NULL;
	struct ata_params *ident_buf = NULL;
	camcontrol_devtype devtype;
	char *buf = NULL;
	int img_size;
	int c;
	int sim_mode = 0;
	int confirmed = 0;
	int quiet = 0;
	int retval = 0;

	while ((c = getopt(argc, argv, combinedopt)) != -1) {
		switch (c) {
		case 'f':
			fw_img_path = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		case 's':
			sim_mode = 1;
			break;
		case 'y':
			confirmed = 1;
			break;
		default:
			break;
		}
	}

	if (fw_img_path == NULL)
		errx(1, "you must specify a firmware image file using -f "
		     "option");

	retval = get_device_type(device, retry_count, timeout, printerrors,
				 &devtype);
	if (retval != 0)
		errx(1, "Unable to determine device type");

	if ((devtype == CC_DT_ATA)
	 || (devtype == CC_DT_SATL)) {
		ccb = cam_getccb(device);
		if (ccb == NULL) {
			warnx("couldn't allocate CCB");
			retval = 1;
			goto bailout;
		}

		if (ata_do_identify(device, retry_count, timeout, ccb,
		    		    &ident_buf) != 0) {
			retval = 1;
			goto bailout;
		}
	} else if (devtype != CC_DT_SCSI)
		errx(1, "Unsupported device type %d", devtype);

	vp = fw_get_vendor(device, ident_buf);
	/*
	 * Bail out if we have an unknown vendor and this isn't an ATA
	 * disk.  For a SCSI disk, we have no chance of working properly
	 * with the default values in the VENDOR_UNKNOWN case.  For an ATA
	 * disk connected via an ATA transport, we may work for drives that
	 * support the ATA_DOWNLOAD_MICROCODE command.
	 */
	if (((vp == NULL)
	  || (vp->type == VENDOR_UNKNOWN))
	 && (devtype == CC_DT_SCSI))
		errx(1, "Unsupported device");

	retval = fw_get_timeout(device, vp, task_attr, retry_count, timeout);
	if (retval != 0) {
		warnx("Unable to get a firmware download timeout value");
		goto bailout;
	}

	buf = fw_read_img(device, retry_count, timeout, quiet, fw_img_path,
	    vp, &img_size);
	if (buf == NULL) {
		retval = 1;
		goto bailout;
	}

	if (!confirmed) {
		fprintf(stdout, "You are about to download firmware image (%s)"
		    " into the following device:\n",
		    fw_img_path);
		if (devtype == CC_DT_SCSI) {
			if (scsidoinquiry(device, argc, argv, combinedopt,
					  MSG_SIMPLE_Q_TAG, 0, 5000) != 0) {
				warnx("Error sending inquiry");
				retval = 1;
				goto bailout;
			}
		} else {
			printf("%s%d: ", device->device_name,
			    device->dev_unit_num);
			ata_print_ident(ident_buf);
			camxferrate(device);
			free(ident_buf);
		}
		fprintf(stdout, "Using a timeout of %u ms, which is %s.\n",
			vp->timeout_ms,
			fw_timeout_desc_table[vp->timeout_type].timeout_desc);
		fprintf(stdout, "\nIt may damage your drive. ");
		if (!get_confirmation()) {
			retval = 1;
			goto bailout;
		}
	}
	if ((sim_mode != 0) && (quiet == 0))
		fprintf(stdout, "Running in simulation mode\n");

	if (fw_download_img(device, vp, buf, img_size, sim_mode, printerrors,
	    quiet, retry_count, vp->timeout_ms, fw_img_path, devtype) != 0) {
		fprintf(stderr, "Firmware download failed\n");
		retval = 1;
		goto bailout;
	} else if (quiet == 0)
		fprintf(stdout, "Firmware download successful\n");

bailout:
	cam_freeccb(ccb);
	free(buf);
	return (retval);
}