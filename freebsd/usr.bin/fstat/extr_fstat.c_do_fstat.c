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
struct procstat {int dummy; } ;
struct passwd {int pw_uid; } ;
struct kinfo_proc {scalar_t__ ki_stat; } ;

/* Variables and functions */
 int KERN_PROC_PID ; 
 int KERN_PROC_PROC ; 
 int KERN_PROC_UID ; 
 scalar_t__ SZOMB ; 
 int atoi (int /*<<< orphan*/ *) ; 
 int checkfile ; 
 int /*<<< orphan*/  dofiles (struct procstat*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fsflg ; 
 scalar_t__ getfname (char*) ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memf ; 
 int mflg ; 
 int nflg ; 
 int /*<<< orphan*/ * nlistf ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  optind ; 
 int /*<<< orphan*/  pflg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  procstat_close (struct procstat*) ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int,int,int*) ; 
 struct procstat* procstat_open_kvm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct procstat* procstat_open_sysctl () ; 
 int /*<<< orphan*/  putchar (char) ; 
 int sflg ; 
 int /*<<< orphan*/  uflg ; 
 int /*<<< orphan*/  usage () ; 
 int vflg ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
do_fstat(int argc, char **argv)
{
	struct kinfo_proc *p;
	struct passwd *passwd;
	struct procstat *procstat;
	int arg, ch, what;
	int cnt, i;

	arg = 0;
	what = KERN_PROC_PROC;
	nlistf = memf = NULL;
	while ((ch = getopt(argc, argv, "fmnp:su:vN:M:")) != -1)
		switch((char)ch) {
		case 'f':
			fsflg = 1;
			break;
		case 'M':
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
		case 'm':
			mflg = 1;
			break;
		case 'n':
			nflg = 1;
			break;
		case 'p':
			if (pflg++)
				usage();
			if (!isdigit(*optarg)) {
				warnx("-p requires a process id");
				usage();
			}
			what = KERN_PROC_PID;
			arg = atoi(optarg);
			break;
		case 's':
			sflg = 1;
			break;
		case 'u':
			if (uflg++)
				usage();
			if (!(passwd = getpwnam(optarg)))
				errx(1, "%s: unknown uid", optarg);
			what = KERN_PROC_UID;
			arg = passwd->pw_uid;
			break;
		case 'v':
			vflg = 1;
			break;
		case '?':
		default:
			usage();
		}

	if (*(argv += optind)) {
		for (; *argv; ++argv) {
			if (getfname(*argv))
				checkfile = 1;
		}
		if (!checkfile)	/* file(s) specified, but none accessible */
			exit(1);
	}

	if (fsflg && !checkfile) {
		/* -f with no files means use wd */
		if (getfname(".") == 0)
			exit(1);
		checkfile = 1;
	}

	if (memf != NULL)
		procstat = procstat_open_kvm(nlistf, memf);
	else
		procstat = procstat_open_sysctl();
	if (procstat == NULL)
		errx(1, "procstat_open()");
	p = procstat_getprocs(procstat, what, arg, &cnt);
	if (p == NULL)
		errx(1, "procstat_getprocs()");

	/*
	 * Print header.
	 */
	if (nflg)
		printf("%s",
"USER     CMD          PID   FD  DEV    INUM       MODE SZ|DV R/W");
	else
		printf("%s",
"USER     CMD          PID   FD MOUNT      INUM MODE         SZ|DV R/W");
	if (checkfile && fsflg == 0)
		printf(" NAME\n");
	else
		putchar('\n');

	/*
	 * Go through the process list.
	 */
	for (i = 0; i < cnt; i++) {
		if (p[i].ki_stat == SZOMB)
			continue;
		dofiles(procstat, &p[i]);
	}
	procstat_freeprocs(procstat, p);
	procstat_close(procstat);
	return (0);
}