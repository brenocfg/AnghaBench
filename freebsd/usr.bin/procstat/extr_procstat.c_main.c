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
struct procstat_cmd {scalar_t__ cmd; char* xocontainer; int /*<<< orphan*/  (* opt ) (int,char**) ;} ;
struct procstat {int dummy; } ;
struct kinfo_proc {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  KERN_PROC_PID ; 
 int /*<<< orphan*/  KERN_PROC_PROC ; 
 int /*<<< orphan*/  PROCSTAT_XO_VERSION ; 
 int PS_OPT_CAPABILITIES ; 
 int PS_OPT_NOHEADER ; 
 int PS_OPT_PERTHREAD ; 
 int PS_OPT_SIGNUM ; 
 int PS_OPT_VERBOSE ; 
 int PS_SUBCOMMAND_OPTS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct procstat_cmd* getcmd (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  kinfo_proc_sort (struct kinfo_proc*,int) ; 
 char* optarg ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  procstat (struct procstat_cmd const*,struct procstat*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_close (struct procstat*) ; 
 scalar_t__ procstat_files ; 
 int /*<<< orphan*/  procstat_freeprocs (struct procstat*,struct kinfo_proc*) ; 
 struct kinfo_proc* procstat_getprocs (struct procstat*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ procstat_kstack ; 
 struct procstat* procstat_open_core (char*) ; 
 struct procstat* procstat_open_kvm (char*,char*) ; 
 struct procstat* procstat_open_sysctl () ; 
 int procstat_opts ; 
 int /*<<< orphan*/  sleep (int) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  stub1 (int,char**) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_flush () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_version (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int ch, interval;
	int i;
	struct kinfo_proc *p;
	const struct procstat_cmd *cmd;
	struct procstat *prstat, *cprstat;
	long l;
	pid_t pid;
	char *dummy;
	char *nlistf, *memf;
	int aflag;
	int cnt;

	interval = 0;
	cmd = NULL;
	memf = nlistf = NULL;
	aflag = 0;
	argc = xo_parse_args(argc, argv);

	while ((ch = getopt(argc, argv, "abCcefHhijkLlM:N:nrSstvw:x")) != -1) {
		switch (ch) {
		case 'a':
			aflag++;
			break;
		case 'b':
			if (cmd != NULL)
				usage();
			cmd = getcmd("binary");
			break;
		case 'C':
			procstat_opts |= PS_OPT_CAPABILITIES;
			break;
		case 'c':
			if (cmd != NULL)
				usage();
			cmd = getcmd("arguments");
			break;
		case 'e':
			if (cmd != NULL)
				usage();
			cmd = getcmd("environment");
			break;
		case 'f':
			if (cmd != NULL)
				usage();
			cmd = getcmd("files");
			break;
		case 'H':
			procstat_opts |= PS_OPT_PERTHREAD;
			break;
		case 'h':
			procstat_opts |= PS_OPT_NOHEADER;
			break;
		case 'i':
			if (cmd != NULL)
				usage();
			cmd = getcmd("signals");
			break;
		case 'j':
			if (cmd != NULL)
				usage();
			cmd = getcmd("tsignals");
			break;
		case 'k':
			if (cmd != NULL && cmd->cmd == procstat_kstack) {
				if ((procstat_opts & PS_OPT_VERBOSE) != 0)
					usage();
				procstat_opts |= PS_OPT_VERBOSE;
			} else {
				if (cmd != NULL)
					usage();
				cmd = getcmd("kstack");
			}
			break;
		case 'L':
			if (cmd != NULL)
				usage();
			cmd = getcmd("ptlwpinfo");
			break;
		case 'l':
			if (cmd != NULL)
				usage();
			cmd = getcmd("rlimit");
			break;
		case 'M':
			memf = optarg;
			break;
		case 'N':
			nlistf = optarg;
			break;
		case 'n':
			procstat_opts |= PS_OPT_SIGNUM;
			break;
		case 'r':
			if (cmd != NULL)
				usage();
			cmd = getcmd("rusage");
			break;
		case 'S':
			if (cmd != NULL)
				usage();
			cmd = getcmd("cpuset");
			break;
		case 's':
			if (cmd != NULL)
				usage();
			cmd = getcmd("credentials");
			break;
		case 't':
			if (cmd != NULL)
				usage();
			cmd = getcmd("threads");
			break;
		case 'v':
			if (cmd != NULL)
				usage();
			cmd = getcmd("vm");
			break;
		case 'w':
			l = strtol(optarg, &dummy, 10);
			if (*dummy != '\0')
				usage();
			if (l < 1 || l > INT_MAX)
				usage();
			interval = l;
			break;
		case 'x':
			if (cmd != NULL)
				usage();
			cmd = getcmd("auxv");
			break;
		case '?':
		default:
			usage();
		}

	}
	argc -= optind;
	argv += optind;

	if (cmd == NULL && argv[0] != NULL && (cmd = getcmd(argv[0])) != NULL) {
		if ((procstat_opts & PS_SUBCOMMAND_OPTS) != 0)
			usage();
		if (cmd->opt != NULL) {
			optreset = 1;
			optind = 1;
			cmd->opt(argc, argv);
			argc -= optind;
			argv += optind;
		} else {
			argc -= 1;
			argv += 1;
		}
	} else {
		if (cmd == NULL)
			cmd = getcmd("basic");
		if (cmd->cmd != procstat_files &&
		    (procstat_opts & PS_OPT_CAPABILITIES) != 0)
			usage();
	}

	/* Must specify either the -a flag or a list of pids. */
	if (!(aflag == 1 && argc == 0) && !(aflag == 0 && argc > 0))
		usage();

	if (memf != NULL)
		prstat = procstat_open_kvm(nlistf, memf);
	else
		prstat = procstat_open_sysctl();
	if (prstat == NULL)
		xo_errx(1, "procstat_open()");
	do {
		xo_set_version(PROCSTAT_XO_VERSION);
		xo_open_container("procstat");
		xo_open_container(cmd->xocontainer);

		if (aflag) {
			p = procstat_getprocs(prstat, KERN_PROC_PROC, 0, &cnt);
			if (p == NULL)
				xo_errx(1, "procstat_getprocs()");
			kinfo_proc_sort(p, cnt);
			for (i = 0; i < cnt; i++) {
				procstat(cmd, prstat, &p[i]);

				/* Suppress header after first process. */
				procstat_opts |= PS_OPT_NOHEADER;
				xo_flush();
			}
			procstat_freeprocs(prstat, p);
		}
		for (i = 0; i < argc; i++) {
			l = strtol(argv[i], &dummy, 10);
			if (*dummy == '\0') {
				if (l < 0)
					usage();
				pid = l;

				p = procstat_getprocs(prstat, KERN_PROC_PID,
				    pid, &cnt);
				if (p == NULL)
					xo_errx(1, "procstat_getprocs()");
				if (cnt != 0)
					procstat(cmd, prstat, p);
				procstat_freeprocs(prstat, p);
			} else {
				cprstat = procstat_open_core(argv[i]);
				if (cprstat == NULL) {
					warnx("procstat_open()");
					continue;
				}
				p = procstat_getprocs(cprstat, KERN_PROC_PID,
				    -1, &cnt);
				if (p == NULL)
					xo_errx(1, "procstat_getprocs()");
				if (cnt != 0)
					procstat(cmd, cprstat, p);
				procstat_freeprocs(cprstat, p);
				procstat_close(cprstat);
			}
			/* Suppress header after first process. */
			procstat_opts |= PS_OPT_NOHEADER;
		}

		xo_close_container(cmd->xocontainer);
		xo_close_container("procstat");
		xo_finish();
		if (interval)
			sleep(interval);
	} while (interval);

	procstat_close(prstat);

	exit(0);
}