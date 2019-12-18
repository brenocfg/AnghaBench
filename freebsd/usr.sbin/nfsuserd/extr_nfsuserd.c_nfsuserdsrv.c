#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_short ;
struct svc_req {int rq_proc; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_9__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct passwd {int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_gid; } ;
struct nfsd_idargs {int nid_usertimeout; int nid_ngroup; int /*<<< orphan*/  nid_name; int /*<<< orphan*/  nid_gid; int /*<<< orphan*/  nid_flag; int /*<<< orphan*/ * nid_grps; void* nid_namelen; int /*<<< orphan*/  nid_uid; } ;
struct info {int retval; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct group {int /*<<< orphan*/  gr_name; int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_12__ {int len; scalar_t__ buf; } ;
struct TYPE_13__ {TYPE_1__ xp_rtaddr; } ;
struct TYPE_11__ {int ss_family; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
#define  AF_INET 134 
#define  AF_INET6 133 
 int /*<<< orphan*/  IN6_ARE_ADDR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPPORT_RESERVED ; 
 int /*<<< orphan*/  IPV6PORT_RESERVED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NFSID_ADDGID ; 
 int /*<<< orphan*/  NFSID_ADDGROUPNAME ; 
 int /*<<< orphan*/  NFSID_ADDUID ; 
 int /*<<< orphan*/  NFSID_ADDUSERNAME ; 
 int NFSSVC_IDNAME ; 
 int NFSSVC_NEWSTRUCT ; 
 int NGROUPS ; 
#define  NULLPROC 132 
#define  RPCNFSUSERD_GETGID 131 
#define  RPCNFSUSERD_GETGROUP 130 
#define  RPCNFSUSERD_GETUID 129 
#define  RPCNFSUSERD_GETUSER 128 
 int /*<<< orphan*/  defaultgid ; 
 int /*<<< orphan*/  defaultgroup ; 
 int /*<<< orphan*/  defaultuid ; 
 int /*<<< orphan*/  defaultuser ; 
 void* defusertimeout ; 
 TYPE_10__ fromip ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct group* getgrnam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getgrouplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 struct passwd* getpwnam (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntoa (TYPE_9__) ; 
 int /*<<< orphan*/ * inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  manage_gids ; 
 int nfsbind_localhost () ; 
 int nfssvc (int,struct nfsd_idargs*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 void* strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_getargs (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_sendreply (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_decode (TYPE_2__*) ; 
 int /*<<< orphan*/  svcerr_noproc (TYPE_2__*) ; 
 int /*<<< orphan*/  svcerr_weakauth (TYPE_2__*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  xdr_getid ; 
 int /*<<< orphan*/  xdr_getname ; 
 int /*<<< orphan*/  xdr_retval ; 
 int /*<<< orphan*/  xdr_void ; 

__attribute__((used)) static void
nfsuserdsrv(struct svc_req *rqstp, SVCXPRT *transp)
{
	struct passwd *pwd;
	struct group *grp;
	int error;
#if defined(INET) || defined(INET6)
	u_short sport;
	int ret;
#endif
	struct info info;
	struct nfsd_idargs nid;
	gid_t grps[NGROUPS];
	int ngroup;
#ifdef INET
	struct sockaddr_in *fromsin, *sin;
#endif
#ifdef INET6
	struct sockaddr_in6 *fromsin6, *sin6;
	char buf[INET6_ADDRSTRLEN];
#endif

	/*
	 * Only handle requests from localhost on a reserved port number.
	 * If the upcall is from a different address, call nfsbind_localhost()
	 * to check for a remapping of localhost, due to jails.
	 * (Since a reserved port # at localhost implies a client with
	 *  local root, there won't be a security breach. This is about
	 *  the only case I can think of where a reserved port # means
	 *  something.)
	 */
	if (rqstp->rq_proc != NULLPROC) {
		switch (fromip.ss_family) {
#ifdef INET
		case AF_INET:
			if (transp->xp_rtaddr.len < sizeof(*sin)) {
				syslog(LOG_ERR, "xp_rtaddr too small");
				svcerr_weakauth(transp);
				return;
			}
			sin = (struct sockaddr_in *)transp->xp_rtaddr.buf;
			fromsin = (struct sockaddr_in *)&fromip;
			sport = ntohs(sin->sin_port);
			if (sport >= IPPORT_RESERVED) {
				syslog(LOG_ERR, "not a reserved port#");
				svcerr_weakauth(transp);
				return;
			}
			ret = 1;
			if (sin->sin_addr.s_addr != fromsin->sin_addr.s_addr)
				ret = nfsbind_localhost();
			if (ret == 0 || sin->sin_addr.s_addr !=
			    fromsin->sin_addr.s_addr) {
				syslog(LOG_ERR, "bad from ip %s",
				    inet_ntoa(sin->sin_addr));
				svcerr_weakauth(transp);
				return;
			}
			break;
#endif	/* INET */
#ifdef INET6
		case AF_INET6:
			if (transp->xp_rtaddr.len < sizeof(*sin6)) {
				syslog(LOG_ERR, "xp_rtaddr too small");
				svcerr_weakauth(transp);
				return;
			}
			sin6 = (struct sockaddr_in6 *)transp->xp_rtaddr.buf;
			fromsin6 = (struct sockaddr_in6 *)&fromip;
			sport = ntohs(sin6->sin6_port);
			if (sport >= IPV6PORT_RESERVED) {
				syslog(LOG_ERR, "not a reserved port#");
				svcerr_weakauth(transp);
				return;
			}
			ret = 1;
			if (!IN6_ARE_ADDR_EQUAL(&sin6->sin6_addr,
			    &fromsin6->sin6_addr))
				ret = nfsbind_localhost();
			if (ret == 0 || !IN6_ARE_ADDR_EQUAL(&sin6->sin6_addr,
			    &fromsin6->sin6_addr)) {
				if (inet_ntop(AF_INET6, &sin6->sin6_addr, buf,
				    INET6_ADDRSTRLEN) != NULL)
					syslog(LOG_ERR, "bad from ip %s", buf);
				else
					syslog(LOG_ERR, "bad from ip6 addr");
				svcerr_weakauth(transp);
				return;
			}
			break;
#endif	/* INET6 */
		}
	}
	switch (rqstp->rq_proc) {
	case NULLPROC:
		if (!svc_sendreply(transp, (xdrproc_t)xdr_void, NULL))
			syslog(LOG_ERR, "Can't send reply");
		return;
	case RPCNFSUSERD_GETUID:
		if (!svc_getargs(transp, (xdrproc_t)xdr_getid,
		    (caddr_t)&info)) {
			svcerr_decode(transp);
			return;
		}
		pwd = getpwuid((uid_t)info.id);
		info.retval = 0;
		if (pwd != NULL) {
			nid.nid_usertimeout = defusertimeout;
			nid.nid_uid = pwd->pw_uid;
			nid.nid_name = pwd->pw_name;
			if (manage_gids != 0) {
				/* Get the group list for this user. */
				ngroup = NGROUPS;
				if (getgrouplist(pwd->pw_name, pwd->pw_gid,
				    grps, &ngroup) < 0)
					syslog(LOG_ERR, "Group list too small");
				nid.nid_ngroup = ngroup;
				nid.nid_grps = grps;
			} else {
				nid.nid_ngroup = 0;
				nid.nid_grps = NULL;
			}
		} else {
			nid.nid_usertimeout = 5;
			nid.nid_uid = (uid_t)info.id;
			nid.nid_name = defaultuser;
			nid.nid_ngroup = 0;
			nid.nid_grps = NULL;
		}
		nid.nid_namelen = strlen(nid.nid_name);
		nid.nid_flag = NFSID_ADDUID;
		error = nfssvc(NFSSVC_IDNAME | NFSSVC_NEWSTRUCT, &nid);
		if (error) {
			info.retval = error;
			syslog(LOG_ERR, "Can't add user %s\n", pwd->pw_name);
		} else if (verbose) {
			syslog(LOG_ERR,"Added uid=%d name=%s\n",
			    nid.nid_uid, nid.nid_name);
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_retval,
		    (caddr_t)&info))
			syslog(LOG_ERR, "Can't send reply");
		return;
	case RPCNFSUSERD_GETGID:
		if (!svc_getargs(transp, (xdrproc_t)xdr_getid,
		    (caddr_t)&info)) {
			svcerr_decode(transp);
			return;
		}
		grp = getgrgid((gid_t)info.id);
		info.retval = 0;
		if (grp != NULL) {
			nid.nid_usertimeout = defusertimeout;
			nid.nid_gid = grp->gr_gid;
			nid.nid_name = grp->gr_name;
		} else {
			nid.nid_usertimeout = 5;
			nid.nid_gid = (gid_t)info.id;
			nid.nid_name = defaultgroup;
		}
		nid.nid_namelen = strlen(nid.nid_name);
		nid.nid_ngroup = 0;
		nid.nid_grps = NULL;
		nid.nid_flag = NFSID_ADDGID;
		error = nfssvc(NFSSVC_IDNAME | NFSSVC_NEWSTRUCT, &nid);
		if (error) {
			info.retval = error;
			syslog(LOG_ERR, "Can't add group %s\n",
			    grp->gr_name);
		} else if (verbose) {
			syslog(LOG_ERR,"Added gid=%d name=%s\n",
			    nid.nid_gid, nid.nid_name);
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_retval,
		    (caddr_t)&info))
			syslog(LOG_ERR, "Can't send reply");
		return;
	case RPCNFSUSERD_GETUSER:
		if (!svc_getargs(transp, (xdrproc_t)xdr_getname,
		    (caddr_t)&info)) {
			svcerr_decode(transp);
			return;
		}
		pwd = getpwnam(info.name);
		info.retval = 0;
		if (pwd != NULL) {
			nid.nid_usertimeout = defusertimeout;
			nid.nid_uid = pwd->pw_uid;
			nid.nid_name = pwd->pw_name;
		} else {
			nid.nid_usertimeout = 5;
			nid.nid_uid = defaultuid;
			nid.nid_name = info.name;
		}
		nid.nid_namelen = strlen(nid.nid_name);
		nid.nid_ngroup = 0;
		nid.nid_grps = NULL;
		nid.nid_flag = NFSID_ADDUSERNAME;
		error = nfssvc(NFSSVC_IDNAME | NFSSVC_NEWSTRUCT, &nid);
		if (error) {
			info.retval = error;
			syslog(LOG_ERR, "Can't add user %s\n", pwd->pw_name);
		} else if (verbose) {
			syslog(LOG_ERR,"Added uid=%d name=%s\n",
			    nid.nid_uid, nid.nid_name);
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_retval,
		    (caddr_t)&info))
			syslog(LOG_ERR, "Can't send reply");
		return;
	case RPCNFSUSERD_GETGROUP:
		if (!svc_getargs(transp, (xdrproc_t)xdr_getname,
		    (caddr_t)&info)) {
			svcerr_decode(transp);
			return;
		}
		grp = getgrnam(info.name);
		info.retval = 0;
		if (grp != NULL) {
			nid.nid_usertimeout = defusertimeout;
			nid.nid_gid = grp->gr_gid;
			nid.nid_name = grp->gr_name;
		} else {
			nid.nid_usertimeout = 5;
			nid.nid_gid = defaultgid;
			nid.nid_name = info.name;
		}
		nid.nid_namelen = strlen(nid.nid_name);
		nid.nid_ngroup = 0;
		nid.nid_grps = NULL;
		nid.nid_flag = NFSID_ADDGROUPNAME;
		error = nfssvc(NFSSVC_IDNAME | NFSSVC_NEWSTRUCT, &nid);
		if (error) {
			info.retval = error;
			syslog(LOG_ERR, "Can't add group %s\n",
			    grp->gr_name);
		} else if (verbose) {
			syslog(LOG_ERR,"Added gid=%d name=%s\n",
			    nid.nid_gid, nid.nid_name);
		}
		if (!svc_sendreply(transp, (xdrproc_t)xdr_retval,
		    (caddr_t)&info))
			syslog(LOG_ERR, "Can't send reply");
		return;
	default:
		svcerr_noproc(transp);
		return;
	};
}