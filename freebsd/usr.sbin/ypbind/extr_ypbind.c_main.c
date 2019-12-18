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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct dirent {char* d_name; } ;
struct _dom_binding {int dom_lockfd; int dom_default; struct _dom_binding* dom_pnext; scalar_t__ dom_alive; int /*<<< orphan*/  dom_vers; int /*<<< orphan*/  dom_domain; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* BINDINGDIR ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int /*<<< orphan*/  LOG_PID ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  MADV_PROTECT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MAX_CHILDREN ; 
 int O_CREAT ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  READFD ; 
 int /*<<< orphan*/  RPC_ANYSOCK ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  YPBINDLOCK ; 
 int /*<<< orphan*/  YPBINDPROG ; 
 int /*<<< orphan*/  YPBINDVERS ; 
 scalar_t__ YPMAXDOMAIN ; 
 int /*<<< orphan*/  YPSET_ALL ; 
 int /*<<< orphan*/  YPSET_LOCAL ; 
 int /*<<< orphan*/  YPVERS ; 
 int /*<<< orphan*/  _rpc_dtablesize () ; 
 int /*<<< orphan*/  broadcast (struct _dom_binding*) ; 
 int /*<<< orphan*/  bzero (struct _dom_binding*,int) ; 
 int /*<<< orphan*/  checkwork () ; 
 int /*<<< orphan*/  children ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* domain_name ; 
 int /*<<< orphan*/  domains ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fdsr ; 
 int flock (int,int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  handle_children (struct _dom_binding*) ; 
 scalar_t__ madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct _dom_binding* malloc (int) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  openlog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppid ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reaper ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  svc_fdset ; 
 int /*<<< orphan*/  svc_getreqset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svctcp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svcudp_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * tcptransp ; 
 int /*<<< orphan*/  terminate ; 
 int /*<<< orphan*/ * udptransp ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 
 int /*<<< orphan*/  yp_get_default_domain (char**) ; 
 int /*<<< orphan*/  yp_manycast ; 
 int /*<<< orphan*/  yp_restricted_mode (char*) ; 
 struct _dom_binding* ypbindlist ; 
 int /*<<< orphan*/  ypbindprog_2 ; 
 int yplockfd ; 
 int /*<<< orphan*/  ypsecuremode ; 
 int /*<<< orphan*/  ypsetmode ; 

int
main(int argc, char *argv[])
{
	struct timeval tv;
	int i;
	DIR *dird;
	struct dirent *dirp;
	struct _dom_binding *ypdb, *next;

	/* Check that another ypbind isn't already running. */
	if ((yplockfd = (open(YPBINDLOCK, O_RDONLY|O_CREAT, 0444))) == -1)
		err(1, "%s", YPBINDLOCK);

	if (flock(yplockfd, LOCK_EX|LOCK_NB) == -1 && errno == EWOULDBLOCK)
		errx(1, "another ypbind is already running. Aborting");

	/* XXX domainname will be overridden if we use restricted mode */
	yp_get_default_domain(&domain_name);
	if (domain_name[0] == '\0')
		errx(1, "domainname not set. Aborting");

	for (i = 1; i<argc; i++) {
		if (strcmp("-ypset", argv[i]) == 0)
			ypsetmode = YPSET_ALL;
		else if (strcmp("-ypsetme", argv[i]) == 0)
		        ypsetmode = YPSET_LOCAL;
		else if (strcmp("-s", argv[i]) == 0)
		        ypsecuremode++;
		else if (strcmp("-S", argv[i]) == 0 && argc > i)
			yp_restricted_mode(argv[++i]);
		else if (strcmp("-m", argv[i]) == 0)
			yp_manycast++;
		else
			errx(1, "unknown option: %s", argv[i]);
	}

	if (strlen(domain_name) > YPMAXDOMAIN)
		warnx("truncating domain name %s", domain_name);

	/* blow away everything in BINDINGDIR (if it exists) */

	if ((dird = opendir(BINDINGDIR)) != NULL) {
		char path[MAXPATHLEN];
		while ((dirp = readdir(dird)) != NULL)
			if (strcmp(dirp->d_name, ".") &&
			    strcmp(dirp->d_name, "..")) {
				sprintf(path,"%s/%s",BINDINGDIR,dirp->d_name);
				unlink(path);
			}
		closedir(dird);
	}

#ifdef DAEMON
	if (daemon(0,0))
		err(1, "fork");
#endif

	pmap_unset(YPBINDPROG, YPBINDVERS);

	udptransp = svcudp_create(RPC_ANYSOCK);
	if (udptransp == NULL)
		errx(1, "cannot create udp service");
	if (!svc_register(udptransp, YPBINDPROG, YPBINDVERS, ypbindprog_2,
	    IPPROTO_UDP))
		errx(1, "unable to register (YPBINDPROG, YPBINDVERS, udp)");

	tcptransp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (tcptransp == NULL)
		errx(1, "cannot create tcp service");

	if (!svc_register(tcptransp, YPBINDPROG, YPBINDVERS, ypbindprog_2,
	    IPPROTO_TCP))
		errx(1, "unable to register (YPBINDPROG, YPBINDVERS, tcp)");

	/* build initial domain binding, make it "unsuccessful" */
	ypbindlist = malloc(sizeof *ypbindlist);
	if (ypbindlist == NULL)
		errx(1, "malloc");
	bzero(ypbindlist, sizeof *ypbindlist);
	strlcpy(ypbindlist->dom_domain, domain_name, sizeof ypbindlist->dom_domain);
	ypbindlist->dom_vers = YPVERS;
	ypbindlist->dom_alive = 0;
	ypbindlist->dom_lockfd = -1;
	ypbindlist->dom_default = 1;
	domains++;

	signal(SIGCHLD, reaper);
	signal(SIGTERM, terminate);

	ppid = getpid(); /* Remember who we are. */

	openlog(argv[0], LOG_PID, LOG_DAEMON);

	if (madvise(NULL, 0, MADV_PROTECT) != 0)
		syslog(LOG_WARNING, "madvise(): %m");

	/* Kick off the default domain */
	broadcast(ypbindlist);

	while (1) {
		fdsr = svc_fdset;

		tv.tv_sec = 60;
		tv.tv_usec = 0;

		switch (select(_rpc_dtablesize(), &fdsr, NULL, NULL, &tv)) {
		case 0:
			checkwork();
			break;
		case -1:
			if (errno != EINTR)
				syslog(LOG_WARNING, "select: %m");
			break;
		default:
			for (ypdb = ypbindlist; ypdb; ypdb = next) {
				next = ypdb->dom_pnext;
				if (READFD > 0 && FD_ISSET(READFD, &fdsr)) {
					handle_children(ypdb);
					if (children == (MAX_CHILDREN - 1))
						checkwork();
				}
			}
			svc_getreqset(&fdsr);
			break;
		}
	}

	/* NOTREACHED */
	exit(1);
}