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

/* Variables and functions */
 char* Cdir ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int EX_OK ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  LOG_AUTH ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  O_WRONLY ; 
 unsigned long VERIEXEC_ACTIVE ; 
 unsigned long VERIEXEC_DEBUG_OFF ; 
 unsigned long VERIEXEC_DEBUG_ON ; 
 unsigned long VERIEXEC_ENFORCE ; 
 unsigned long VERIEXEC_GETSTATE ; 
 unsigned long VERIEXEC_GETVERSION ; 
 unsigned long VERIEXEC_LOCK ; 
 unsigned long VERIEXEC_STATE_ACTIVE ; 
 unsigned long VERIEXEC_STATE_ENFORCE ; 
 unsigned long VERIEXEC_STATE_LOADED ; 
 unsigned long VERIEXEC_STATE_LOCKED ; 
 int /*<<< orphan*/  Verbose ; 
 int VeriexecVersion ; 
 int /*<<< orphan*/  _PATH_DEV_VERIEXEC ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  dev_fd ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getprogname () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,unsigned long,int*) ; 
 int /*<<< orphan*/  open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 int ve_trust_init () ; 
 int /*<<< orphan*/  veriexec_check_path (char*) ; 
 scalar_t__ veriexec_load (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	unsigned long ctl;
	int c;
	int x;

	dev_fd = open(_PATH_DEV_VERIEXEC, O_WRONLY, 0);

	while ((c = getopt(argc, argv, "C:i:x:vz:")) != -1) {
		switch (c) {
		case 'C':
			Cdir = optarg;
			break;
		case 'i':
			if (dev_fd < 0) {
				err(EX_UNAVAILABLE, "cannot open veriexec");
			}
			if (ioctl(dev_fd, VERIEXEC_GETSTATE, &x)) {
				err(EX_UNAVAILABLE,
				    "Cannot get veriexec state");
			}
			switch (optarg[0]) {
			case 'a':	/* active */
				ctl = VERIEXEC_STATE_ACTIVE;
				break;
			case 'e':	/* enforce */
				ctl = VERIEXEC_STATE_ENFORCE;
				break;
			case 'l':	/* loaded/locked */
				ctl = (strncmp(optarg, "lock", 4)) ?
				    VERIEXEC_STATE_LOCKED :
				    VERIEXEC_STATE_LOADED;
				break;
			default:
				errx(EX_USAGE, "unknown state %s", optarg);
				break;
			}
			exit((x & ctl) == 0);
			break;
		case 'v':
			Verbose++;
			break;
		case 'x':
			/*
			 * -x says all other args are paths to check.
			 */
			for (x = 0; optind < argc; optind++) {
				if (veriexec_check_path(argv[optind])) {
					warn("%s", argv[optind]);
					x = 2;
				}
			}
			exit(x);
			break;
		case 'z':
			switch (optarg[0]) {
			case 'a':	/* active */
				ctl = VERIEXEC_ACTIVE;
				break;
			case 'd':	/* debug* */
				ctl = (strstr(optarg, "off")) ?
				    VERIEXEC_DEBUG_OFF : VERIEXEC_DEBUG_ON;
				if (optind < argc && ctl == VERIEXEC_DEBUG_ON) {
					x = atoi(argv[optind]);
					if (x == 0)
						ctl = VERIEXEC_DEBUG_OFF;
				}
				break;
			case 'e':	/* enforce */
				ctl = VERIEXEC_ENFORCE;
				break;
			case 'g':
				ctl = VERIEXEC_GETSTATE; /* get state */
				break;
			case 'l':	/* lock */
				ctl = VERIEXEC_LOCK;
				break;
			default:
				errx(EX_USAGE, "unknown command %s", optarg);
				break;
			}
			if (dev_fd < 0) {
				err(EX_UNAVAILABLE, "cannot open veriexec");
			}
			if (ioctl(dev_fd, ctl, &x)) {
				err(EX_UNAVAILABLE, "cannot %s veriexec", optarg);
			}
			if (ctl == VERIEXEC_DEBUG_ON ||
			    ctl == VERIEXEC_DEBUG_OFF) {
				printf("debug is: %d\n", x);
			} else if (ctl == VERIEXEC_GETSTATE) {
				printf("%#o\n", x);
			}
			exit(EX_OK);
			break;
		}
	}
	openlog(getprogname(), LOG_PID, LOG_AUTH);
	if (ve_trust_init() < 1)
		errx(EX_OSFILE, "cannot initialize trust store");
#ifdef VERIEXEC_GETVERSION
	if (ioctl(dev_fd, VERIEXEC_GETVERSION, &VeriexecVersion)) {
		VeriexecVersion = 0;	/* unknown */
	}
#endif

	for (; optind < argc; optind++) {
		if (veriexec_load(argv[optind])) {
			err(EX_DATAERR, "cannot load %s", argv[optind]);
		}
	}
	exit(EX_OK);
}