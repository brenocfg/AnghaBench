#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct protox {scalar_t__ pr_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_LINK ; 
 scalar_t__ AF_NETGRAPH ; 
 scalar_t__ AF_UNIX ; 
 scalar_t__ AF_UNSPEC ; 
 int Aflag ; 
 int Bflag ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int Lflag ; 
 size_t N_SFSTAT ; 
 size_t N_UNP_COUNT ; 
 size_t N_UNP_DHEAD ; 
 size_t N_UNP_GENCNT ; 
 size_t N_UNP_SHEAD ; 
 size_t N_UNP_SPHEAD ; 
 scalar_t__ PF_KEY ; 
 int Pflag ; 
 int Qflag ; 
 int Rflag ; 
 int Tflag ; 
 int Wflag ; 
 scalar_t__ af ; 
 int aflag ; 
 void* atoi (char*) ; 
 int bflag ; 
 int /*<<< orphan*/  bpf_stats (char*) ; 
 int dflag ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getgid () ; 
 int getopt (int,char**,char*) ; 
 int gflag ; 
 int hflag ; 
 int iflag ; 
 char* interface ; 
 scalar_t__ interval ; 
 int /*<<< orphan*/  intpr (int /*<<< orphan*/ *,scalar_t__) ; 
 struct protox* ip6protox ; 
 int /*<<< orphan*/  isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ kread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kresolve_list (TYPE_1__*) ; 
 int /*<<< orphan*/ * kvmd ; 
 int live ; 
 int /*<<< orphan*/  mbpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* memf ; 
 int mflag ; 
 int /*<<< orphan*/  mroute6pr () ; 
 int /*<<< orphan*/  mroutepr () ; 
 int /*<<< orphan*/  mrt6_stats () ; 
 int /*<<< orphan*/  mrt_stats () ; 
 struct protox* name2protox (char*) ; 
 struct protox* netgraphprotox ; 
 int /*<<< orphan*/  netisr_stats () ; 
 TYPE_1__* nl ; 
 char* nlistf ; 
 void* noutputs ; 
 int numeric_addr ; 
 int numeric_port ; 
 char* optarg ; 
 scalar_t__ optind ; 
 struct protox* pfkeyprotox ; 
 int pflag ; 
 int /*<<< orphan*/  printproto (struct protox*,scalar_t__,int*) ; 
 struct protox* protox ; 
 int rflag ; 
 int /*<<< orphan*/  routepr (int,scalar_t__) ; 
 int /*<<< orphan*/  rt_stats () ; 
 scalar_t__ setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethostent (int) ; 
 int /*<<< orphan*/  setnetent (int) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 void* unit ; 
 int /*<<< orphan*/  unixpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usage () ; 
 int xflag ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_errx (int,char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int xo_parse_args (int,char**) ; 
 int zflag ; 

int
main(int argc, char *argv[])
{
	struct protox *tp = NULL;  /* for printing cblocks & stats */
	int ch;
	int fib = -1;
	char *endptr;
	bool first = true;

	af = AF_UNSPEC;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(EXIT_FAILURE);

	while ((ch = getopt(argc, argv, "46AaBbdF:f:ghI:iLlM:mN:nPp:Qq:RrSTsuWw:xz"))
	    != -1)
		switch(ch) {
		case '4':
#ifdef INET
			af = AF_INET;
#else
			errx(1, "IPv4 support is not compiled in");
#endif
			break;
		case '6':
#ifdef INET6
			af = AF_INET6;
#else
			errx(1, "IPv6 support is not compiled in");
#endif
			break;
		case 'A':
			Aflag = 1;
			break;
		case 'a':
			aflag = 1;
			break;
		case 'B':
			Bflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'F':
			fib = strtol(optarg, &endptr, 0);
			if (*endptr != '\0' ||
			    (fib == 0 && (errno == EINVAL || errno == ERANGE)))
				xo_errx(1, "%s: invalid fib", optarg);
			break;
		case 'f':
			if (strcmp(optarg, "inet") == 0)
				af = AF_INET;
#ifdef INET6
			else if (strcmp(optarg, "inet6") == 0)
				af = AF_INET6;
#endif
#ifdef IPSEC
			else if (strcmp(optarg, "pfkey") == 0)
				af = PF_KEY;
#endif
			else if (strcmp(optarg, "unix") == 0 ||
				 strcmp(optarg, "local") == 0)
				af = AF_UNIX;
#ifdef NETGRAPH
			else if (strcmp(optarg, "ng") == 0
			    || strcmp(optarg, "netgraph") == 0)
				af = AF_NETGRAPH;
#endif
			else if (strcmp(optarg, "link") == 0)
				af = AF_LINK;
			else {
				xo_errx(1, "%s: unknown address family",
				    optarg);
			}
			break;
		case 'g':
			gflag = 1;
			break;
		case 'h':
			hflag = 1;
			break;
		case 'I': {
			char *cp;

			iflag = 1;
			for (cp = interface = optarg; isalpha(*cp); cp++)
				continue;
			unit = atoi(cp);
			break;
		}
		case 'i':
			iflag = 1;
			break;
		case 'L':
			Lflag = 1;
			break;
		case 'M':
			memf = optarg;
			break;
		case 'm':
			mflag = 1;
			break;
		case 'N':
			nlistf = optarg;
			break;
		case 'n':
			numeric_addr = numeric_port = 1;
			break;
		case 'P':
			Pflag = 1;
			break;
		case 'p':
			if ((tp = name2protox(optarg)) == NULL) {
				xo_errx(1, "%s: unknown or uninstrumented "
				    "protocol", optarg);
			}
			pflag = 1;
			break;
		case 'Q':
			Qflag = 1;
			break;
		case 'q':
			noutputs = atoi(optarg);
			if (noutputs != 0)
				noutputs++;
			break;
		case 'r':
			rflag = 1;
			break;
		case 'R':
			Rflag = 1;
			break;
		case 's':
			++sflag;
			break;
		case 'S':
			numeric_addr = 1;
			break;
		case 'u':
			af = AF_UNIX;
			break;
		case 'W':
		case 'l':
			Wflag = 1;
			break;
		case 'w':
			interval = atoi(optarg);
			iflag = 1;
			break;
		case 'T':
			Tflag = 1;
			break;
		case 'x':
			xflag = 1;
			break;
		case 'z':
			zflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;

#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		if (isdigit(**argv)) {
			interval = atoi(*argv);
			if (interval <= 0)
				usage();
			++argv;
			iflag = 1;
		}
		if (*argv) {
			nlistf = *argv;
			if (*++argv)
				memf = *argv;
		}
	}
#endif

	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	live = (nlistf == NULL && memf == NULL);
	if (!live) {
		if (setgid(getgid()) != 0)
			xo_err(-1, "setgid");
		/* Load all necessary kvm symbols */
		kresolve_list(nl);
	}

	if (xflag && Tflag)
		xo_errx(1, "-x and -T are incompatible, pick one.");

	if (Bflag) {
		if (!live)
			usage();
		bpf_stats(interface);
		xo_finish();
		exit(0);
	}
	if (mflag) {
		if (!live) {
			if (kread(0, NULL, 0) == 0)
				mbpr(kvmd, nl[N_SFSTAT].n_value);
		} else
			mbpr(NULL, 0);
		xo_finish();
		exit(0);
	}
	if (Qflag) {
		if (!live) {
			if (kread(0, NULL, 0) == 0)
				netisr_stats();
		} else
			netisr_stats();
		xo_finish();
		exit(0);
	}
#if 0
	/*
	 * Keep file descriptors open to avoid overhead
	 * of open/close on each call to get* routines.
	 */
	sethostent(1);
	setnetent(1);
#else
	/*
	 * This does not make sense any more with DNS being default over
	 * the files.  Doing a setXXXXent(1) causes a tcp connection to be
	 * used for the queries, which is slower.
	 */
#endif
	if (iflag && !sflag) {
		xo_open_container("statistics");
		intpr(NULL, af);
		xo_close_container("statistics");
		xo_finish();
		exit(0);
	}
	if (rflag) {
		xo_open_container("statistics");
		if (sflag) {
			rt_stats();
		} else
			routepr(fib, af);
		xo_close_container("statistics");
		xo_finish();
		exit(0);
	}

	if (gflag) {
		xo_open_container("statistics");
		if (sflag) {
			if (af == AF_INET || af == AF_UNSPEC)
				mrt_stats();
#ifdef INET6
			if (af == AF_INET6 || af == AF_UNSPEC)
				mrt6_stats();
#endif
		} else {
			if (af == AF_INET || af == AF_UNSPEC)
				mroutepr();
#ifdef INET6
			if (af == AF_INET6 || af == AF_UNSPEC)
				mroute6pr();
#endif
		}
		xo_close_container("statistics");
		xo_finish();
		exit(0);
	}

	if (tp) {
		xo_open_container("statistics");
		printproto(tp, tp->pr_name, &first);
		if (!first)
			xo_close_list("socket");
		xo_close_container("statistics");
		xo_finish();
		exit(0);
	}

	xo_open_container("statistics");
	if (af == AF_INET || af == AF_UNSPEC)
		for (tp = protox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name, &first);
#ifdef INET6
	if (af == AF_INET6 || af == AF_UNSPEC)
		for (tp = ip6protox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name, &first);
#endif /*INET6*/
#ifdef IPSEC
	if (af == PF_KEY || af == AF_UNSPEC)
		for (tp = pfkeyprotox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name, &first);
#endif /*IPSEC*/
#ifdef NETGRAPH
	if (af == AF_NETGRAPH || af == AF_UNSPEC)
		for (tp = netgraphprotox; tp->pr_name; tp++)
			printproto(tp, tp->pr_name, &first);
#endif /* NETGRAPH */
	if ((af == AF_UNIX || af == AF_UNSPEC) && !sflag)
		unixpr(nl[N_UNP_COUNT].n_value, nl[N_UNP_GENCNT].n_value,
		    nl[N_UNP_DHEAD].n_value, nl[N_UNP_SHEAD].n_value,
		    nl[N_UNP_SPHEAD].n_value, &first);

	if (!first)
		xo_close_list("socket");
	xo_close_container("statistics");
	xo_finish();
	exit(0);
}