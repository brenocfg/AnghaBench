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
typedef  int u_short ;
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHNOREQ ; 
 int /*<<< orphan*/  AUTHREQ ; 
 int /*<<< orphan*/  BCASTSYNC ; 
 int /*<<< orphan*/  CONFIGFILE ; 
 int DEF ; 
 int /*<<< orphan*/  DRIFTFILE ; 
 int /*<<< orphan*/  DVAR ; 
 int /*<<< orphan*/  FORCE_STEP_ONCE ; 
 scalar_t__ HAVE_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV4 ; 
 int /*<<< orphan*/  IPV6 ; 
 int /*<<< orphan*/  JAILDIR ; 
 int /*<<< orphan*/  KEYFILE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  LOOP_MAX ; 
 int NTP_MAXKEY ; 
 char* OPT_ARG (int /*<<< orphan*/ ) ; 
 long OPT_VALUE_UPDATEINTERVAL ; 
 int /*<<< orphan*/  PANICGATE ; 
 int /*<<< orphan*/  PIDFILE ; 
 int /*<<< orphan*/  PROPAGATIONDELAY ; 
 int /*<<< orphan*/  PROTO_AUTHENTICATE ; 
 int /*<<< orphan*/  PROTO_BROADCLIENT ; 
 int /*<<< orphan*/  PROTO_BROADDELAY ; 
 int /*<<< orphan*/  QUIT ; 
 int RW ; 
 int /*<<< orphan*/  SLEW ; 
 int STACKCT_OPT (int /*<<< orphan*/ ) ; 
 char** STACKLST_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATSDIR ; 
 int /*<<< orphan*/  STATS_FREQ_FILE ; 
 int /*<<< orphan*/  STATS_PID_FILE ; 
 int /*<<< orphan*/  STATS_STATSDIR ; 
 void* TRUE ; 
 int /*<<< orphan*/  TRUSTEDKEY ; 
 int /*<<< orphan*/  UPDATEINTERVAL ; 
 int /*<<< orphan*/  USER ; 
 int /*<<< orphan*/  VAR ; 
 void* allow_panic ; 
 scalar_t__ atol (char const*) ; 
 int /*<<< orphan*/  authtrust (int,int) ; 
 scalar_t__ check_netinfo ; 
 char* chrootdir ; 
 int cmdline_server_count ; 
 char** cmdline_servers ; 
 int droproot ; 
 char* erealloc (char*,size_t) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* force_step_once ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  getauthkeys (char*) ; 
 char* group ; 
 long interface_interval ; 
 scalar_t__ ipv4_works ; 
 scalar_t__ ipv6_works ; 
 int /*<<< orphan*/  loop_config (int /*<<< orphan*/ ,int) ; 
 void* mode_ntpdate ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ntpdOptions ; 
 int /*<<< orphan*/  optionUsage (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proto_config (int /*<<< orphan*/ ,int,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sys_var (char const*,scalar_t__,int) ; 
 int sscanf (char const*,char*,double*) ; 
 int /*<<< orphan*/  stats_config (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 char* user ; 

void
getCmdOpts(
	int	argc,
	char **	argv
	)
{
	extern const char *config_file;
	int errflg;

	/*
	 * Initialize, initialize
	 */
	errflg = 0;

	if (ipv4_works && ipv6_works) {
		if (HAVE_OPT( IPV4 ))
			ipv6_works = 0;
		else if (HAVE_OPT( IPV6 ))
			ipv4_works = 0;
	} else if (!ipv4_works && !ipv6_works) {
		msyslog(LOG_ERR, "Neither IPv4 nor IPv6 networking detected, fatal.");
		exit(1);
	} else if (HAVE_OPT( IPV4 ) && !ipv4_works)
		msyslog(LOG_WARNING, "-4/--ipv4 ignored, IPv4 networking not found.");
	else if (HAVE_OPT( IPV6 ) && !ipv6_works)
		msyslog(LOG_WARNING, "-6/--ipv6 ignored, IPv6 networking not found.");

	if (HAVE_OPT( AUTHREQ ))
		proto_config(PROTO_AUTHENTICATE, 1, 0., NULL);
	else if (HAVE_OPT( AUTHNOREQ ))
		proto_config(PROTO_AUTHENTICATE, 0, 0., NULL);

	if (HAVE_OPT( BCASTSYNC ))
		proto_config(PROTO_BROADCLIENT, 1, 0., NULL);

	if (HAVE_OPT( CONFIGFILE )) {
		config_file = OPT_ARG( CONFIGFILE );
#ifdef HAVE_NETINFO
		check_netinfo = 0;
#endif
	}

	if (HAVE_OPT( DRIFTFILE ))
		stats_config(STATS_FREQ_FILE, OPT_ARG( DRIFTFILE ));

	if (HAVE_OPT( PANICGATE ))
		allow_panic = TRUE;

	if (HAVE_OPT( FORCE_STEP_ONCE ))
		force_step_once = TRUE;

#ifdef HAVE_DROPROOT
	if (HAVE_OPT( JAILDIR )) {
		droproot = 1;
		chrootdir = OPT_ARG( JAILDIR );
	}
#endif

	if (HAVE_OPT( KEYFILE ))
		getauthkeys(OPT_ARG( KEYFILE ));

	if (HAVE_OPT( PIDFILE ))
		stats_config(STATS_PID_FILE, OPT_ARG( PIDFILE ));

	if (HAVE_OPT( QUIT ))
		mode_ntpdate = TRUE;

	if (HAVE_OPT( PROPAGATIONDELAY ))
		do {
			double tmp;
			const char *my_ntp_optarg = OPT_ARG( PROPAGATIONDELAY );

			if (sscanf(my_ntp_optarg, "%lf", &tmp) != 1) {
				msyslog(LOG_ERR,
					"command line broadcast delay value %s undecodable",
					my_ntp_optarg);
			} else {
				proto_config(PROTO_BROADDELAY, 0, tmp, NULL);
			}
		} while (0);

	if (HAVE_OPT( STATSDIR ))
		stats_config(STATS_STATSDIR, OPT_ARG( STATSDIR ));

	if (HAVE_OPT( TRUSTEDKEY )) {
		int		ct = STACKCT_OPT(  TRUSTEDKEY );
		const char**	pp = STACKLST_OPT( TRUSTEDKEY );

		do  {
			u_long tkey;
			const char* p = *pp++;

			tkey = (int)atol(p);
			if (tkey == 0 || tkey > NTP_MAXKEY) {
				msyslog(LOG_ERR,
				    "command line trusted key %s is invalid",
				    p);
			} else {
				authtrust(tkey, 1);
			}
		} while (--ct > 0);
	}

#ifdef HAVE_DROPROOT
	if (HAVE_OPT( USER )) {
		droproot = 1;
		user = estrdup(OPT_ARG( USER ));
		group = strrchr(user, ':');
		if (group != NULL) {
			size_t	len;

			*group++ = '\0'; /* get rid of the ':' */
			len = group - user;
			group = estrdup(group);
			user = erealloc(user, len);
		}
	}
#endif

	if (HAVE_OPT( VAR )) {
		int		ct;
		const char **	pp;
		const char *	v_assign;

		ct = STACKCT_OPT(  VAR );
		pp = STACKLST_OPT( VAR );

		do  {
			v_assign = *pp++;
			set_sys_var(v_assign, strlen(v_assign) + 1, RW);
		} while (--ct > 0);
	}

	if (HAVE_OPT( DVAR )) {
		int		ct = STACKCT_OPT(  DVAR );
		const char**	pp = STACKLST_OPT( DVAR );

		do  {
			const char* my_ntp_optarg = *pp++;

			set_sys_var(my_ntp_optarg, strlen(my_ntp_optarg)+1,
			    (u_short) (RW | DEF));
		} while (--ct > 0);
	}

	if (HAVE_OPT( SLEW ))
		loop_config(LOOP_MAX, 600);

	if (HAVE_OPT( UPDATEINTERVAL )) {
		long val = OPT_VALUE_UPDATEINTERVAL;

		if (val >= 0)
			interface_interval = val;
		else {
			fprintf(stderr,
				"command line interface update interval %ld must not be negative\n",
				val);
			msyslog(LOG_ERR,
				"command line interface update interval %ld must not be negative",
				val);
			errflg++;
		}
	}


	/* save list of servers from cmd line for config_peers() use */
	if (argc > 0) {
		cmdline_server_count = argc;
		cmdline_servers = argv;
	}

	/* display usage & exit with any option processing errors */
	if (errflg)
		optionUsage(&ntpdOptions, 2);	/* does not return */
}