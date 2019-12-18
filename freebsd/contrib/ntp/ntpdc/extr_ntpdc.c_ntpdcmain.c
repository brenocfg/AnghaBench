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
struct TYPE_2__ {int /*<<< orphan*/  l_uf; scalar_t__ l_ui; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDCMD (char*) ; 
 int /*<<< orphan*/  ADDHOST (char*) ; 
 void* AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DEFDELAY ; 
 char* DEFHOST ; 
 scalar_t__ HAVE_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITDATASIZE ; 
 int /*<<< orphan*/  INTERACTIVE ; 
 int /*<<< orphan*/  IPV4 ; 
 int /*<<< orphan*/  IPV6 ; 
 int /*<<< orphan*/  LISTPEERS ; 
 int /*<<< orphan*/  NUMERIC ; 
 int /*<<< orphan*/  OPT_VALUE_SET_DEBUG_LEVEL ; 
 int /*<<< orphan*/  PEERS ; 
 int /*<<< orphan*/  SHOWPEERS ; 
 int /*<<< orphan*/  SIGINT ; 
 int STACKCT_OPT (int /*<<< orphan*/ ) ; 
 char** STACKLST_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  abortcmd ; 
 void* ai_fam_default ; 
 void* ai_fam_templ ; 
 int /*<<< orphan*/ * ccmds ; 
 char** chosts ; 
 int /*<<< orphan*/  clear_globals () ; 
 int /*<<< orphan*/  debug ; 
 TYPE_1__ delay_time ; 
 int /*<<< orphan*/  docmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcmds () ; 
 int /*<<< orphan*/  init_auth () ; 
 int /*<<< orphan*/  init_lib () ; 
 int interactive ; 
 int /*<<< orphan*/  ipv6_works ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int ntpOptionProcess (int /*<<< orphan*/ *,int,char**) ; 
 int ntp_optind ; 
 int /*<<< orphan*/  ntpdcOptions ; 
 int numcmds ; 
 int numhosts ; 
 scalar_t__ openhost (char*) ; 
 int /*<<< orphan*/  pktdata ; 
 int /*<<< orphan*/  pktdatasize ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 scalar_t__ showhostnames ; 
 int /*<<< orphan*/  signal_no_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_applink () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  taskIdSelf () ; 
 int /*<<< orphan*/  taskPrioritySet (int /*<<< orphan*/ ,int) ; 

int
ntpdcmain(
	int argc,
	char *argv[]
	)
{
	delay_time.l_ui = 0;
	delay_time.l_uf = DEFDELAY;

#ifdef SYS_VXWORKS
	clear_globals();
	taskPrioritySet(taskIdSelf(), 100 );
#endif

	init_lib();	/* sets up ipv4_works, ipv6_works */
	ssl_applink();
	init_auth();

	/* Check to see if we have IPv6. Otherwise default to IPv4 */
	if (!ipv6_works)
		ai_fam_default = AF_INET;

	progname = argv[0];

	{
		int optct = ntpOptionProcess(&ntpdcOptions, argc, argv);
		argc -= optct;
		argv += optct;
	}

	if (HAVE_OPT(IPV4))
		ai_fam_templ = AF_INET;
	else if (HAVE_OPT(IPV6))
		ai_fam_templ = AF_INET6;
	else
		ai_fam_templ = ai_fam_default;

	if (HAVE_OPT(COMMAND)) {
		int		cmdct = STACKCT_OPT( COMMAND );
		const char**	cmds  = STACKLST_OPT( COMMAND );

		while (cmdct-- > 0) {
			ADDCMD(*cmds++);
		}
	}

	debug = OPT_VALUE_SET_DEBUG_LEVEL;

	if (HAVE_OPT(INTERACTIVE)) {
		interactive = 1;
	}

	if (HAVE_OPT(NUMERIC)) {
		showhostnames = 0;
	}

	if (HAVE_OPT(LISTPEERS)) {
		ADDCMD("listpeers");
	}

	if (HAVE_OPT(PEERS)) {
		ADDCMD("peers");
	}

	if (HAVE_OPT(SHOWPEERS)) {
		ADDCMD("dmpeers");
	}

	if (ntp_optind == argc) {
		ADDHOST(DEFHOST);
	} else {
		for (; ntp_optind < argc; ntp_optind++)
		    ADDHOST(argv[ntp_optind]);
	}

	if (numcmds == 0 && interactive == 0
	    && isatty(fileno(stdin)) && isatty(fileno(stderr))) {
		interactive = 1;
	}

#ifndef SYS_WINNT /* Under NT cannot handle SIGINT, WIN32 spawns a handler */
	if (interactive)
		(void) signal_no_reset(SIGINT, abortcmd);
#endif /* SYS_WINNT */

	/*
	 * Initialize the packet data buffer
	 */
	pktdatasize = INITDATASIZE;
	pktdata = emalloc(INITDATASIZE);

	if (numcmds == 0) {
		(void) openhost(chosts[0]);
		getcmds();
	} else {
		int ihost;
		int icmd;

		for (ihost = 0; ihost < numhosts; ihost++) {
			if (openhost(chosts[ihost]))
			    for (icmd = 0; icmd < numcmds; icmd++) {
				    if (numhosts > 1) 
					printf ("--- %s ---\n",chosts[ihost]);
				    docmd(ccmds[icmd]);
			    }
		}
	}
#ifdef SYS_WINNT
	WSACleanup();
#endif
	return(0);
}