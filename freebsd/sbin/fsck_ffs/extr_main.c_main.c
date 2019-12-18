#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;
struct TYPE_4__ {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_3__ {int tv_sec; scalar_t__ tv_usec; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIT ; 
 int ERESTART ; 
 int /*<<< orphan*/  Eflag ; 
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGINFO ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  Zflag ; 
 scalar_t__ alarmhandler ; 
 int argtoimax (char,char*,int /*<<< orphan*/ ,int) ; 
 int bflag ; 
 int bkgrdcheck ; 
 int bkgrdflag ; 
 scalar_t__ catch ; 
 scalar_t__ catchquit ; 
 int checkfilesys (char*) ; 
 scalar_t__ ckclean ; 
 int cvtlevel ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ infohandler ; 
 scalar_t__ inoopt ; 
 int lfmode ; 
 int /*<<< orphan*/  nflag ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  preen ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ returntosingle ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int skipclean ; 
 int surrender ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  usage () ; 
 int wantrestart ; 
 int /*<<< orphan*/  yflag ; 
 int /*<<< orphan*/  zflag ; 

int
main(int argc, char *argv[])
{
	int ch;
	struct rlimit rlimit;
	struct itimerval itimerval;
	int fsret;
	int ret = 0;

	sync();
	skipclean = 1;
	inoopt = 0;
	while ((ch = getopt(argc, argv, "b:Bc:CdEfFm:npRrSyZz")) != -1) {
		switch (ch) {
		case 'b':
			skipclean = 0;
			bflag = argtoimax('b', "number", optarg, 10);
			printf("Alternate super block location: %jd\n", bflag);
			break;

		case 'B':
			bkgrdflag = 1;
			break;

		case 'c':
			skipclean = 0;
			cvtlevel = argtoimax('c', "conversion level", optarg,
			    10);
			if (cvtlevel < 3)
				errx(EEXIT, "cannot do level %d conversion",
				    cvtlevel);
			break;

		case 'd':
			debug++;
			break;

		case 'E':
			Eflag++;
			break;

		case 'f':
			skipclean = 0;
			break;

		case 'F':
			bkgrdcheck = 1;
			break;

		case 'm':
			lfmode = argtoimax('m', "mode", optarg, 8);
			if (lfmode &~ 07777)
				errx(EEXIT, "bad mode to -m: %o", lfmode);
			printf("** lost+found creation mode %o\n", lfmode);
			break;

		case 'n':
			nflag++;
			yflag = 0;
			break;

		case 'p':
			preen++;
			/*FALLTHROUGH*/

		case 'C':
			ckclean++;
			break;

		case 'R':
			wantrestart = 1;
			break;
		case 'r':
			inoopt++;
			break;

		case 'S':
			surrender = 1;
			break;

		case 'y':
			yflag++;
			nflag = 0;
			break;

		case 'Z':
			Zflag++;
			break;

		case 'z':
			zflag++;
			break;

		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (!argc)
		usage();

	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		(void)signal(SIGINT, catch);
	if (ckclean)
		(void)signal(SIGQUIT, catchquit);
	signal(SIGINFO, infohandler);
	if (bkgrdflag) {
		signal(SIGALRM, alarmhandler);
		itimerval.it_interval.tv_sec = 5;
		itimerval.it_interval.tv_usec = 0;
		itimerval.it_value.tv_sec = 5;
		itimerval.it_value.tv_usec = 0;
		setitimer(ITIMER_REAL, &itimerval, NULL);
	}
	/*
	 * Push up our allowed memory limit so we can cope
	 * with huge file systems.
	 */
	if (getrlimit(RLIMIT_DATA, &rlimit) == 0) {
		rlimit.rlim_cur = rlimit.rlim_max;
		(void)setrlimit(RLIMIT_DATA, &rlimit);
	}
	while (argc > 0) {
		if ((fsret = checkfilesys(*argv)) == ERESTART)
			continue;
		ret |= fsret;
		argc--;
		argv++;
	}

	if (returntosingle)
		ret = 2;
	exit(ret);
}