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
typedef  union ccb {int dummy; } ccb ;
typedef  scalar_t__ u_int64_t ;
struct ccb_getdev {int dummy; } ;
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;
struct ata_params {int support2; } ;

/* Variables and functions */
#define  ATA_AMA_ACTION_FREEZE_LOCK 129 
 int ATA_AMA_ACTION_PRINT ; 
#define  ATA_AMA_ACTION_SET_MAX 128 
 int ATA_SUPPORT_AMAX_ADDR ; 
 int ata_do_identify (struct cam_device*,int,int,union ccb*,struct ata_params**) ; 
 int ata_get_native_max (struct cam_device*,int,int,union ccb*,scalar_t__*) ; 
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int ataama_freeze (struct cam_device*,int,int,union ccb*) ; 
 int /*<<< orphan*/  ataama_print (struct ata_params*,scalar_t__,int) ; 
 int ataama_set (struct cam_device*,int,int,union ccb*,scalar_t__) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int /*<<< orphan*/  camxferrate (struct cam_device*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct ata_params*) ; 
 scalar_t__ get_cgd (struct cam_device*,struct ccb_getdev*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reprobe (struct cam_device*) ; 
 scalar_t__ strtoumax (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
ataama(struct cam_device *device, int retry_count, int timeout,
       int argc, char **argv, char *combinedopt)
{
	union ccb *ccb;
	struct ata_params *ident_buf;
	struct ccb_getdev cgd;
	int error, quiet, c, action, actions;
	u_int64_t nativesize, maxsize;

	actions = 0;
	quiet = 0;
	maxsize = 0;

	/* default action is to print AMA information */
	action = ATA_AMA_ACTION_PRINT;

	while ((c = getopt(argc, argv, combinedopt)) != -1) {
		switch(c){
		case 's':
			action = ATA_AMA_ACTION_SET_MAX;
			maxsize = strtoumax(optarg, NULL, 0);
			actions++;
			break;

		case 'f':
			action = ATA_AMA_ACTION_FREEZE_LOCK;
			actions++;
			break;

		case 'q':
			quiet++;
			break;
		}
	}

	if (actions > 1) {
		warnx("too many AMA actions specified");
		return (1);
	}

	if (get_cgd(device, &cgd) != 0) {
		warnx("couldn't get CGD");
		return (1);
	}

	ccb = cam_getccb(device);
	if (ccb == NULL) {
		warnx("couldn't allocate CCB");
		return (1);
	}

	error = ata_do_identify(device, retry_count, timeout, ccb, &ident_buf);
	if (error != 0) {
		cam_freeccb(ccb);
		return (1);
	}

	if (quiet == 0) {
		printf("%s%d: ", device->device_name, device->dev_unit_num);
		ata_print_ident(ident_buf);
		camxferrate(device);
	}

	if (action == ATA_AMA_ACTION_PRINT) {
		nativesize = 0;
		if (ident_buf->support2 & ATA_SUPPORT_AMAX_ADDR)
			ata_get_native_max(device, retry_count, timeout, ccb,
					   &nativesize);
		ataama_print(ident_buf, nativesize, 1);

		cam_freeccb(ccb);
		free(ident_buf);
		return (error);
	}

	if (!(ident_buf->support2 & ATA_SUPPORT_AMAX_ADDR)) {
		warnx("Accessible Max Address is not supported by this device");
		cam_freeccb(ccb);
		free(ident_buf);
		return (1);
	}

	switch(action) {
	case ATA_AMA_ACTION_SET_MAX:
		error = ata_get_native_max(device, retry_count, timeout, ccb,
					   &nativesize);
		if (error == 0) {
			error = ataama_set(device, retry_count, timeout,
				       ccb, maxsize);
			if (error == 0) {
				if (quiet == 0) {
					/* redo identify to get new values */
					error = ata_do_identify(device,
					    retry_count, timeout, ccb,
					    &ident_buf);
					ataama_print(ident_buf, nativesize, 1);
				}
				/* Hint CAM to reprobe the device. */
				reprobe(device);
			}
		}
		break;

	case ATA_AMA_ACTION_FREEZE_LOCK:
		error = ataama_freeze(device, retry_count, timeout,
					   ccb);
		if (error == 0 && quiet == 0)
			printf("Accessible Max Address has been frozen\n");
		break;

	default:
		errx(1, "Option currently not supported");
	}

	cam_freeccb(ccb);
	free(ident_buf);

	return (error);
}