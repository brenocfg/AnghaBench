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
struct nfsd_nfsd_args {char* principal; scalar_t__ minthreads; scalar_t__ maxthreads; } ;
struct addrinfo {char* ai_canonname; int /*<<< orphan*/  ai_flags; } ;
typedef  int /*<<< orphan*/  principal ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AI_CANONNAME ; 
 scalar_t__ EAUTH ; 
 scalar_t__ ENXIO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ get_tuned_nfsdcount () ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ masterpid ; 
 scalar_t__ maxthreads ; 
 scalar_t__ maxthreads_set ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ minthreads ; 
 scalar_t__ minthreads_set ; 
 int /*<<< orphan*/  nfsd_exit (int) ; 
 scalar_t__ nfsdcnt ; 
 scalar_t__ nfsdcnt_set ; 
 int nfssvc (int /*<<< orphan*/ ,struct nfsd_nfsd_args*) ; 
 int /*<<< orphan*/  nfssvc_nfsd ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
start_server(int master, struct nfsd_nfsd_args *nfsdargp, const char *vhost)
{
	char principal[MAXHOSTNAMELEN + 5];
	int status, error;
	char hostname[MAXHOSTNAMELEN + 1], *cp;
	struct addrinfo *aip, hints;

	status = 0;
	if (vhost == NULL)
		gethostname(hostname, sizeof (hostname));
	else
		strlcpy(hostname, vhost, sizeof (hostname));
	snprintf(principal, sizeof (principal), "nfs@%s", hostname);
	if ((cp = strchr(hostname, '.')) == NULL ||
	    *(cp + 1) == '\0') {
		/* If not fully qualified, try getaddrinfo() */
		memset((void *)&hints, 0, sizeof (hints));
		hints.ai_flags = AI_CANONNAME;
		error = getaddrinfo(hostname, NULL, &hints, &aip);
		if (error == 0) {
			if (aip->ai_canonname != NULL &&
			    (cp = strchr(aip->ai_canonname, '.')) !=
			    NULL && *(cp + 1) != '\0')
				snprintf(principal, sizeof (principal),
				    "nfs@%s", aip->ai_canonname);
			freeaddrinfo(aip);
		}
	}
	nfsdargp->principal = principal;

	if (nfsdcnt_set)
		nfsdargp->minthreads = nfsdargp->maxthreads = nfsdcnt;
	else {
		nfsdargp->minthreads = minthreads_set ? minthreads : get_tuned_nfsdcount();
		nfsdargp->maxthreads = maxthreads_set ? maxthreads : nfsdargp->minthreads;
		if (nfsdargp->maxthreads < nfsdargp->minthreads)
			nfsdargp->maxthreads = nfsdargp->minthreads;
	}
	error = nfssvc(nfssvc_nfsd, nfsdargp);
	if (error < 0 && errno == EAUTH) {
		/*
		 * This indicates that it could not register the
		 * rpcsec_gss credentials, usually because the
		 * gssd daemon isn't running.
		 * (only the experimental server with nfsv4)
		 */
		syslog(LOG_ERR, "No gssd, using AUTH_SYS only");
		principal[0] = '\0';
		error = nfssvc(nfssvc_nfsd, nfsdargp);
	}
	if (error < 0) {
		if (errno == ENXIO) {
			syslog(LOG_ERR, "Bad -p option, cannot run");
			if (masterpid != 0 && master == 0)
				kill(masterpid, SIGUSR1);
		} else
			syslog(LOG_ERR, "nfssvc: %m");
		status = 1;
	}
	if (master)
		nfsd_exit(status);
	else
		exit(status);
}