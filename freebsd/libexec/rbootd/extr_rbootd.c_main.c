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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  RMPCONN ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ BootAny ; 
 char* BootDir ; 
 char* BpfGetIntfName (char**) ; 
 int BpfOpen () ; 
 scalar_t__ BpfRead (int /*<<< orphan*/ *,int) ; 
 char* ConfigFile ; 
 int /*<<< orphan*/  DIR_RCVD ; 
 int /*<<< orphan*/ * DbgFp ; 
 scalar_t__ DebugFlg ; 
 int /*<<< orphan*/  DebugOff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DebugOn (int /*<<< orphan*/ ) ; 
 char* DfltConfig ; 
 int /*<<< orphan*/  DispPkt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoTimeout () ; 
 scalar_t__ EINTR ; 
 char* EnetStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Exit (int /*<<< orphan*/ ) ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ GetBootFiles () ; 
 char* IntfName ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int MAXHOSTNAMELEN ; 
 char* MyHost ; 
 scalar_t__ MyPid ; 
 scalar_t__ ParseConfig () ; 
 char* PidFile ; 
 int /*<<< orphan*/  ProcessPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RMP_TIMEOUT ; 
 int /*<<< orphan*/  ReConfig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RmpConns ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN (int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getdtablesize () ; 
 scalar_t__ gethostname (char*,int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char *argv[])
{
	int c, fd, omask, maxfds;
	fd_set rset;

	/*
	 *  Close any open file descriptors.
	 *  Temporarily leave stdin & stdout open for `-d',
	 *  and stderr open for any pre-syslog error messages.
	 */
	{
		int i, nfds = getdtablesize();

		for (i = 0; i < nfds; i++)
			if (i != fileno(stdin) && i != fileno(stdout) &&
			    i != fileno(stderr))
				(void) close(i);
	}

	/*
	 *  Parse any arguments.
	 */
	while ((c = getopt(argc, argv, "adi:")) != -1)
		switch(c) {
		    case 'a':
			BootAny++;
			break;
		    case 'd':
			DebugFlg++;
			break;
		    case 'i':
			IntfName = optarg;
			break;
		    default:
			usage();
		}
	for (; optind < argc; optind++) {
		if (ConfigFile == NULL)
			ConfigFile = argv[optind];
		else {
			warnx("too many config files (`%s' ignored)",
			    argv[optind]);
		}
	}

	if (ConfigFile == NULL)			/* use default config file */
		ConfigFile = DfltConfig;

	if (DebugFlg) {
		DbgFp = stdout;				/* output to stdout */

		(void) signal(SIGUSR1, SIG_IGN);	/* dont muck w/DbgFp */
		(void) signal(SIGUSR2, SIG_IGN);
		(void) fclose(stderr);			/* finished with it */
	} else {
		if (daemon(0, 0))
			err(1, "can't detach from terminal");

		(void) signal(SIGUSR1, DebugOn);
		(void) signal(SIGUSR2, DebugOff);
	}

	openlog("rbootd", LOG_PID, LOG_DAEMON);

	/*
	 *  If no interface was specified, get one now.
	 *
	 *  This is convoluted because we want to get the default interface
	 *  name for the syslog("restarted") message.  If BpfGetIntfName()
	 *  runs into an error, it will return a syslog-able error message
	 *  (in `errmsg') which will be displayed here.
	 */
	if (IntfName == NULL) {
		char *errmsg;

		if ((IntfName = BpfGetIntfName(&errmsg)) == NULL) {
			/* Backslash to avoid trigraph '??)'. */
			syslog(LOG_NOTICE, "restarted (?\?)");
			/* BpfGetIntfName() returns safe names, using %m */
			syslog(LOG_ERR, "%s", errmsg);
			Exit(0);
		}
	}

	syslog(LOG_NOTICE, "restarted (%s)", IntfName);

	(void) signal(SIGHUP, ReConfig);
	(void) signal(SIGINT, Exit);
	(void) signal(SIGTERM, Exit);

	/*
	 *  Grab our host name and pid.
	 */
	if (gethostname(MyHost, MAXHOSTNAMELEN - 1) < 0) {
		syslog(LOG_ERR, "gethostname: %m");
		Exit(0);
	}
	MyHost[MAXHOSTNAMELEN - 1] = '\0';

	MyPid = getpid();

	/*
	 *  Write proc's pid to a file.
	 */
	{
		FILE *fp;

		if ((fp = fopen(PidFile, "w")) != NULL) {
			(void) fprintf(fp, "%d\n", (int) MyPid);
			(void) fclose(fp);
		} else {
			syslog(LOG_WARNING, "fopen: failed (%s)", PidFile);
		}
	}

	/*
	 *  All boot files are relative to the boot directory, we might
	 *  as well chdir() there to make life easier.
	 */
	if (chdir(BootDir) < 0) {
		syslog(LOG_ERR, "chdir: %m (%s)", BootDir);
		Exit(0);
	}

	/*
	 *  Initial configuration.
	 */
	omask = sigblock(sigmask(SIGHUP));	/* prevent reconfig's */
	if (GetBootFiles() == 0)		/* get list of boot files */
		Exit(0);
	if (ParseConfig() == 0)			/* parse config file */
		Exit(0);

	/*
	 *  Open and initialize a BPF device for the appropriate interface.
	 *  If an error is encountered, a message is displayed and Exit()
	 *  is called.
	 */
	fd = BpfOpen();

	(void) sigsetmask(omask);		/* allow reconfig's */

	/*
	 *  Main loop: receive a packet, determine where it came from,
	 *  and if we service this host, call routine to handle request.
	 */
	maxfds = fd + 1;
	FD_ZERO(&rset);
	FD_SET(fd, &rset);
	for (;;) {
		struct timeval timeout;
		fd_set r;
		int nsel;

		r = rset;

		if (RmpConns == NULL) {		/* timeout isn't necessary */
			nsel = select(maxfds, &r, NULL, NULL, NULL);
		} else {
			timeout.tv_sec = RMP_TIMEOUT;
			timeout.tv_usec = 0;
			nsel = select(maxfds, &r, NULL, NULL, &timeout);
		}

		if (nsel < 0) {
			if (errno == EINTR)
				continue;
			syslog(LOG_ERR, "select: %m");
			Exit(0);
		} else if (nsel == 0) {		/* timeout */
			DoTimeout();			/* clear stale conns */
			continue;
		}

		if (FD_ISSET(fd, &r)) {
			RMPCONN rconn;
			CLIENT *client, *FindClient();
			int doread = 1;

			while (BpfRead(&rconn, doread)) {
				doread = 0;

				if (DbgFp != NULL)	/* display packet */
					DispPkt(&rconn,DIR_RCVD);

				omask = sigblock(sigmask(SIGHUP));

				/*
				 *  If we do not restrict service, set the
				 *  client to NULL (ProcessPacket() handles
				 *  this).  Otherwise, check that we can
				 *  service this host; if not, log a message
				 *  and ignore the packet.
				 */
				if (BootAny) {
					client = NULL;
				} else if ((client=FindClient(&rconn))==NULL) {
					syslog(LOG_INFO,
					       "%s: boot packet ignored",
					       EnetStr(&rconn));
					(void) sigsetmask(omask);
					continue;
				}

				ProcessPacket(&rconn,client);

				(void) sigsetmask(omask);
			}
		}
	}
}