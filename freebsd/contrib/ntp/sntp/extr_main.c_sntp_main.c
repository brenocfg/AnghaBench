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
struct event_config {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; } ;
struct TYPE_3__ {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  BROADCAST ; 
 int /*<<< orphan*/  CONCURRENT ; 
 int CTX_BCST ; 
 int CTX_CONC ; 
 int CTX_UCST ; 
 scalar_t__ ENABLED_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_FEATURE_FDS ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HAVE_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV4 ; 
 int /*<<< orphan*/  IPV6 ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  KEYFILE ; 
 int /*<<< orphan*/  KOD ; 
 int /*<<< orphan*/  LOGFILE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  OPT_ARG (int /*<<< orphan*/ ) ; 
 int OPT_VALUE_GAP ; 
 int /*<<< orphan*/  OPT_VALUE_NTPVERSION ; 
 scalar_t__ OPT_VALUE_SET_DEBUG_LEVEL ; 
 int OPT_VALUE_STEPLIMIT ; 
 int /*<<< orphan*/  OPT_VALUE_TIMEOUT ; 
 int /*<<< orphan*/  SLEW ; 
 int STACKCT_OPT (int /*<<< orphan*/ ) ; 
 char** STACKLST_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STEP ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * addremove_io_fd ; 
 int /*<<< orphan*/  ai_fam_pref ; 
 int /*<<< orphan*/  auth_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_config_require_features (struct event_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_enable_debug_mode () ; 
 int /*<<< orphan*/  event_set_log_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evthread_enable_lock_debuging () ; 
 int /*<<< orphan*/  evthread_use_pthreads () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_2__ gap ; 
 int /*<<< orphan*/  gettimeofday_cached (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_lookup (char const*,int) ; 
 int /*<<< orphan*/  init_auth () ; 
 int /*<<< orphan*/  init_lib () ; 
 scalar_t__ ipv4_works ; 
 scalar_t__ ipv6_works ; 
 scalar_t__ isc_net_probeipv6 () ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  kod_init_kod_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libevent_version_ok () ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 
 int ntpOptionProcess (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  ntpver ; 
 int /*<<< orphan*/  open_logfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_sockets () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  response_timeout ; 
 TYPE_1__ response_tv ; 
 int /*<<< orphan*/  sntpOptions ; 
 int /*<<< orphan*/  sntp_addremove_fd ; 
 int /*<<< orphan*/  sntp_init_logging (char*) ; 
 int /*<<< orphan*/  sntp_libevent_log_cb ; 
 int /*<<< orphan*/  start_tv ; 
 int steplimit ; 
 int /*<<< orphan*/  time_adjusted ; 
 int /*<<< orphan*/  worker_per_query ; 

int
sntp_main (
	int argc,
	char **argv,
	const char *sntpVersion
	)
{
	int			i;
	int			exitcode;
	int			optct;
	struct event_config *	evcfg;

	/* Initialize logging system - sets up progname */
	sntp_init_logging(argv[0]);

	if (!libevent_version_ok())
		exit(EX_SOFTWARE);

	init_lib();
	init_auth();

	optct = ntpOptionProcess(&sntpOptions, argc, argv);
	argc -= optct;
	argv += optct;


	debug = OPT_VALUE_SET_DEBUG_LEVEL;

	TRACE(2, ("init_lib() done, %s%s\n",
		  (ipv4_works)
		      ? "ipv4_works "
		      : "",
		  (ipv6_works)
		      ? "ipv6_works "
		      : ""));
	ntpver = OPT_VALUE_NTPVERSION;
	steplimit = OPT_VALUE_STEPLIMIT / 1e3;
	gap.tv_usec = max(0, OPT_VALUE_GAP * 1000);
	gap.tv_usec = min(gap.tv_usec, 999999);

	if (HAVE_OPT(LOGFILE))
		open_logfile(OPT_ARG(LOGFILE));

	msyslog(LOG_INFO, "%s", sntpVersion);

	if (0 == argc && !HAVE_OPT(BROADCAST) && !HAVE_OPT(CONCURRENT)) {
		printf("%s: Must supply at least one of -b hostname, -c hostname, or hostname.\n",
		       progname);
		exit(EX_USAGE);
	}


	/*
	** Eventually, we probably want:
	** - separate bcst and ucst timeouts (why?)
	** - multiple --timeout values in the commandline
	*/

	response_timeout = OPT_VALUE_TIMEOUT;
	response_tv.tv_sec = response_timeout;
	response_tv.tv_usec = 0;

	/* IPv6 available? */
	if (isc_net_probeipv6() != ISC_R_SUCCESS) {
		ai_fam_pref = AF_INET;
		TRACE(1, ("No ipv6 support available, forcing ipv4\n"));
	} else {
		/* Check for options -4 and -6 */
		if (HAVE_OPT(IPV4))
			ai_fam_pref = AF_INET;
		else if (HAVE_OPT(IPV6))
			ai_fam_pref = AF_INET6;
	}

	/* TODO: Parse config file if declared */

	/*
	** Init the KOD system.
	** For embedded systems with no writable filesystem,
	** -K /dev/null can be used to disable KoD storage.
	*/
	kod_init_kod_db(OPT_ARG(KOD), FALSE);

	/* HMS: Check and see what happens if KEYFILE doesn't exist */
	auth_init(OPT_ARG(KEYFILE), &keys);

	/*
	** Considering employing a variable that prevents functions of doing
	** anything until everything is initialized properly
	**
	** HMS: What exactly does the above mean?
	*/
	event_set_log_callback(&sntp_libevent_log_cb);
	if (debug > 0)
		event_enable_debug_mode();
#ifdef WORK_THREAD
	evthread_use_pthreads();
	/* we use libevent from main thread only, locks should be academic */
	if (debug > 0)
		evthread_enable_lock_debuging();
#endif
	evcfg = event_config_new();
	if (NULL == evcfg) {
		printf("%s: event_config_new() failed!\n", progname);
		return -1;
	}
#ifndef HAVE_SOCKETPAIR
	event_config_require_features(evcfg, EV_FEATURE_FDS);
#endif
	/* all libevent calls are from main thread */
	/* event_config_set_flag(evcfg, EVENT_BASE_FLAG_NOLOCK); */
	base = event_base_new_with_config(evcfg);
	event_config_free(evcfg);
	if (NULL == base) {
		printf("%s: event_base_new() failed!\n", progname);
		return -1;
	}

	/* wire into intres resolver */
	worker_per_query = TRUE;
	addremove_io_fd = &sntp_addremove_fd;

	open_sockets();

	if (HAVE_OPT(BROADCAST)) {
		int		cn = STACKCT_OPT(  BROADCAST );
		const char **	cp = STACKLST_OPT( BROADCAST );

		while (cn-- > 0) {
			handle_lookup(*cp, CTX_BCST);
			cp++;
		}
	}

	if (HAVE_OPT(CONCURRENT)) {
		int		cn = STACKCT_OPT( CONCURRENT );
		const char **	cp = STACKLST_OPT( CONCURRENT );

		while (cn-- > 0) {
			handle_lookup(*cp, CTX_UCST | CTX_CONC);
			cp++;
		}
	}

	for (i = 0; i < argc; ++i)
		handle_lookup(argv[i], CTX_UCST);

	gettimeofday_cached(base, &start_tv);
	event_base_dispatch(base);
	event_base_free(base);

	if (!time_adjusted &&
	    (ENABLED_OPT(STEP) || ENABLED_OPT(SLEW)))
		exitcode = 1;
	else
		exitcode = 0;

	return exitcode;
}