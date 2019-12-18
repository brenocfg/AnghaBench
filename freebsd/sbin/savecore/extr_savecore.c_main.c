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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CREATE ; 
 int /*<<< orphan*/  CAP_FCNTL ; 
 int /*<<< orphan*/  CAP_FSTATAT ; 
 int /*<<< orphan*/  CAP_FSTATFS ; 
 int /*<<< orphan*/  CAP_FTRUNCATE ; 
 int /*<<< orphan*/  CAP_PREAD ; 
 int /*<<< orphan*/  CAP_SYMLINKAT ; 
 int /*<<< orphan*/  CAP_UNLINKAT ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 int /*<<< orphan*/  DoFile (char const*,int,char*) ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_PERROR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SIGINFO ; 
 scalar_t__ atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int chdir (char*) ; 
 int checkfor ; 
 int clear ; 
 int compress ; 
 char** enum_dumpdevs (int*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int force ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  infohandler ; 
 int /*<<< orphan*/  init_caps (int,char**) ; 
 int keep ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ maxdumps ; 
 scalar_t__ nerr ; 
 scalar_t__ nfound ; 
 scalar_t__ nsaved ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int xo_parse_args (int,char**) ; 

int
main(int argc, char **argv)
{
	cap_rights_t rights;
	const char *savedir;
	int i, ch, error, savedirfd;

	checkfor = compress = clear = force = keep = verbose = 0;
	nfound = nsaved = nerr = 0;
	savedir = ".";

	openlog("savecore", LOG_PERROR, LOG_DAEMON);
	signal(SIGINFO, infohandler);

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

	while ((ch = getopt(argc, argv, "Ccfkm:vz")) != -1)
		switch(ch) {
		case 'C':
			checkfor = 1;
			break;
		case 'c':
			clear = 1;
			break;
		case 'f':
			force = 1;
			break;
		case 'k':
			keep = 1;
			break;
		case 'm':
			maxdumps = atoi(optarg);
			if (maxdumps <= 0) {
				logmsg(LOG_ERR, "Invalid maxdump value");
				exit(1);
			}
			break;
		case 'v':
			verbose++;
			break;
		case 'z':
			compress = 1;
			break;
		case '?':
		default:
			usage();
		}
	if (checkfor && (clear || force || keep))
		usage();
	if (clear && (compress || keep))
		usage();
	if (maxdumps > 0 && (checkfor || clear))
		usage();
	argc -= optind;
	argv += optind;
	if (argc >= 1 && !checkfor && !clear) {
		error = chdir(argv[0]);
		if (error) {
			logmsg(LOG_ERR, "chdir(%s): %m", argv[0]);
			exit(1);
		}
		savedir = argv[0];
		argc--;
		argv++;
	}
	if (argc == 0)
		argv = enum_dumpdevs(&argc);

	savedirfd = open(savedir, O_RDONLY | O_DIRECTORY);
	if (savedirfd < 0) {
		logmsg(LOG_ERR, "open(%s): %m", savedir);
		exit(1);
	}
	(void)cap_rights_init(&rights, CAP_CREATE, CAP_FCNTL, CAP_FSTATAT,
	    CAP_FSTATFS, CAP_PREAD, CAP_SYMLINKAT, CAP_FTRUNCATE, CAP_UNLINKAT,
	    CAP_WRITE);
	if (caph_rights_limit(savedirfd, &rights) < 0) {
		logmsg(LOG_ERR, "cap_rights_limit(): %m");
		exit(1);
	}

	/* Enter capability mode. */
	init_caps(argc, argv);

	for (i = 0; i < argc; i++)
		DoFile(savedir, savedirfd, argv[i]);

	/* Emit minimal output. */
	if (nfound == 0) {
		if (checkfor) {
			if (verbose)
				printf("No dump exists\n");
			exit(1);
		}
		if (verbose)
			logmsg(LOG_WARNING, "no dumps found");
	} else if (nsaved == 0) {
		if (nerr != 0) {
			if (verbose)
				logmsg(LOG_WARNING,
				    "unsaved dumps found but not saved");
			exit(1);
		} else if (verbose)
			logmsg(LOG_WARNING, "no unsaved dumps found");
	}

	return (0);
}