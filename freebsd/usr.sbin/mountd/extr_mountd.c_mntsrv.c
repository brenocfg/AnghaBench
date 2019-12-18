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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  u_short ;
struct svc_req {int rq_proc; int /*<<< orphan*/  rq_vers; } ;
struct statfs {int /*<<< orphan*/  f_fsid; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int sa_family; int /*<<< orphan*/  sa_len; } ;
struct fhreturn {int fhr_flag; int fhr_numsecflavors; int* fhr_secflavors; int /*<<< orphan*/  fhr_fh; int /*<<< orphan*/  fhr_vers; } ;
struct exportlist {int ex_defnumsecflavors; int* ex_defsecflavors; struct dirlist* ex_dirl; struct dirlist* ex_defdir; } ;
struct dirlist {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  nfsfh_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {struct sockaddr* buf; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  AF_INET 135 
#define  AF_INET6 134 
 int DP_HOSTSET ; 
 int EACCES ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  IPPORT_RESERVED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MNTPATHLEN ; 
#define  MOUNTPROC_DUMP 133 
#define  MOUNTPROC_EXPORT 132 
#define  MOUNTPROC_MNT 131 
#define  MOUNTPROC_UMNT 130 
#define  MOUNTPROC_UMNTALL 129 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
#define  NULLPROC 128 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mlist (char*,char*) ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  chk_host (struct dirlist*,struct sockaddr*,int*,int*,int*,int**) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  del_mlist (char*,char*) ; 
 int /*<<< orphan*/  dir_only ; 
 struct dirlist* dirp_search (struct dirlist*,char*) ; 
 int /*<<< orphan*/  dolog ; 
 int errno ; 
 struct exportlist* ex_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exphead ; 
 int /*<<< orphan*/  getfh (char*,int /*<<< orphan*/ *) ; 
 int getnameinfo (struct sockaddr*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 int /*<<< orphan*/  resvport_only ; 
 int /*<<< orphan*/  scan_tree (struct dirlist*,struct sockaddr*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  svc_getargs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* svc_getrpccaller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_sendreply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_decode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_noproc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_weakauth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int /*<<< orphan*/  xdr_dir ; 
 int /*<<< orphan*/  xdr_explist ; 
 int /*<<< orphan*/  xdr_explist_brief ; 
 int /*<<< orphan*/  xdr_fhs ; 
 int /*<<< orphan*/  xdr_long ; 
 int /*<<< orphan*/  xdr_mlist ; 
 int /*<<< orphan*/  xdr_void ; 

void
mntsrv(struct svc_req *rqstp, SVCXPRT *transp)
{
	struct exportlist *ep;
	struct dirlist *dp;
	struct fhreturn fhr;
	struct stat stb;
	struct statfs fsb;
	char host[NI_MAXHOST], numerichost[NI_MAXHOST];
	int lookup_failed = 1;
	struct sockaddr *saddr;
	u_short sport;
	char rpcpath[MNTPATHLEN + 1], dirpath[MAXPATHLEN];
	int bad = 0, defset, hostset;
	sigset_t sighup_mask;
	int numsecflavors, *secflavorsp;

	sigemptyset(&sighup_mask);
	sigaddset(&sighup_mask, SIGHUP);
	saddr = svc_getrpccaller(transp)->buf;
	switch (saddr->sa_family) {
	case AF_INET6:
		sport = ntohs(((struct sockaddr_in6 *)saddr)->sin6_port);
		break;
	case AF_INET:
		sport = ntohs(((struct sockaddr_in *)saddr)->sin_port);
		break;
	default:
		syslog(LOG_ERR, "request from unknown address family");
		return;
	}
	switch (rqstp->rq_proc) {
	case MOUNTPROC_MNT:
	case MOUNTPROC_UMNT:
	case MOUNTPROC_UMNTALL:
		lookup_failed = getnameinfo(saddr, saddr->sa_len, host,
		    sizeof host, NULL, 0, 0);
	}
	getnameinfo(saddr, saddr->sa_len, numerichost,
	    sizeof numerichost, NULL, 0, NI_NUMERICHOST);
	switch (rqstp->rq_proc) {
	case NULLPROC:
		if (!svc_sendreply(transp, (xdrproc_t)xdr_void, NULL))
			syslog(LOG_ERR, "can't send reply");
		return;
	case MOUNTPROC_MNT:
		if (sport >= IPPORT_RESERVED && resvport_only) {
			syslog(LOG_NOTICE,
			    "mount request from %s from unprivileged port",
			    numerichost);
			svcerr_weakauth(transp);
			return;
		}
		if (!svc_getargs(transp, (xdrproc_t)xdr_dir, rpcpath)) {
			syslog(LOG_NOTICE, "undecodable mount request from %s",
			    numerichost);
			svcerr_decode(transp);
			return;
		}

		/*
		 * Get the real pathname and make sure it is a directory
		 * or a regular file if the -r option was specified
		 * and it exists.
		 */
		if (realpath(rpcpath, dirpath) == NULL ||
		    stat(dirpath, &stb) < 0 ||
		    statfs(dirpath, &fsb) < 0) {
			chdir("/");	/* Just in case realpath doesn't */
			syslog(LOG_NOTICE,
			    "mount request from %s for non existent path %s",
			    numerichost, dirpath);
			if (debug)
				warnx("stat failed on %s", dirpath);
			bad = ENOENT;	/* We will send error reply later */
		}
		if (!bad &&
		    !S_ISDIR(stb.st_mode) &&
		    (dir_only || !S_ISREG(stb.st_mode))) {
			syslog(LOG_NOTICE,
			    "mount request from %s for non-directory path %s",
			    numerichost, dirpath);
			if (debug)
				warnx("mounting non-directory %s", dirpath);
			bad = ENOTDIR;	/* We will send error reply later */
		}

		/* Check in the exports list */
		sigprocmask(SIG_BLOCK, &sighup_mask, NULL);
		if (bad)
			ep = NULL;
		else
			ep = ex_search(&fsb.f_fsid, exphead);
		hostset = defset = 0;
		if (ep && (chk_host(ep->ex_defdir, saddr, &defset, &hostset,
		    &numsecflavors, &secflavorsp) ||
		    ((dp = dirp_search(ep->ex_dirl, dirpath)) &&
		      chk_host(dp, saddr, &defset, &hostset, &numsecflavors,
		       &secflavorsp)) ||
		    (defset && scan_tree(ep->ex_defdir, saddr) == 0 &&
		     scan_tree(ep->ex_dirl, saddr) == 0))) {
			if (bad) {
				if (!svc_sendreply(transp, (xdrproc_t)xdr_long,
				    (caddr_t)&bad))
					syslog(LOG_ERR, "can't send reply");
				sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
				return;
			}
			if (hostset & DP_HOSTSET) {
				fhr.fhr_flag = hostset;
				fhr.fhr_numsecflavors = numsecflavors;
				fhr.fhr_secflavors = secflavorsp;
			} else {
				fhr.fhr_flag = defset;
				fhr.fhr_numsecflavors = ep->ex_defnumsecflavors;
				fhr.fhr_secflavors = ep->ex_defsecflavors;
			}
			fhr.fhr_vers = rqstp->rq_vers;
			/* Get the file handle */
			memset(&fhr.fhr_fh, 0, sizeof(nfsfh_t));
			if (getfh(dirpath, (fhandle_t *)&fhr.fhr_fh) < 0) {
				bad = errno;
				syslog(LOG_ERR, "can't get fh for %s", dirpath);
				if (!svc_sendreply(transp, (xdrproc_t)xdr_long,
				    (caddr_t)&bad))
					syslog(LOG_ERR, "can't send reply");
				sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
				return;
			}
			if (!svc_sendreply(transp, (xdrproc_t)xdr_fhs,
			    (caddr_t)&fhr))
				syslog(LOG_ERR, "can't send reply");
			if (!lookup_failed)
				add_mlist(host, dirpath);
			else
				add_mlist(numerichost, dirpath);
			if (debug)
				warnx("mount successful");
			if (dolog)
				syslog(LOG_NOTICE,
				    "mount request succeeded from %s for %s",
				    numerichost, dirpath);
		} else {
			if (!bad)
				bad = EACCES;
			syslog(LOG_NOTICE,
			    "mount request denied from %s for %s",
			    numerichost, dirpath);
		}

		if (bad && !svc_sendreply(transp, (xdrproc_t)xdr_long,
		    (caddr_t)&bad))
			syslog(LOG_ERR, "can't send reply");
		sigprocmask(SIG_UNBLOCK, &sighup_mask, NULL);
		return;
	case MOUNTPROC_DUMP:
		if (!svc_sendreply(transp, (xdrproc_t)xdr_mlist, (caddr_t)NULL))
			syslog(LOG_ERR, "can't send reply");
		else if (dolog)
			syslog(LOG_NOTICE,
			    "dump request succeeded from %s",
			    numerichost);
		return;
	case MOUNTPROC_UMNT:
		if (sport >= IPPORT_RESERVED && resvport_only) {
			syslog(LOG_NOTICE,
			    "umount request from %s from unprivileged port",
			    numerichost);
			svcerr_weakauth(transp);
			return;
		}
		if (!svc_getargs(transp, (xdrproc_t)xdr_dir, rpcpath)) {
			syslog(LOG_NOTICE, "undecodable umount request from %s",
			    numerichost);
			svcerr_decode(transp);
			return;
		}
		if (realpath(rpcpath, dirpath) == NULL) {
			syslog(LOG_NOTICE, "umount request from %s "
			    "for non existent path %s",
			    numerichost, dirpath);
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_void, (caddr_t)NULL))
			syslog(LOG_ERR, "can't send reply");
		if (!lookup_failed)
			del_mlist(host, dirpath);
		del_mlist(numerichost, dirpath);
		if (dolog)
			syslog(LOG_NOTICE,
			    "umount request succeeded from %s for %s",
			    numerichost, dirpath);
		return;
	case MOUNTPROC_UMNTALL:
		if (sport >= IPPORT_RESERVED && resvport_only) {
			syslog(LOG_NOTICE,
			    "umountall request from %s from unprivileged port",
			    numerichost);
			svcerr_weakauth(transp);
			return;
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_void, (caddr_t)NULL))
			syslog(LOG_ERR, "can't send reply");
		if (!lookup_failed)
			del_mlist(host, NULL);
		del_mlist(numerichost, NULL);
		if (dolog)
			syslog(LOG_NOTICE,
			    "umountall request succeeded from %s",
			    numerichost);
		return;
	case MOUNTPROC_EXPORT:
		if (!svc_sendreply(transp, (xdrproc_t)xdr_explist, (caddr_t)NULL))
			if (!svc_sendreply(transp, (xdrproc_t)xdr_explist_brief,
			    (caddr_t)NULL))
				syslog(LOG_ERR, "can't send reply");
		if (dolog)
			syslog(LOG_NOTICE,
			    "export request succeeded from %s",
			    numerichost);
		return;
	default:
		svcerr_noproc(transp);
		return;
	}
}