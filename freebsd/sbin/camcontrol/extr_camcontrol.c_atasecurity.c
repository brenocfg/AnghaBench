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
struct cam_device {char* device_name; int /*<<< orphan*/  dev_unit_num; } ;
struct ata_security_password {int ctrl; int revision; int /*<<< orphan*/  password; } ;
struct TYPE_2__ {int command1; } ;
struct ata_params {int security_status; int master_passwd_revision; int /*<<< orphan*/  enhanced_erase_time; int /*<<< orphan*/  erase_time; TYPE_1__ support; } ;
typedef  int /*<<< orphan*/  pwd ;

/* Variables and functions */
#define  ATA_SECURITY_ACTION_DISABLE 132 
#define  ATA_SECURITY_ACTION_ERASE 131 
#define  ATA_SECURITY_ACTION_ERASE_ENHANCED 130 
#define  ATA_SECURITY_ACTION_FREEZE 129 
 int ATA_SECURITY_ACTION_PRINT ; 
 int ATA_SECURITY_ACTION_SET_PASSWORD ; 
#define  ATA_SECURITY_ACTION_UNLOCK 128 
 int ATA_SECURITY_ENABLED ; 
 int ATA_SECURITY_ENH_SUPP ; 
 int ATA_SECURITY_ERASE_ENHANCED ; 
 int ATA_SECURITY_LEVEL_HIGH ; 
 int ATA_SECURITY_LEVEL_MAXIMUM ; 
 int ATA_SECURITY_LOCKED ; 
 int ATA_SECURITY_PASSWORD_MASTER ; 
 int ATA_SECURITY_PASSWORD_USER ; 
 int ATA_SUPPORT_SECURITY ; 
 int ata_do_identify (struct cam_device*,int,int,union ccb*,struct ata_params**) ; 
 int /*<<< orphan*/  ata_getpwd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ata_print_ident (struct ata_params*) ; 
 int atasecurity_disable (struct cam_device*,union ccb*,int,int,struct ata_security_password*,int) ; 
 int atasecurity_erase (struct cam_device*,union ccb*,int,int,int,struct ata_security_password*,int) ; 
 scalar_t__ atasecurity_erase_confirm (struct cam_device*,struct ata_params*) ; 
 int atasecurity_erase_timeout_msecs (int /*<<< orphan*/ ) ; 
 int atasecurity_freeze (struct cam_device*,union ccb*,int,int,int) ; 
 int /*<<< orphan*/  atasecurity_print (struct ata_params*) ; 
 int atasecurity_set_password (struct cam_device*,union ccb*,int,int,struct ata_security_password*,int) ; 
 int atasecurity_unlock (struct cam_device*,union ccb*,int,int,struct ata_security_password*,int) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 int /*<<< orphan*/  camxferrate (struct cam_device*) ; 
 int /*<<< orphan*/  free (struct ata_params*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (struct ata_security_password*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
atasecurity(struct cam_device *device, int retry_count, int timeout,
	    int argc, char **argv, char *combinedopt)
{
	union ccb *ccb;
	struct ata_params *ident_buf;
	int error, confirm, quiet, c, action, actions, setpwd;
	int security_enabled, erase_timeout, pwdsize;
	struct ata_security_password pwd;

	actions = 0;
	setpwd = 0;
	erase_timeout = 0;
	confirm = 0;
	quiet = 0;

	memset(&pwd, 0, sizeof(pwd));

	/* default action is to print security information */
	action = ATA_SECURITY_ACTION_PRINT;

	/* user is master by default as its safer that way */
	pwd.ctrl |= ATA_SECURITY_PASSWORD_MASTER;
	pwdsize = sizeof(pwd.password);

	while ((c = getopt(argc, argv, combinedopt)) != -1) {
		switch(c){
		case 'f':
			action = ATA_SECURITY_ACTION_FREEZE;
			actions++;
			break;

		case 'U':
			if (strcasecmp(optarg, "user") == 0) {
				pwd.ctrl |= ATA_SECURITY_PASSWORD_USER;
				pwd.ctrl &= ~ATA_SECURITY_PASSWORD_MASTER;
			} else if (strcasecmp(optarg, "master") == 0) {
				pwd.ctrl |= ATA_SECURITY_PASSWORD_MASTER;
				pwd.ctrl &= ~ATA_SECURITY_PASSWORD_USER;
			} else {
				warnx("-U argument '%s' is invalid (must be "
				      "'user' or 'master')", optarg);
				return (1);
			}
			break;

		case 'l':
			if (strcasecmp(optarg, "high") == 0) {
				pwd.ctrl |= ATA_SECURITY_LEVEL_HIGH;
				pwd.ctrl &= ~ATA_SECURITY_LEVEL_MAXIMUM;
			} else if (strcasecmp(optarg, "maximum") == 0) {
				pwd.ctrl |= ATA_SECURITY_LEVEL_MAXIMUM;
				pwd.ctrl &= ~ATA_SECURITY_LEVEL_HIGH;
			} else {
				warnx("-l argument '%s' is unknown (must be "
				      "'high' or 'maximum')", optarg);
				return (1);
			}
			break;

		case 'k':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			action = ATA_SECURITY_ACTION_UNLOCK;
			actions++;
			break;

		case 'd':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			action = ATA_SECURITY_ACTION_DISABLE;
			actions++;
			break;

		case 'e':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			action = ATA_SECURITY_ACTION_ERASE;
			actions++;
			break;

		case 'h':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			pwd.ctrl |= ATA_SECURITY_ERASE_ENHANCED;
			action = ATA_SECURITY_ACTION_ERASE_ENHANCED;
			actions++;
			break;

		case 's':
			if (ata_getpwd(pwd.password, pwdsize, c) != 0)
				return (1);
			setpwd = 1;
			if (action == ATA_SECURITY_ACTION_PRINT)
				action = ATA_SECURITY_ACTION_SET_PASSWORD;
			/*
			 * Don't increment action as this can be combined
			 * with other actions.
			 */
			break;

		case 'y':
			confirm++;
			break;

		case 'q':
			quiet++;
			break;

		case 'T':
			erase_timeout = atoi(optarg) * 1000;
			break;
		}
	}

	if (actions > 1) {
		warnx("too many security actions specified");
		return (1);
	}

	if ((ccb = cam_getccb(device)) == NULL) {
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

	if (action == ATA_SECURITY_ACTION_PRINT) {
		atasecurity_print(ident_buf);
		free(ident_buf);
		cam_freeccb(ccb);
		return (0);
	}

	if ((ident_buf->support.command1 & ATA_SUPPORT_SECURITY) == 0) {
		warnx("Security not supported");
		free(ident_buf);
		cam_freeccb(ccb);
		return (1);
	}

	/* default timeout 15 seconds the same as linux hdparm */
	timeout = timeout ? timeout : 15 * 1000;

	security_enabled = ident_buf->security_status & ATA_SECURITY_ENABLED;

	/* first set the password if requested */
	if (setpwd == 1) {
		/* confirm we can erase before setting the password if erasing */
		if (confirm == 0 &&
		    (action == ATA_SECURITY_ACTION_ERASE_ENHANCED ||
		    action == ATA_SECURITY_ACTION_ERASE) &&
		    atasecurity_erase_confirm(device, ident_buf) == 0) {
			cam_freeccb(ccb);
			free(ident_buf);
			return (error);
		}

		if (pwd.ctrl & ATA_SECURITY_PASSWORD_MASTER) {
			pwd.revision = ident_buf->master_passwd_revision;
			if (pwd.revision != 0 && pwd.revision != 0xfff &&
			    --pwd.revision == 0) {
				pwd.revision = 0xfffe;
			}
		}
		error = atasecurity_set_password(device, ccb, retry_count,
						 timeout, &pwd, quiet);
		if (error != 0) {
			cam_freeccb(ccb);
			free(ident_buf);
			return (error);
		}
		security_enabled = 1;
	}

	switch(action) {
	case ATA_SECURITY_ACTION_FREEZE:
		error = atasecurity_freeze(device, ccb, retry_count,
					   timeout, quiet);
		break;

	case ATA_SECURITY_ACTION_UNLOCK:
		if (security_enabled) {
			if (ident_buf->security_status & ATA_SECURITY_LOCKED) {
				error = atasecurity_unlock(device, ccb,
					retry_count, timeout, &pwd, quiet);
			} else {
				warnx("Can't unlock, drive is not locked");
				error = 1;
			}
		} else {
			warnx("Can't unlock, security is disabled");
			error = 1;
		}
		break;

	case ATA_SECURITY_ACTION_DISABLE:
		if (security_enabled) {
			/* First unlock the drive if its locked */
			if (ident_buf->security_status & ATA_SECURITY_LOCKED) {
				error = atasecurity_unlock(device, ccb,
							   retry_count,
							   timeout,
							   &pwd,
							   quiet);
			}

			if (error == 0) {
				error = atasecurity_disable(device,
							    ccb,
							    retry_count,
							    timeout,
							    &pwd,
							    quiet);
			}
		} else {
			warnx("Can't disable security (already disabled)");
			error = 1;
		}
		break;

	case ATA_SECURITY_ACTION_ERASE:
		if (security_enabled) {
			if (erase_timeout == 0) {
				erase_timeout = atasecurity_erase_timeout_msecs(
				    ident_buf->erase_time);
			}

			error = atasecurity_erase(device, ccb, retry_count,
			    timeout, erase_timeout, &pwd, quiet);
		} else {
			warnx("Can't secure erase (security is disabled)");
			error = 1;
		}
		break;

	case ATA_SECURITY_ACTION_ERASE_ENHANCED:
		if (security_enabled) {
			if (ident_buf->security_status & ATA_SECURITY_ENH_SUPP) {
				if (erase_timeout == 0) {
					erase_timeout =
					    atasecurity_erase_timeout_msecs(
						ident_buf->enhanced_erase_time);
				}

				error = atasecurity_erase(device, ccb,
							  retry_count, timeout,
							  erase_timeout, &pwd,
							  quiet);
			} else {
				warnx("Enhanced erase is not supported");
				error = 1;
			}
		} else {
			warnx("Can't secure erase (enhanced), "
			      "(security is disabled)");
			error = 1;
		}
		break;
	}

	cam_freeccb(ccb);
	free(ident_buf);

	return (error);
}