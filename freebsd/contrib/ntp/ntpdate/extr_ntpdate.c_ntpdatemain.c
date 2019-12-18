#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct recvbuf {int dummy; } ;
struct pollfd {int dummy; } ;
struct TYPE_10__ {size_t ni_namelist_len; char** ni_namelist_val; } ;
typedef  TYPE_1__ ni_namelist ;
struct TYPE_11__ {int /*<<< orphan*/  l_uf; int /*<<< orphan*/  l_ui; } ;
typedef  TYPE_2__ l_fp ;
typedef  void* fd_set ;
struct TYPE_12__ {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int BUFSIZ ; 
 int DEFSAMPLES ; 
 scalar_t__ EINTR ; 
 int EOF ; 
 int /*<<< orphan*/  ExpandEnvironmentStrings (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYFILE ; 
 int LFPTOFP (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int LOG_NDELAY ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_NTP ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_UPTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  MINTIMEOUT ; 
 int /*<<< orphan*/  NTPDATE_PRIO ; 
 int NTP_SHIFT ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int SOCKET_ERROR ; 
 int TIMER_HZ ; 
 int /*<<< orphan*/  Version ; 
 int /*<<< orphan*/  WSACleanup () ; 
 scalar_t__ WSAEINTR ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  addserver (char*) ; 
 int /*<<< orphan*/  ai_fam_templ ; 
 scalar_t__ alarm_flag ; 
 int /*<<< orphan*/  always_step ; 
 void* atoi (char*) ; 
 int /*<<< orphan*/  atolfp (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  authistrusted (int) ; 
 int /*<<< orphan*/  authreadkeys (char*) ; 
 int /*<<< orphan*/  authtrust (int,int) ; 
 int /*<<< orphan*/  clear_globals () ; 
 int clock_adjust () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ complete_servers ; 
 scalar_t__ debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fd ; 
 void* fdmask ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  freerecvbuf (struct recvbuf*) ; 
 int full_recvbuffs () ; 
 struct recvbuf* get_full_recv_buffer () ; 
 TYPE_1__* getnetinfoservers () ; 
 int /*<<< orphan*/  init_alarm () ; 
 int /*<<< orphan*/  init_auth () ; 
 int /*<<< orphan*/  init_io () ; 
 int /*<<< orphan*/  init_lib () ; 
 scalar_t__ initializing ; 
 int /*<<< orphan*/  input_handler () ; 
 int /*<<< orphan*/  ipv6_works ; 
 char* key_file ; 
 char* key_file_storage ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxfd ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ nbsock ; 
 int /*<<< orphan*/  never_step ; 
 int /*<<< orphan*/  ni_namelist_free (TYPE_1__*) ; 
 int /*<<< orphan*/  nice (int /*<<< orphan*/ ) ; 
 int ntp_getopt (int,char**,char*) ; 
 char* ntp_optarg ; 
 int ntp_optind ; 
 int /*<<< orphan*/  ntpdate_timerid ; 
 int /*<<< orphan*/  openlog (char*,int,...) ; 
 int poll (void*,unsigned int,int) ; 
 char* progname ; 
 int /*<<< orphan*/  receive (struct recvbuf*) ; 
 int select (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlogmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int simple_query ; 
 int /*<<< orphan*/  ssl_applink () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sys_authdelay ; 
 int sys_authenticate ; 
 int sys_authkey ; 
 scalar_t__ sys_numservers ; 
 scalar_t__ sys_samples ; 
 int sys_timeout ; 
 void* sys_version ; 
 int syslogit ; 
 int /*<<< orphan*/  taskIdSelf () ; 
 int /*<<< orphan*/  taskPrioritySet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ timeout ; 
 int /*<<< orphan*/  timer () ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 
 int unpriv_port ; 
 int verbose ; 

int
ntpdatemain (
	int argc,
	char *argv[]
	)
{
	int was_alarmed;
	int tot_recvbufs;
	struct recvbuf *rbuf;
	l_fp tmp;
	int errflg;
	int c;
	int nfound;

#ifdef HAVE_NETINFO
	ni_namelist *netinfoservers;
#endif
#ifdef SYS_WINNT
	key_file = key_file_storage;

	if (!ExpandEnvironmentStrings(KEYFILE, key_file, MAX_PATH))
		msyslog(LOG_ERR, "ExpandEnvironmentStrings(KEYFILE) failed: %m");

	ssl_applink();
#endif /* SYS_WINNT */

#ifdef NO_MAIN_ALLOWED
	clear_globals();
#endif

	init_lib();	/* sets up ipv4_works, ipv6_works */

	/* Check to see if we have IPv6. Otherwise default to IPv4 */
	if (!ipv6_works)
		ai_fam_templ = AF_INET;

	errflg = 0;
	progname = argv[0];
	syslogit = 0;

	/*
	 * Decode argument list
	 */
	while ((c = ntp_getopt(argc, argv, "46a:bBde:k:o:p:qst:uv")) != EOF)
		switch (c)
		{
		case '4':
			ai_fam_templ = AF_INET;
			break;
		case '6':
			ai_fam_templ = AF_INET6;
			break;
		case 'a':
			c = atoi(ntp_optarg);
			sys_authenticate = 1;
			sys_authkey = c;
			break;
		case 'b':
			always_step++;
			never_step = 0;
			break;
		case 'B':
			never_step++;
			always_step = 0;
			break;
		case 'd':
			++debug;
			break;
		case 'e':
			if (!atolfp(ntp_optarg, &tmp)
			|| tmp.l_ui != 0) {
				(void) fprintf(stderr,
					   "%s: encryption delay %s is unlikely\n",
					   progname, ntp_optarg);
				errflg++;
			} else {
				sys_authdelay = tmp.l_uf;
			}
			break;
		case 'k':
			key_file = ntp_optarg;
			break;
		case 'o':
			sys_version = atoi(ntp_optarg);
			break;
		case 'p':
			c = atoi(ntp_optarg);
			if (c <= 0 || c > NTP_SHIFT) {
				(void) fprintf(stderr,
					   "%s: number of samples (%d) is invalid\n",
					   progname, c);
				errflg++;
			} else {
				sys_samples = c;
			}
			break;
		case 'q':
			simple_query = 1;
			break;
		case 's':
			syslogit = 1;
			break;
		case 't':
			if (!atolfp(ntp_optarg, &tmp)) {
				(void) fprintf(stderr,
					   "%s: timeout %s is undecodeable\n",
					   progname, ntp_optarg);
				errflg++;
			} else {
				sys_timeout = ((LFPTOFP(&tmp) * TIMER_HZ)
					   + 0x8000) >> 16;
				sys_timeout = max(sys_timeout, MINTIMEOUT);
			}
			break;
		case 'v':
			verbose = 1;
			break;
		case 'u':
			unpriv_port = 1;
			break;
		case '?':
			++errflg;
			break;
		default:
			break;
	    }

	if (errflg) {
		(void) fprintf(stderr,
		    "usage: %s [-46bBdqsuv] [-a key#] [-e delay] [-k file] [-p samples] [-o version#] [-t timeo] server ...\n",
		    progname);
		exit(2);
	}

	/*
	 * If number of Samples (-p) not specified by user:
	 * - if a simple_query (-q) just ONE will do
	 * - otherwise the normal is DEFSAMPLES
	 */
	if (sys_samples == 0)
		 sys_samples = (simple_query ? 1 : DEFSAMPLES);

	if (debug || simple_query) {
#ifdef HAVE_SETVBUF
		static char buf[BUFSIZ];
		setvbuf(stdout, buf, _IOLBF, BUFSIZ);
#else
		setlinebuf(stdout);
#endif
	}

	/*
	 * Logging.  Open the syslog if we have to
	 */
	if (syslogit) {
#if !defined (SYS_WINNT) && !defined (SYS_VXWORKS) && !defined SYS_CYGWIN32
# ifndef	LOG_DAEMON
		openlog("ntpdate", LOG_PID);
# else

#  ifndef	LOG_NTP
#	define	LOG_NTP LOG_DAEMON
#  endif
		openlog("ntpdate", LOG_PID | LOG_NDELAY, LOG_NTP);
		if (debug)
			setlogmask(LOG_UPTO(LOG_DEBUG));
		else
			setlogmask(LOG_UPTO(LOG_INFO));
# endif /* LOG_DAEMON */
#endif	/* SYS_WINNT */
	}

	if (debug || verbose)
		msyslog(LOG_NOTICE, "%s", Version);

	/*
	 * Add servers we are going to be polling
	 */
#ifdef HAVE_NETINFO
	netinfoservers = getnetinfoservers();
#endif

	for ( ; ntp_optind < argc; ntp_optind++)
		addserver(argv[ntp_optind]);

#ifdef HAVE_NETINFO
	if (netinfoservers) {
		if ( netinfoservers->ni_namelist_len &&
		    *netinfoservers->ni_namelist_val ) {
			u_int servercount = 0;
			while (servercount < netinfoservers->ni_namelist_len) {
				if (debug) msyslog(LOG_DEBUG,
						   "Adding time server %s from NetInfo configuration.",
						   netinfoservers->ni_namelist_val[servercount]);
				addserver(netinfoservers->ni_namelist_val[servercount++]);
			}
		}
		ni_namelist_free(netinfoservers);
		free(netinfoservers);
	}
#endif

	if (sys_numservers == 0) {
		msyslog(LOG_ERR, "no servers can be used, exiting");
		exit(1);
	}

	/*
	 * Initialize the time of day routines and the I/O subsystem
	 */
	if (sys_authenticate) {
		init_auth();
		if (!authreadkeys(key_file)) {
			msyslog(LOG_ERR, "no key file <%s>, exiting", key_file);
			exit(1);
		}
		authtrust(sys_authkey, 1);
		if (!authistrusted(sys_authkey)) {
			msyslog(LOG_ERR, "authentication key %lu unknown",
				(unsigned long) sys_authkey);
			exit(1);
		}
	}
	init_io();
	init_alarm();

	/*
	 * Set the priority.
	 */
#ifdef SYS_VXWORKS
	taskPrioritySet( taskIdSelf(), NTPDATE_PRIO);
#endif
#if defined(HAVE_ATT_NICE)
	nice (NTPDATE_PRIO);
#endif
#if defined(HAVE_BSD_NICE)
	(void) setpriority(PRIO_PROCESS, 0, NTPDATE_PRIO);
#endif


	initializing = 0;
	was_alarmed = 0;

	while (complete_servers < sys_numservers) {
#ifdef HAVE_POLL_H
		struct pollfd* rdfdes;
		rdfdes = fdmask;
#else
		fd_set rdfdes;
		rdfdes = fdmask;
#endif

		if (alarm_flag) {		/* alarmed? */
			was_alarmed = 1;
			alarm_flag = 0;
		}
		tot_recvbufs = full_recvbuffs();	/* get received buffers */

		if (!was_alarmed && tot_recvbufs == 0) {
			/*
			 * Nothing to do.	 Wait for something.
			 */
#ifdef HAVE_POLL_H
			nfound = poll(rdfdes, (unsigned int)nbsock, timeout.tv_sec * 1000);

#else
			nfound = select(maxfd, &rdfdes, NULL, NULL,
					&timeout);
#endif
			if (nfound > 0)
				input_handler();
			else if (nfound == SOCKET_ERROR)
			{
#ifndef SYS_WINNT
				if (errno != EINTR)
#else
				if (WSAGetLastError() != WSAEINTR)
#endif
					msyslog(LOG_ERR,
#ifdef HAVE_POLL_H
						"poll() error: %m"
#else
						"select() error: %m"
#endif
						);
			} else if (errno != 0) {
#ifndef SYS_VXWORKS
				msyslog(LOG_DEBUG,
#ifdef HAVE_POLL_H
					"poll(): nfound = %d, error: %m",
#else
					"select(): nfound = %d, error: %m",
#endif
					nfound);
#endif
			}
			if (alarm_flag) {		/* alarmed? */
				was_alarmed = 1;
				alarm_flag = 0;
			}
			tot_recvbufs = full_recvbuffs();	/* get received buffers */
		}

		/*
		 * Out here, signals are unblocked.  Call receive
		 * procedure for each incoming packet.
		 */
		rbuf = get_full_recv_buffer();
		while (rbuf != NULL)
		{
			receive(rbuf);
			freerecvbuf(rbuf);
			rbuf = get_full_recv_buffer();
		}

		/*
		 * Call timer to process any timeouts
		 */
		if (was_alarmed) {
			timer();
			was_alarmed = 0;
		}

		/*
		 * Go around again
		 */
	}

	/*
	 * When we get here we've completed the polling of all servers.
	 * Adjust the clock, then exit.
	 */
#ifdef SYS_WINNT
	WSACleanup();
#endif
#ifdef SYS_VXWORKS
	close (fd);
	timer_delete(ntpdate_timerid);
#endif

	return clock_adjust();
}