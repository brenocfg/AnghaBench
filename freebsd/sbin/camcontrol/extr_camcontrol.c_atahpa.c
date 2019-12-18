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
typedef  scalar_t__ u_int64_t ;
struct ccb_getdev {int dummy; } ;
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;
struct ata_set_max_pwd {int /*<<< orphan*/  password; } ;
struct TYPE_2__ {int command1; int command2; } ;
struct ata_params {TYPE_1__ support; } ;
typedef  int /*<<< orphan*/  pwd ;

/* Variables and functions */
#define  ATA_HPA_ACTION_FREEZE_LOCK 132 
#define  ATA_HPA_ACTION_LOCK 131 
 int ATA_HPA_ACTION_PRINT ; 
#define  ATA_HPA_ACTION_SET_MAX 130 
#define  ATA_HPA_ACTION_SET_PWD 129 
#define  ATA_HPA_ACTION_UNLOCK 128 
 int ATA_SUPPORT_ADDRESS48 ; 
 int ATA_SUPPORT_MAXSECURITY ; 
 int ATA_SUPPORT_PROTECTED ; 
 int ata_do_identify (struct cam_device*,int,int,union ccb*,struct ata_params**) ; 
 int /*<<< orphan*/  ata_getpwd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int ata_read_native_max (struct cam_device*,int,int,union ccb*,struct ata_params*,scalar_t__*) ; 
 int atahpa_freeze_lock (struct cam_device*,int,int,union ccb*,int) ; 
 int atahpa_lock (struct cam_device*,int,int,union ccb*,int) ; 
 int atahpa_password (struct cam_device*,int,int,union ccb*,int,struct ata_set_max_pwd*) ; 
 int /*<<< orphan*/  atahpa_print (struct ata_params*,scalar_t__,int) ; 
 int /*<<< orphan*/  atahpa_set_confirm (struct cam_device*,struct ata_params*,scalar_t__,int) ; 
 int atahpa_set_max (struct cam_device*,int,int,union ccb*,int,scalar_t__,int) ; 
 int atahpa_unlock (struct cam_device*,int,int,union ccb*,int,struct ata_set_max_pwd*) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int /*<<< orphan*/  camxferrate (struct cam_device*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (struct ata_params*) ; 
 scalar_t__ get_cgd (struct cam_device*,struct ccb_getdev*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct ata_set_max_pwd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  reprobe (struct cam_device*) ; 
 scalar_t__ strtoumax (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
atahpa(struct cam_device *device, int retry_count, int timeout,
       int argc, char **argv, char *combinedopt)
{
	union ccb *ccb;
	struct ata_params *ident_buf;
	struct ccb_getdev cgd;
	struct ata_set_max_pwd pwd;
	int error, confirm, quiet, c, action, actions, persist;
	int security, is48bit, pwdsize;
	u_int64_t hpasize, maxsize;

	actions = 0;
	confirm = 0;
	quiet = 0;
	maxsize = 0;
	persist = 0;
	security = 0;

	memset(&pwd, 0, sizeof(pwd));

	/* default action is to print hpa information */
	action = ATA_HPA_ACTION_PRINT;
	pwdsize = sizeof(pwd.password);

	while ((c = getopt(argc, argv, combinedopt)) != -1) {
		switch(c){
		case 's':
			action = ATA_HPA_ACTION_SET_MAX;
			maxsize = strtoumax(optarg, NULL, 0);
			actions++;
			break;

		case 'p':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			action = ATA_HPA_ACTION_SET_PWD;
			security = 1;
			actions++;
			break;

		case 'l':
			action = ATA_HPA_ACTION_LOCK;
			security = 1;
			actions++;
			break;

		case 'U':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			action = ATA_HPA_ACTION_UNLOCK;
			security = 1;
			actions++;
			break;

		case 'f':
			action = ATA_HPA_ACTION_FREEZE_LOCK;
			security = 1;
			actions++;
			break;

		case 'P':
			persist = 1;
			break;

		case 'y':
			confirm++;
			break;

		case 'q':
			quiet++;
			break;
		}
	}

	if (actions > 1) {
		warnx("too many hpa actions specified");
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

	if (action == ATA_HPA_ACTION_PRINT) {
		hpasize = 0;
		if (ident_buf->support.command1 & ATA_SUPPORT_PROTECTED)
			ata_read_native_max(device, retry_count, timeout, ccb,
				    ident_buf, &hpasize);
		atahpa_print(ident_buf, hpasize, 1);

		cam_freeccb(ccb);
		free(ident_buf);
		return (error);
	}

	if (!(ident_buf->support.command1 & ATA_SUPPORT_PROTECTED)) {
		warnx("HPA is not supported by this device");
		cam_freeccb(ccb);
		free(ident_buf);
		return (1);
	}

	if (security && !(ident_buf->support.command2 & ATA_SUPPORT_MAXSECURITY)) {
		warnx("HPA Security is not supported by this device");
		cam_freeccb(ccb);
		free(ident_buf);
		return (1);
	}

	is48bit = ident_buf->support.command2 & ATA_SUPPORT_ADDRESS48;

	/*
	 * The ATA spec requires:
	 * 1. Read native max addr is called directly before set max addr
	 * 2. Read native max addr is NOT called before any other set max call
	 */
	switch(action) {
	case ATA_HPA_ACTION_SET_MAX:
		if (confirm == 0 &&
		    atahpa_set_confirm(device, ident_buf, maxsize,
		    persist) == 0) {
			cam_freeccb(ccb);
			free(ident_buf);
			return (1);
		}

		error = ata_read_native_max(device, retry_count, timeout,
					    ccb, ident_buf, &hpasize);
		if (error == 0) {
			error = atahpa_set_max(device, retry_count, timeout,
					       ccb, is48bit, maxsize, persist);
			if (error == 0) {
				if (quiet == 0) {
					/* redo identify to get new values */
					error = ata_do_identify(device,
					    retry_count, timeout, ccb,
					    &ident_buf);
					atahpa_print(ident_buf, hpasize, 1);
				}
				/* Hint CAM to reprobe the device. */
				reprobe(device);
			}
		}
		break;

	case ATA_HPA_ACTION_SET_PWD:
		error = atahpa_password(device, retry_count, timeout,
					ccb, is48bit, &pwd);
		if (error == 0 && quiet == 0)
			printf("HPA password has been set\n");
		break;

	case ATA_HPA_ACTION_LOCK:
		error = atahpa_lock(device, retry_count, timeout,
				    ccb, is48bit);
		if (error == 0 && quiet == 0)
			printf("HPA has been locked\n");
		break;

	case ATA_HPA_ACTION_UNLOCK:
		error = atahpa_unlock(device, retry_count, timeout,
				      ccb, is48bit, &pwd);
		if (error == 0 && quiet == 0)
			printf("HPA has been unlocked\n");
		break;

	case ATA_HPA_ACTION_FREEZE_LOCK:
		error = atahpa_freeze_lock(device, retry_count, timeout,
					   ccb, is48bit);
		if (error == 0 && quiet == 0)
			printf("HPA has been frozen\n");
		break;

	default:
		errx(1, "Option currently not supported");
	}

	cam_freeccb(ccb);
	free(ident_buf);

	return (error);
}