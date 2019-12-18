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
typedef  scalar_t__ ctladm_optret ;
typedef  int ctladm_cmdfunction ;
typedef  int ctladm_cmdargs ;

/* Variables and functions */
 scalar_t__ CC_OR_AMBIGUOUS ; 
 scalar_t__ CC_OR_NOT_FOUND ; 
 int CTLADM_ARG_DEVICE ; 
 int CTLADM_ARG_INITIATOR ; 
 int CTLADM_ARG_NEED_TL ; 
 int CTLADM_ARG_NONE ; 
 int CTLADM_ARG_RETRIES ; 
 int CTLADM_ARG_TARG_LUN ; 
#define  CTLADM_CMD_CREATE 158 
#define  CTLADM_CMD_DELAY 157 
#define  CTLADM_CMD_DEVLIST 156 
#define  CTLADM_CMD_DUMPOOA 155 
#define  CTLADM_CMD_DUMPSTRUCTS 154 
#define  CTLADM_CMD_ERR_INJECT 153 
#define  CTLADM_CMD_HELP 152 
#define  CTLADM_CMD_INQUIRY 151 
#define  CTLADM_CMD_INQ_VPD_DEVID 150 
#define  CTLADM_CMD_ISLIST 149 
#define  CTLADM_CMD_ISLOGOUT 148 
#define  CTLADM_CMD_ISTERMINATE 147 
#define  CTLADM_CMD_LUNLIST 146 
#define  CTLADM_CMD_LUNMAP 145 
#define  CTLADM_CMD_MODESENSE 144 
#define  CTLADM_CMD_MODIFY 143 
#define  CTLADM_CMD_PORT 142 
#define  CTLADM_CMD_PORTLIST 141 
#define  CTLADM_CMD_PRES_IN 140 
#define  CTLADM_CMD_PRES_OUT 139 
#define  CTLADM_CMD_READ 138 
#define  CTLADM_CMD_READCAPACITY 137 
#define  CTLADM_CMD_REPORT_LUNS 136 
#define  CTLADM_CMD_REQ_SENSE 135 
#define  CTLADM_CMD_RM 134 
#define  CTLADM_CMD_RTPG 133 
#define  CTLADM_CMD_START 132 
#define  CTLADM_CMD_STOP 131 
#define  CTLADM_CMD_SYNC_CACHE 130 
#define  CTLADM_CMD_TUR 129 
#define  CTLADM_CMD_WRITE 128 
 char* CTL_DEFAULT_DEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int cctl_create_lun (int,int,char**,char*) ; 
 int cctl_delay (int,int,int,char**,char*) ; 
 int cctl_devlist (int,int,char**,char*) ; 
 int cctl_dump_ooa (int,int,char**) ; 
 int cctl_dump_structs (int,int) ; 
 int cctl_error_inject (int,int,int,char**,char*) ; 
 int cctl_inquiry (int,int,int,int) ; 
 int cctl_inquiry_vpd_devid (int,int,int) ; 
 int cctl_islist (int,int,char**,char*) ; 
 int cctl_islogout (int,int,char**,char*) ; 
 int cctl_isterminate (int,int,char**,char*) ; 
 int cctl_lunlist (int) ; 
 int cctl_lunmap (int,int,char**,char*) ; 
 int cctl_mode_sense (int,int,int,int,int,char**,char*) ; 
 int cctl_modify_lun (int,int,char**,char*) ; 
 int cctl_persistent_reserve_in (int,int,int,int,char**,char*,int) ; 
 int cctl_persistent_reserve_out (int,int,int,int,char**,char*,int) ; 
 int cctl_port (int,int,char**,char*) ; 
 int cctl_portlist (int,int,char**,char*) ; 
 int cctl_read_capacity (int,int,int,int,int,char**,char*) ; 
 int cctl_read_write (int,int,int,int,int,char**,char*,int) ; 
 int cctl_report_luns (int,int,int,int) ; 
 int cctl_report_target_port_group (int,int,int) ; 
 int cctl_req_sense (int,int,int,int) ; 
 int cctl_rm_lun (int,int,char**,char*) ; 
 int cctl_start_stop (int,int,int,int,int,int,char**,char*) ; 
 int cctl_sync_cache (int,int,int,int,int,char**,char*) ; 
 int cctl_tur (int,int,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getoption (int /*<<< orphan*/ ,char*,int*,int*,char const**) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int kldload (char*) ; 
 int modfind (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  option_table ; 
 int optreset ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 char* strerror (int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	int c;
	ctladm_cmdfunction command;
	ctladm_cmdargs cmdargs;
	ctladm_optret optreturn;
	char *device;
	const char *mainopt = "C:D:I:";
	const char *subopt = NULL;
	char combinedopt[256];
	int lun;
	int optstart = 2;
	int retval, fd;
	int retries;
	int initid;
	int saved_errno;

	retval = 0;
	cmdargs = CTLADM_ARG_NONE;
	command = CTLADM_CMD_HELP;
	device = NULL;
	fd = -1;
	retries = 0;
	lun = 0;
	initid = 7;

	if (argc < 2) {
		usage(1);
		retval = 1;
		goto bailout;
	}

	/*
	 * Get the base option.
	 */
	optreturn = getoption(option_table,argv[1], &command, &cmdargs,&subopt);

	if (optreturn == CC_OR_AMBIGUOUS) {
		warnx("ambiguous option %s", argv[1]);
		usage(0);
		exit(1);
	} else if (optreturn == CC_OR_NOT_FOUND) {
		warnx("option %s not found", argv[1]);
		usage(0);
		exit(1);
	}

	if (cmdargs & CTLADM_ARG_NEED_TL) {
		if ((argc < 3) || (!isdigit(argv[2][0]))) {
			warnx("option %s requires a lun argument",
			      argv[1]);
			usage(0);
			exit(1);
		}
		lun = strtol(argv[2], NULL, 0);

		cmdargs |= CTLADM_ARG_TARG_LUN;
		optstart++;
	}

	/*
	 * Ahh, getopt(3) is a pain.
	 *
	 * This is a gross hack.  There really aren't many other good
	 * options (excuse the pun) for parsing options in a situation like
	 * this.  getopt is kinda braindead, so you end up having to run
	 * through the options twice, and give each invocation of getopt
	 * the option string for the other invocation.
	 *
	 * You would think that you could just have two groups of options.
	 * The first group would get parsed by the first invocation of
	 * getopt, and the second group would get parsed by the second
	 * invocation of getopt.  It doesn't quite work out that way.  When
	 * the first invocation of getopt finishes, it leaves optind pointing
	 * to the argument _after_ the first argument in the second group.
	 * So when the second invocation of getopt comes around, it doesn't
	 * recognize the first argument it gets and then bails out.
	 *
	 * A nice alternative would be to have a flag for getopt that says
	 * "just keep parsing arguments even when you encounter an unknown
	 * argument", but there isn't one.  So there's no real clean way to
	 * easily parse two sets of arguments without having one invocation
	 * of getopt know about the other.
	 *
	 * Without this hack, the first invocation of getopt would work as
	 * long as the generic arguments are first, but the second invocation
	 * (in the subfunction) would fail in one of two ways.  In the case
	 * where you don't set optreset, it would fail because optind may be
	 * pointing to the argument after the one it should be pointing at.
	 * In the case where you do set optreset, and reset optind, it would
	 * fail because getopt would run into the first set of options, which
	 * it doesn't understand.
	 *
	 * All of this would "sort of" work if you could somehow figure out
	 * whether optind had been incremented one option too far.  The
	 * mechanics of that, however, are more daunting than just giving
	 * both invocations all of the expect options for either invocation.
	 *
	 * Needless to say, I wouldn't mind if someone invented a better
	 * (non-GPL!) command line parsing interface than getopt.  I
	 * wouldn't mind if someone added more knobs to getopt to make it
	 * work better.  Who knows, I may talk myself into doing it someday,
	 * if the standards weenies let me.  As it is, it just leads to
	 * hackery like this and causes people to avoid it in some cases.
	 *
	 * KDM, September 8th, 1998
	 */
	if (subopt != NULL)
		sprintf(combinedopt, "%s%s", mainopt, subopt);
	else
		sprintf(combinedopt, "%s", mainopt);

	/*
	 * Start getopt processing at argv[2/3], since we've already
	 * accepted argv[1..2] as the command name, and as a possible
	 * device name.
	 */
	optind = optstart;

	/*
	 * Now we run through the argument list looking for generic
	 * options, and ignoring options that possibly belong to
	 * subfunctions.
	 */
	while ((c = getopt(argc, argv, combinedopt))!= -1){
		switch (c) {
		case 'C':
			cmdargs |= CTLADM_ARG_RETRIES;
			retries = strtol(optarg, NULL, 0);
			break;
		case 'D':
			device = strdup(optarg);
			cmdargs |= CTLADM_ARG_DEVICE;
			break;
		case 'I':
			cmdargs |= CTLADM_ARG_INITIATOR;
			initid = strtol(optarg, NULL, 0);
			break;
		default:
			break;
		}
	}

	if ((cmdargs & CTLADM_ARG_INITIATOR) == 0)
		initid = 7;

	optind = optstart;
	optreset = 1;

	/*
	 * Default to opening the CTL device for now.
	 */
	if (((cmdargs & CTLADM_ARG_DEVICE) == 0)
	 && (command != CTLADM_CMD_HELP)) {
		device = strdup(CTL_DEFAULT_DEV);
		cmdargs |= CTLADM_ARG_DEVICE;
	}

	if ((cmdargs & CTLADM_ARG_DEVICE)
	 && (command != CTLADM_CMD_HELP)) {
		fd = open(device, O_RDWR);
		if (fd == -1 && errno == ENOENT) {
			saved_errno = errno;
			retval = kldload("ctl");
			if (retval != -1)
				fd = open(device, O_RDWR);
			else
				errno = saved_errno;
		}
		if (fd == -1) {
			fprintf(stderr, "%s: error opening %s: %s\n",
				argv[0], device, strerror(errno));
			retval = 1;
			goto bailout;
		}
#ifdef	WANT_ISCSI
		else {
			if (modfind("cfiscsi") == -1 &&
			    kldload("cfiscsi") == -1)
				warn("couldn't load cfiscsi");
		}
#endif
	} else if ((command != CTLADM_CMD_HELP)
		&& ((cmdargs & CTLADM_ARG_DEVICE) == 0)) {
		fprintf(stderr, "%s: you must specify a device with the "
			"--device argument for this command\n", argv[0]);
		command = CTLADM_CMD_HELP;
		retval = 1;
	}

	switch (command) {
	case CTLADM_CMD_TUR:
		retval = cctl_tur(fd, lun, initid, retries);
		break;
	case CTLADM_CMD_INQUIRY:
		retval = cctl_inquiry(fd, lun, initid, retries);
		break;
	case CTLADM_CMD_REQ_SENSE:
		retval = cctl_req_sense(fd, lun, initid, retries);
		break;
	case CTLADM_CMD_REPORT_LUNS:
		retval = cctl_report_luns(fd, lun, initid, retries);
		break;
	case CTLADM_CMD_CREATE:
		retval = cctl_create_lun(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_RM:
		retval = cctl_rm_lun(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_DEVLIST:
		retval = cctl_devlist(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_READ:
	case CTLADM_CMD_WRITE:
		retval = cctl_read_write(fd, lun, initid, retries,
					 argc, argv, combinedopt, command);
		break;
	case CTLADM_CMD_PORT:
		retval = cctl_port(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_PORTLIST:
		retval = cctl_portlist(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_LUNMAP:
		retval = cctl_lunmap(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_READCAPACITY:
		retval = cctl_read_capacity(fd, lun, initid, retries,
					    argc, argv, combinedopt);
		break;
	case CTLADM_CMD_MODESENSE:
		retval = cctl_mode_sense(fd, lun, initid, retries,
					 argc, argv, combinedopt);
		break;
	case CTLADM_CMD_START:
	case CTLADM_CMD_STOP:
		retval = cctl_start_stop(fd, lun, initid, retries,
					 (command == CTLADM_CMD_START) ? 1 : 0,
					 argc, argv, combinedopt);
		break;
	case CTLADM_CMD_SYNC_CACHE:
		retval = cctl_sync_cache(fd, lun, initid, retries,
					 argc, argv, combinedopt);
		break;
	case CTLADM_CMD_LUNLIST:
		retval = cctl_lunlist(fd);
		break;
	case CTLADM_CMD_DELAY:
		retval = cctl_delay(fd, lun, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_ERR_INJECT:
		retval = cctl_error_inject(fd, lun, argc, argv,
					   combinedopt);
		break;
	case CTLADM_CMD_DUMPOOA:
		retval = cctl_dump_ooa(fd, argc, argv);
		break;
	case CTLADM_CMD_DUMPSTRUCTS:
		retval = cctl_dump_structs(fd, cmdargs);
		break;
	case CTLADM_CMD_PRES_IN:
		retval = cctl_persistent_reserve_in(fd, lun, initid,
		                                    argc, argv, combinedopt,
						    retries);
		break;
	case CTLADM_CMD_PRES_OUT:
		retval = cctl_persistent_reserve_out(fd, lun, initid,
						     argc, argv, combinedopt,
						     retries);
		break;
	case CTLADM_CMD_INQ_VPD_DEVID:
	        retval = cctl_inquiry_vpd_devid(fd, lun, initid);
		break;
	case CTLADM_CMD_RTPG:
	        retval = cctl_report_target_port_group(fd, lun, initid);
		break;
	case CTLADM_CMD_MODIFY:
	        retval = cctl_modify_lun(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_ISLIST:
	        retval = cctl_islist(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_ISLOGOUT:
	        retval = cctl_islogout(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_ISTERMINATE:
	        retval = cctl_isterminate(fd, argc, argv, combinedopt);
		break;
	case CTLADM_CMD_HELP:
	default:
		usage(retval);
		break;
	}
bailout:

	if (fd != -1)
		close(fd);

	exit (retval);
}