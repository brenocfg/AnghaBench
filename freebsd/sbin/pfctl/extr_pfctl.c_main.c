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
typedef  int /*<<< orphan*/  anchorname ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PFCTL_FLAG_ALTQ ; 
 int PFCTL_FLAG_FILTER ; 
 int PFCTL_FLAG_NAT ; 
 int PFCTL_FLAG_OPTION ; 
 int PFCTL_FLAG_TABLE ; 
 int PFCTL_SHOW_LABELS ; 
 int PFCTL_SHOW_NOTHING ; 
 int PFCTL_SHOW_RULES ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PF_DEBUG_NOISY ; 
 int /*<<< orphan*/  PF_DEBUG_NONE ; 
 int /*<<< orphan*/  PF_DEBUG_URGENT ; 
 int PF_OPTIMIZE_BASIC ; 
 int PF_OPTIMIZE_PROFILE ; 
 int PF_OPT_CLRRULECTRS ; 
 int PF_OPT_DEBUG ; 
 int PF_OPT_DISABLE ; 
 int PF_OPT_DUMMYACTION ; 
 int PF_OPT_ENABLE ; 
 int PF_OPT_MERGE ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_NUMERIC ; 
 int PF_OPT_OPTIMIZE ; 
 int PF_OPT_QUIET ; 
 int PF_OPT_RECURSE ; 
 int PF_OPT_SHOWALL ; 
 int PF_OPT_USEDNS ; 
 int PF_OPT_VERBOSE ; 
 int PF_OPT_VERBOSE2 ; 
 int /*<<< orphan*/  PF_OSFP_FILE ; 
 int altqsupport ; 
 char* anchoropt ; 
 char* calloc (int,int) ; 
 int* clearopt ; 
 int /*<<< orphan*/  clearopt_list ; 
 int* debugopt ; 
 int /*<<< orphan*/  debugopt_list ; 
 int dev ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 char* ifaceopt ; 
 int loadopt ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int) ; 
 char* optarg ; 
 int optind ; 
 int* optiopt ; 
 int /*<<< orphan*/  optiopt_list ; 
 char* pf_device ; 
 int /*<<< orphan*/  pfctl_clear_altq (int,int) ; 
 int /*<<< orphan*/  pfctl_clear_fingerprints (int,int) ; 
 int /*<<< orphan*/  pfctl_clear_interface_flags (int,int) ; 
 int /*<<< orphan*/  pfctl_clear_nat (int,int,char*) ; 
 int /*<<< orphan*/  pfctl_clear_rules (int,int,char*) ; 
 int /*<<< orphan*/  pfctl_clear_src_nodes (int,int) ; 
 int /*<<< orphan*/  pfctl_clear_states (int,char*,int) ; 
 int /*<<< orphan*/  pfctl_clear_stats (int,int) ; 
 int /*<<< orphan*/  pfctl_clear_tables (char*,int) ; 
 int /*<<< orphan*/  pfctl_cmdline_symset (char*) ; 
 int pfctl_command_tables (int,char**,char*,int*,char*,char*,int) ; 
 int /*<<< orphan*/  pfctl_debug (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pfctl_disable (int,int) ; 
 scalar_t__ pfctl_enable (int,int) ; 
 scalar_t__ pfctl_file_fingerprints (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pfctl_get_skip_ifaces () ; 
 int /*<<< orphan*/  pfctl_id_kill_states (int,char*,int) ; 
 int /*<<< orphan*/  pfctl_kill_src_nodes (int,char*,int) ; 
 int /*<<< orphan*/  pfctl_label_kill_states (int,char*,int) ; 
 int /*<<< orphan*/  pfctl_load_fingerprints (int,int) ; 
 void* pfctl_lookup_option (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfctl_net_kill_states (int,char*,int) ; 
 scalar_t__ pfctl_rules (int,char*,int,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfctl_show_altq (int,char*,int,int) ; 
 int /*<<< orphan*/  pfctl_show_anchors (int,int,char*) ; 
 int /*<<< orphan*/  pfctl_show_fingerprints (int) ; 
 int /*<<< orphan*/  pfctl_show_ifaces (char*,int) ; 
 int /*<<< orphan*/  pfctl_show_limits (int,int) ; 
 int /*<<< orphan*/  pfctl_show_nat (int,int,char*) ; 
 int /*<<< orphan*/  pfctl_show_rules (int,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int pfctl_show_running (int) ; 
 int /*<<< orphan*/  pfctl_show_src_nodes (int,int) ; 
 int /*<<< orphan*/  pfctl_show_states (int,char*,int) ; 
 int /*<<< orphan*/  pfctl_show_status (int,int) ; 
 int /*<<< orphan*/  pfctl_show_tables (char*,int) ; 
 int /*<<< orphan*/  pfctl_show_timeouts (int,int) ; 
 int pfctl_test_altqsupport (int,int) ; 
 char* rulesopt ; 
 int* showopt ; 
 int /*<<< orphan*/  showopt_list ; 
 char** src_node_kill ; 
 int src_node_killers ; 
 char** state_kill ; 
 int state_killers ; 
 scalar_t__ strchr (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 char* tableopt ; 
 int* tblcmdopt ; 
 int /*<<< orphan*/  tblcmdopt_list ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn_namespace_collision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	int	 error = 0;
	int	 ch;
	int	 mode = O_RDONLY;
	int	 opts = 0;
	int	 optimize = PF_OPTIMIZE_BASIC;
	char	 anchorname[MAXPATHLEN];
	char	*path;

	if (argc < 2)
		usage();

	while ((ch = getopt(argc, argv,
	    "a:AdD:eqf:F:ghi:k:K:mnNOo:Pp:rRs:t:T:vx:z")) != -1) {
		switch (ch) {
		case 'a':
			anchoropt = optarg;
			break;
		case 'd':
			opts |= PF_OPT_DISABLE;
			mode = O_RDWR;
			break;
		case 'D':
			if (pfctl_cmdline_symset(optarg) < 0)
				warnx("could not parse macro definition %s",
				    optarg);
			break;
		case 'e':
			opts |= PF_OPT_ENABLE;
			mode = O_RDWR;
			break;
		case 'q':
			opts |= PF_OPT_QUIET;
			break;
		case 'F':
			clearopt = pfctl_lookup_option(optarg, clearopt_list);
			if (clearopt == NULL) {
				warnx("Unknown flush modifier '%s'", optarg);
				usage();
			}
			mode = O_RDWR;
			break;
		case 'i':
			ifaceopt = optarg;
			break;
		case 'k':
			if (state_killers >= 2) {
				warnx("can only specify -k twice");
				usage();
				/* NOTREACHED */
			}
			state_kill[state_killers++] = optarg;
			mode = O_RDWR;
			break;
		case 'K':
			if (src_node_killers >= 2) {
				warnx("can only specify -K twice");
				usage();
				/* NOTREACHED */
			}
			src_node_kill[src_node_killers++] = optarg;
			mode = O_RDWR;
			break;
		case 'm':
			opts |= PF_OPT_MERGE;
			break;
		case 'n':
			opts |= PF_OPT_NOACTION;
			break;
		case 'N':
			loadopt |= PFCTL_FLAG_NAT;
			break;
		case 'r':
			opts |= PF_OPT_USEDNS;
			break;
		case 'f':
			rulesopt = optarg;
			mode = O_RDWR;
			break;
		case 'g':
			opts |= PF_OPT_DEBUG;
			break;
		case 'A':
			loadopt |= PFCTL_FLAG_ALTQ;
			break;
		case 'R':
			loadopt |= PFCTL_FLAG_FILTER;
			break;
		case 'o':
			optiopt = pfctl_lookup_option(optarg, optiopt_list);
			if (optiopt == NULL) {
				warnx("Unknown optimization '%s'", optarg);
				usage();
			}
			opts |= PF_OPT_OPTIMIZE;
			break;
		case 'O':
			loadopt |= PFCTL_FLAG_OPTION;
			break;
		case 'p':
			pf_device = optarg;
			break;
		case 'P':
			opts |= PF_OPT_NUMERIC;
			break;
		case 's':
			showopt = pfctl_lookup_option(optarg, showopt_list);
			if (showopt == NULL) {
				warnx("Unknown show modifier '%s'", optarg);
				usage();
			}
			break;
		case 't':
			tableopt = optarg;
			break;
		case 'T':
			tblcmdopt = pfctl_lookup_option(optarg, tblcmdopt_list);
			if (tblcmdopt == NULL) {
				warnx("Unknown table command '%s'", optarg);
				usage();
			}
			break;
		case 'v':
			if (opts & PF_OPT_VERBOSE)
				opts |= PF_OPT_VERBOSE2;
			opts |= PF_OPT_VERBOSE;
			break;
		case 'x':
			debugopt = pfctl_lookup_option(optarg, debugopt_list);
			if (debugopt == NULL) {
				warnx("Unknown debug level '%s'", optarg);
				usage();
			}
			mode = O_RDWR;
			break;
		case 'z':
			opts |= PF_OPT_CLRRULECTRS;
			mode = O_RDWR;
			break;
		case 'h':
			/* FALLTHROUGH */
		default:
			usage();
			/* NOTREACHED */
		}
	}

	if (tblcmdopt != NULL) {
		argc -= optind;
		argv += optind;
		ch = *tblcmdopt;
		if (ch == 'l') {
			loadopt |= PFCTL_FLAG_TABLE;
			tblcmdopt = NULL;
		} else
			mode = strchr("acdefkrz", ch) ? O_RDWR : O_RDONLY;
	} else if (argc != optind) {
		warnx("unknown command line argument: %s ...", argv[optind]);
		usage();
		/* NOTREACHED */
	}
	if (loadopt == 0)
		loadopt = ~0;

	if ((path = calloc(1, MAXPATHLEN)) == NULL)
		errx(1, "pfctl: calloc");
	memset(anchorname, 0, sizeof(anchorname));
	if (anchoropt != NULL) {
		int len = strlen(anchoropt);

		if (anchoropt[len - 1] == '*') {
			if (len >= 2 && anchoropt[len - 2] == '/')
				anchoropt[len - 2] = '\0';
			else
				anchoropt[len - 1] = '\0';
			opts |= PF_OPT_RECURSE;
		}
		if (strlcpy(anchorname, anchoropt,
		    sizeof(anchorname)) >= sizeof(anchorname))
			errx(1, "anchor name '%s' too long",
			    anchoropt);
		loadopt &= PFCTL_FLAG_FILTER|PFCTL_FLAG_NAT|PFCTL_FLAG_TABLE;
	}

	if ((opts & PF_OPT_NOACTION) == 0) {
		dev = open(pf_device, mode);
		if (dev == -1)
			err(1, "%s", pf_device);
		altqsupport = pfctl_test_altqsupport(dev, opts);
	} else {
		dev = open(pf_device, O_RDONLY);
		if (dev >= 0)
			opts |= PF_OPT_DUMMYACTION;
		/* turn off options */
		opts &= ~ (PF_OPT_DISABLE | PF_OPT_ENABLE);
		clearopt = showopt = debugopt = NULL;
#if !defined(ENABLE_ALTQ)
		altqsupport = 0;
#else
		altqsupport = 1;
#endif
	}

	if (opts & PF_OPT_DISABLE)
		if (pfctl_disable(dev, opts))
			error = 1;

	if (showopt != NULL) {
		switch (*showopt) {
		case 'A':
			pfctl_show_anchors(dev, opts, anchorname);
			break;
		case 'r':
			pfctl_load_fingerprints(dev, opts);
			pfctl_show_rules(dev, path, opts, PFCTL_SHOW_RULES,
			    anchorname, 0);
			break;
		case 'l':
			pfctl_load_fingerprints(dev, opts);
			pfctl_show_rules(dev, path, opts, PFCTL_SHOW_LABELS,
			    anchorname, 0);
			break;
		case 'n':
			pfctl_load_fingerprints(dev, opts);
			pfctl_show_nat(dev, opts, anchorname);
			break;
		case 'q':
			pfctl_show_altq(dev, ifaceopt, opts,
			    opts & PF_OPT_VERBOSE2);
			break;
		case 's':
			pfctl_show_states(dev, ifaceopt, opts);
			break;
		case 'S':
			pfctl_show_src_nodes(dev, opts);
			break;
		case 'i':
			pfctl_show_status(dev, opts);
			break;
		case 'R':
			error = pfctl_show_running(dev);
			break;
		case 't':
			pfctl_show_timeouts(dev, opts);
			break;
		case 'm':
			pfctl_show_limits(dev, opts);
			break;
		case 'a':
			opts |= PF_OPT_SHOWALL;
			pfctl_load_fingerprints(dev, opts);

			pfctl_show_nat(dev, opts, anchorname);
			pfctl_show_rules(dev, path, opts, 0, anchorname, 0);
			pfctl_show_altq(dev, ifaceopt, opts, 0);
			pfctl_show_states(dev, ifaceopt, opts);
			pfctl_show_src_nodes(dev, opts);
			pfctl_show_status(dev, opts);
			pfctl_show_rules(dev, path, opts, 1, anchorname, 0);
			pfctl_show_timeouts(dev, opts);
			pfctl_show_limits(dev, opts);
			pfctl_show_tables(anchorname, opts);
			pfctl_show_fingerprints(opts);
			break;
		case 'T':
			pfctl_show_tables(anchorname, opts);
			break;
		case 'o':
			pfctl_load_fingerprints(dev, opts);
			pfctl_show_fingerprints(opts);
			break;
		case 'I':
			pfctl_show_ifaces(ifaceopt, opts);
			break;
		}
	}

	if ((opts & PF_OPT_CLRRULECTRS) && showopt == NULL)
		pfctl_show_rules(dev, path, opts, PFCTL_SHOW_NOTHING,
		    anchorname, 0);

	if (clearopt != NULL) {
		if (anchorname[0] == '_' || strstr(anchorname, "/_") != NULL)
			errx(1, "anchor names beginning with '_' cannot "
			    "be modified from the command line");

		switch (*clearopt) {
		case 'r':
			pfctl_clear_rules(dev, opts, anchorname);
			break;
		case 'n':
			pfctl_clear_nat(dev, opts, anchorname);
			break;
		case 'q':
			pfctl_clear_altq(dev, opts);
			break;
		case 's':
			pfctl_clear_states(dev, ifaceopt, opts);
			break;
		case 'S':
			pfctl_clear_src_nodes(dev, opts);
			break;
		case 'i':
			pfctl_clear_stats(dev, opts);
			break;
		case 'a':
			pfctl_clear_rules(dev, opts, anchorname);
			pfctl_clear_nat(dev, opts, anchorname);
			pfctl_clear_tables(anchorname, opts);
			if (!*anchorname) {
				pfctl_clear_altq(dev, opts);
				pfctl_clear_states(dev, ifaceopt, opts);
				pfctl_clear_src_nodes(dev, opts);
				pfctl_clear_stats(dev, opts);
				pfctl_clear_fingerprints(dev, opts);
				pfctl_clear_interface_flags(dev, opts);
			}
			break;
		case 'o':
			pfctl_clear_fingerprints(dev, opts);
			break;
		case 'T':
			pfctl_clear_tables(anchorname, opts);
			break;
		}
	}
	if (state_killers) {
		if (!strcmp(state_kill[0], "label"))
			pfctl_label_kill_states(dev, ifaceopt, opts);
		else if (!strcmp(state_kill[0], "id"))
			pfctl_id_kill_states(dev, ifaceopt, opts);
		else
			pfctl_net_kill_states(dev, ifaceopt, opts);
	}

	if (src_node_killers)
		pfctl_kill_src_nodes(dev, ifaceopt, opts);

	if (tblcmdopt != NULL) {
		error = pfctl_command_tables(argc, argv, tableopt,
		    tblcmdopt, rulesopt, anchorname, opts);
		rulesopt = NULL;
	}
	if (optiopt != NULL) {
		switch (*optiopt) {
		case 'n':
			optimize = 0;
			break;
		case 'b':
			optimize |= PF_OPTIMIZE_BASIC;
			break;
		case 'o':
		case 'p':
			optimize |= PF_OPTIMIZE_PROFILE;
			break;
		}
	}

	if ((rulesopt != NULL) && (loadopt & PFCTL_FLAG_OPTION) &&
	    !anchorname[0] && !(opts & PF_OPT_NOACTION))
		if (pfctl_get_skip_ifaces())
			error = 1;

	if (rulesopt != NULL && !(opts & (PF_OPT_MERGE|PF_OPT_NOACTION)) &&
	    !anchorname[0] && (loadopt & PFCTL_FLAG_OPTION))
		if (pfctl_file_fingerprints(dev, opts, PF_OSFP_FILE))
			error = 1;

	if (rulesopt != NULL) {
		if (anchorname[0] == '_' || strstr(anchorname, "/_") != NULL)
			errx(1, "anchor names beginning with '_' cannot "
			    "be modified from the command line");
		if (pfctl_rules(dev, rulesopt, opts, optimize,
		    anchorname, NULL))
			error = 1;
		else if (!(opts & PF_OPT_NOACTION) &&
		    (loadopt & PFCTL_FLAG_TABLE))
			warn_namespace_collision(NULL);
	}

	if (opts & PF_OPT_ENABLE)
		if (pfctl_enable(dev, opts))
			error = 1;

	if (debugopt != NULL) {
		switch (*debugopt) {
		case 'n':
			pfctl_debug(dev, PF_DEBUG_NONE, opts);
			break;
		case 'u':
			pfctl_debug(dev, PF_DEBUG_URGENT, opts);
			break;
		case 'm':
			pfctl_debug(dev, PF_DEBUG_MISC, opts);
			break;
		case 'l':
			pfctl_debug(dev, PF_DEBUG_NOISY, opts);
			break;
		}
	}

	exit(error);
}