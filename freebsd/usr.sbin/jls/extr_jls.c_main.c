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
typedef  int /*<<< orphan*/  lastjid ;
typedef  int /*<<< orphan*/  jid ;
struct TYPE_2__ {int jp_flags; char* jp_name; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int JAIL_DYING ; 
 int /*<<< orphan*/  JLS_XO_VERSION ; 
 int JP_OPT ; 
 int JP_USER ; 
 int PRINT_DEFAULT ; 
 int PRINT_HEADER ; 
 int PRINT_JAIL_NAME ; 
 int PRINT_NAMEVAL ; 
 int PRINT_QUOTED ; 
 int PRINT_SKIP ; 
 int PRINT_VERBOSE ; 
 int /*<<< orphan*/  add_param (char*,...) ; 
 char* alloca (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 void* feature_present (char*) ; 
 int getopt (int,char**,char*) ; 
 void* ip4_ok ; 
 void* ip6_ok ; 
 int /*<<< orphan*/  jail_errmsg ; 
 int nparams ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/ * param_parent ; 
 TYPE_1__* params ; 
 int print_jail (int,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_errx (int,char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_version (int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	char *dot, *ep, *jname, *pname;
	int c, i, jflags, jid, lastjid, pflags, spc;

	argc = xo_parse_args(argc, argv);
	if (argc < 0)
		exit(1);

        xo_set_version(JLS_XO_VERSION);
	jname = NULL;
	pflags = jflags = jid = 0;
	while ((c = getopt(argc, argv, "adj:hNnqsv")) >= 0)
		switch (c) {
		case 'a':
		case 'd':
			jflags |= JAIL_DYING;
			break;
		case 'j':
			jid = strtoul(optarg, &ep, 10);
			if (!jid || *ep) {
				jid = 0;
				jname = optarg;
			}
			break;
		case 'h':
			pflags = (pflags & ~(PRINT_SKIP | PRINT_VERBOSE)) |
			    PRINT_HEADER;
			break;
		case 'N':
			pflags |= PRINT_JAIL_NAME;
			break;
		case 'n':
			pflags = (pflags & ~PRINT_VERBOSE) | PRINT_NAMEVAL;
			break;
		case 'q':
			pflags |= PRINT_QUOTED;
			break;
		case 's':
			pflags = (pflags & ~(PRINT_HEADER | PRINT_VERBOSE)) |
			    PRINT_NAMEVAL | PRINT_QUOTED | PRINT_SKIP;
			break;
		case 'v':
			pflags = (pflags &
			    ~(PRINT_HEADER | PRINT_NAMEVAL | PRINT_SKIP)) |
			    PRINT_VERBOSE;
			break;
		default:
			xo_errx(1, "usage: jls [-dhNnqv] [-j jail] [param ...]");
		}

#ifdef INET6
	ip6_ok = feature_present("inet6");
#endif
#ifdef INET
	ip4_ok = feature_present("inet");
#endif

	/* Add the parameters to print. */
	if (optind == argc) {
		if (pflags & (PRINT_HEADER | PRINT_NAMEVAL))
			add_param("all", NULL, (size_t)0, NULL, JP_USER);
		else if (pflags & PRINT_VERBOSE) {
			add_param("jid", NULL, (size_t)0, NULL, JP_USER);
			add_param("host.hostname", NULL, (size_t)0, NULL,
			    JP_USER);
			add_param("path", NULL, (size_t)0, NULL, JP_USER);
			add_param("name", NULL, (size_t)0, NULL, JP_USER);
			add_param("dying", NULL, (size_t)0, NULL, JP_USER);
			add_param("cpuset.id", NULL, (size_t)0, NULL, JP_USER);
#ifdef INET
			if (ip4_ok)
				add_param("ip4.addr", NULL, (size_t)0, NULL,
				    JP_USER);
#endif
#ifdef INET6
			if (ip6_ok)
				add_param("ip6.addr", NULL, (size_t)0, NULL,
				    JP_USER | JP_OPT);
#endif
		} else {
			pflags |= PRINT_DEFAULT;
			if (pflags & PRINT_JAIL_NAME)
				add_param("name", NULL, (size_t)0, NULL, JP_USER);
			else
				add_param("jid", NULL, (size_t)0, NULL, JP_USER);
#ifdef INET
			if (ip4_ok)
				add_param("ip4.addr", NULL, (size_t)0, NULL,
				    JP_USER);
#endif
			add_param("host.hostname", NULL, (size_t)0, NULL,
			    JP_USER);
			add_param("path", NULL, (size_t)0, NULL, JP_USER);
		}
	} else {
		pflags &= ~PRINT_VERBOSE;
		while (optind < argc)
			add_param(argv[optind++], NULL, (size_t)0, NULL,
			    JP_USER);
	}

	if (pflags & PRINT_SKIP) {
		/* Check for parameters with jailsys parents. */
		for (i = 0; i < nparams; i++) {
			if ((params[i].jp_flags & JP_USER) &&
			    (dot = strchr(params[i].jp_name, '.'))) {
				pname = alloca((dot - params[i].jp_name) + 1);
				strlcpy(pname, params[i].jp_name,
				    (dot - params[i].jp_name) + 1);
				param_parent[i] = add_param(pname,
				    NULL, (size_t)0, NULL, JP_OPT);
			}
		}
	}

	/* Add the index key parameters. */
	if (jid != 0)
		add_param("jid", &jid, sizeof(jid), NULL, 0);
	else if (jname != NULL)
		add_param("name", jname, strlen(jname), NULL, 0);
	else
		add_param("lastjid", &lastjid, sizeof(lastjid), NULL, 0);

	/* Print a header line if requested. */
	if (pflags & PRINT_VERBOSE) {
		xo_emit("{T:/%3s}{T:JID}{P:  }{T:Hostname}{Pd:/%22s}{T:Path}\n",
		        "", "");
		xo_emit("{P:/%8s}{T:Name}{Pd:/%26s}{T:State}\n", "", "");
		xo_emit("{P:/%8s}{T:CPUSetID}\n", "");
		xo_emit("{P:/%8s}{T:IP Address(es)}\n", "");
	}
	else if (pflags & PRINT_DEFAULT)
		if (pflags & PRINT_JAIL_NAME)
			xo_emit("{P: }{T:JID/%-15s}{P: }{T:IP Address/%-15s}"
			        "{P: }{T:Hostname/%-29s}{P: }{T:Path}\n");
		else
			xo_emit("{T:JID/%6s}{P:  }{T:IP Address}{P:/%6s}"
			        "{T:Hostname}{P:/%22s}{T:Path}\n", "", "");
	else if (pflags & PRINT_HEADER) {
		for (i = spc = 0; i < nparams; i++)
			if (params[i].jp_flags & JP_USER) {
				if (spc)
					xo_emit("{P: }");
				else
					spc = 1;
				xo_emit(params[i].jp_name);
			}
		xo_emit("{P:\n}");
	}

	xo_open_container("jail-information");
	xo_open_list("jail");
	/* Fetch the jail(s) and print the parameters. */
	if (jid != 0 || jname != NULL) {
		if (print_jail(pflags, jflags) < 0)
			xo_errx(1, "%s", jail_errmsg);
	} else {
		for (lastjid = 0;
		     (lastjid = print_jail(pflags, jflags)) >= 0; )
			;
		if (errno != 0 && errno != ENOENT)
			xo_errx(1, "%s", jail_errmsg);
	}
	xo_close_list("jail");
	xo_close_container("jail-information");
	xo_finish();
	return (0);
}