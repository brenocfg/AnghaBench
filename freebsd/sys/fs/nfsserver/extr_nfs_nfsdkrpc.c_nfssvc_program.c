#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct svc_req {scalar_t__ rq_vers; size_t rq_proc; scalar_t__ rq_reply_seq; int /*<<< orphan*/  rq_xid; int /*<<< orphan*/  rq_addr; TYPE_1__* rq_args; } ;
struct sockaddr_in {scalar_t__ sin_family; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct nfsrvcache {int dummy; } ;
struct nfsrv_descript {size_t nd_procnum; int nd_flag; int nd_repstat; TYPE_1__* nd_mreq; int /*<<< orphan*/ * nd_cred; TYPE_1__* nd_mrep; struct sockaddr* nd_nam; int /*<<< orphan*/  nd_nam2; TYPE_1__* nd_md; int /*<<< orphan*/  nd_dpos; } ;
typedef  int /*<<< orphan*/  nd ;
struct TYPE_8__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_7__ {scalar_t__ m_len; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int AUTH_SYS ; 
 int INET6_ADDRSTRLEN ; 
 int INET_ADDRSTRLEN ; 
 scalar_t__ IPPORT_RESERVED ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int ND_GSS ; 
 int ND_GSSINTEGRITY ; 
 int ND_GSSPRIVACY ; 
 int ND_NFSV2 ; 
 int ND_NFSV3 ; 
 int ND_NFSV4 ; 
 int NFSERR_AUTHERR ; 
 int /*<<< orphan*/  NFSEXITCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSLOCKV4ROOTMUTEX () ; 
 int /*<<< orphan*/  NFSMGET (TYPE_1__*) ; 
 scalar_t__ NFSPROC_NOOP ; 
 size_t NFSPROC_NULL ; 
 int /*<<< orphan*/  NFSUNLOCKV4ROOTMUTEX () ; 
 size_t NFSV2PROC_STATFS ; 
 size_t NFSV4PROC_COMPOUND ; 
 int /*<<< orphan*/  NFSV4ROOTLOCKMUTEXPTR ; 
 size_t NFS_V3NPROCS ; 
 scalar_t__ NFS_VER2 ; 
 scalar_t__ NFS_VER3 ; 
 int RC_DROPIT ; 
 int RC_REPLY ; 
 int RPCSEC_GSS_KRB5 ; 
 int RPCSEC_GSS_KRB5I ; 
 int RPCSEC_GSS_KRB5P ; 
 scalar_t__ SVC_ACK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 char* inet_ntoa_r (int /*<<< orphan*/ ,char*) ; 
 char* ip6_sprintf (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (TYPE_1__*) ; 
 int /*<<< orphan*/  mac_cred_associate_nfsd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nfsrv_descript*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtod (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__* newnfs_nfsv3_procid ; 
 int /*<<< orphan*/  newnfs_realign (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_privport ; 
 int nfs_proc (struct nfsrv_descript*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsrvcache**) ; 
 int /*<<< orphan*/  nfsd_suspend_lock ; 
 int /*<<< orphan*/  nfsrvd_sentcache (struct nfsrvcache*,int,scalar_t__) ; 
 int /*<<< orphan*/  nfsv4_getref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int nfsvno_v4rootexport (struct nfsrv_descript*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 
 TYPE_2__* satosin6 (struct sockaddr_in*) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getcred (struct svc_req*,int /*<<< orphan*/ **,int*) ; 
 struct sockaddr* svc_getrpccaller (struct svc_req*) ; 
 int /*<<< orphan*/  svc_sendreply_mbuf (struct svc_req*,TYPE_1__*) ; 
 int /*<<< orphan*/  svcerr_auth (struct svc_req*,int) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_weakauth (struct svc_req*) ; 
 int /*<<< orphan*/  td_softdep_cleanup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfssvc_program(struct svc_req *rqst, SVCXPRT *xprt)
{
	struct nfsrv_descript nd;
	struct nfsrvcache *rp = NULL;
	int cacherep, credflavor;

	memset(&nd, 0, sizeof(nd));
	if (rqst->rq_vers == NFS_VER2) {
		if (rqst->rq_proc > NFSV2PROC_STATFS ||
		    newnfs_nfsv3_procid[rqst->rq_proc] == NFSPROC_NOOP) {
			svcerr_noproc(rqst);
			svc_freereq(rqst);
			goto out;
		}
		nd.nd_procnum = newnfs_nfsv3_procid[rqst->rq_proc];
		nd.nd_flag = ND_NFSV2;
	} else if (rqst->rq_vers == NFS_VER3) {
		if (rqst->rq_proc >= NFS_V3NPROCS) {
			svcerr_noproc(rqst);
			svc_freereq(rqst);
			goto out;
		}
		nd.nd_procnum = rqst->rq_proc;
		nd.nd_flag = ND_NFSV3;
	} else {
		if (rqst->rq_proc != NFSPROC_NULL &&
		    rqst->rq_proc != NFSV4PROC_COMPOUND) {
			svcerr_noproc(rqst);
			svc_freereq(rqst);
			goto out;
		}
		nd.nd_procnum = rqst->rq_proc;
		nd.nd_flag = ND_NFSV4;
	}

	/*
	 * Note: we want rq_addr, not svc_getrpccaller for nd_nam2 -
	 * NFS_SRVMAXDATA uses a NULL value for nd_nam2 to detect TCP
	 * mounts.
	 */
	nd.nd_mrep = rqst->rq_args;
	rqst->rq_args = NULL;
	newnfs_realign(&nd.nd_mrep, M_WAITOK);
	nd.nd_md = nd.nd_mrep;
	nd.nd_dpos = mtod(nd.nd_md, caddr_t);
	nd.nd_nam = svc_getrpccaller(rqst);
	nd.nd_nam2 = rqst->rq_addr;
	nd.nd_mreq = NULL;
	nd.nd_cred = NULL;

	if (nfs_privport != 0) {
		/* Check if source port is privileged */
		u_short port;
		struct sockaddr *nam = nd.nd_nam;
		struct sockaddr_in *sin;

		sin = (struct sockaddr_in *)nam;
		/*
		 * INET/INET6 - same code:
		 *    sin_port and sin6_port are at same offset
		 */
		port = ntohs(sin->sin_port);
		if (port >= IPPORT_RESERVED &&
		    nd.nd_procnum != NFSPROC_NULL) {
#ifdef INET6
			char buf[INET6_ADDRSTRLEN];
#else
			char buf[INET_ADDRSTRLEN];
#endif
#ifdef INET6
#if defined(KLD_MODULE)
			/* Do not use ip6_sprintf: the nfs module should work without INET6. */
#define	ip6_sprintf(buf, a)						\
			(sprintf((buf), "%x:%x:%x:%x:%x:%x:%x:%x",	\
			    (a)->s6_addr16[0], (a)->s6_addr16[1],	\
			    (a)->s6_addr16[2], (a)->s6_addr16[3],	\
			    (a)->s6_addr16[4], (a)->s6_addr16[5],	\
			    (a)->s6_addr16[6], (a)->s6_addr16[7]),	\
			    (buf))
#endif
#endif
			printf("NFS request from unprivileged port (%s:%d)\n",
#ifdef INET6
			    sin->sin_family == AF_INET6 ?
			    ip6_sprintf(buf, &satosin6(sin)->sin6_addr) :
#if defined(KLD_MODULE)
#undef ip6_sprintf
#endif
#endif
			    inet_ntoa_r(sin->sin_addr, buf), port);
			svcerr_weakauth(rqst);
			svc_freereq(rqst);
			m_freem(nd.nd_mrep);
			goto out;
		}
	}

	if (nd.nd_procnum != NFSPROC_NULL) {
		if (!svc_getcred(rqst, &nd.nd_cred, &credflavor)) {
			svcerr_weakauth(rqst);
			svc_freereq(rqst);
			m_freem(nd.nd_mrep);
			goto out;
		}

		/* Set the flag based on credflavor */
		if (credflavor == RPCSEC_GSS_KRB5) {
			nd.nd_flag |= ND_GSS;
		} else if (credflavor == RPCSEC_GSS_KRB5I) {
			nd.nd_flag |= (ND_GSS | ND_GSSINTEGRITY);
		} else if (credflavor == RPCSEC_GSS_KRB5P) {
			nd.nd_flag |= (ND_GSS | ND_GSSPRIVACY);
		} else if (credflavor != AUTH_SYS) {
			svcerr_weakauth(rqst);
			svc_freereq(rqst);
			m_freem(nd.nd_mrep);
			goto out;
		}

#ifdef MAC
		mac_cred_associate_nfsd(nd.nd_cred);
#endif
		/*
		 * Get a refcnt (shared lock) on nfsd_suspend_lock.
		 * NFSSVC_SUSPENDNFSD will take an exclusive lock on
		 * nfsd_suspend_lock to suspend these threads.
		 * The call to nfsv4_lock() that precedes nfsv4_getref()
		 * ensures that the acquisition of the exclusive lock
		 * takes priority over acquisition of the shared lock by
		 * waiting for any exclusive lock request to complete.
		 * This must be done here, before the check of
		 * nfsv4root exports by nfsvno_v4rootexport().
		 */
		NFSLOCKV4ROOTMUTEX();
		nfsv4_lock(&nfsd_suspend_lock, 0, NULL, NFSV4ROOTLOCKMUTEXPTR,
		    NULL);
		nfsv4_getref(&nfsd_suspend_lock, NULL, NFSV4ROOTLOCKMUTEXPTR,
		    NULL);
		NFSUNLOCKV4ROOTMUTEX();

		if ((nd.nd_flag & ND_NFSV4) != 0) {
			nd.nd_repstat = nfsvno_v4rootexport(&nd);
			if (nd.nd_repstat != 0) {
				NFSLOCKV4ROOTMUTEX();
				nfsv4_relref(&nfsd_suspend_lock);
				NFSUNLOCKV4ROOTMUTEX();
				svcerr_weakauth(rqst);
				svc_freereq(rqst);
				m_freem(nd.nd_mrep);
				goto out;
			}
		}

		cacherep = nfs_proc(&nd, rqst->rq_xid, xprt, &rp);
		NFSLOCKV4ROOTMUTEX();
		nfsv4_relref(&nfsd_suspend_lock);
		NFSUNLOCKV4ROOTMUTEX();
	} else {
		NFSMGET(nd.nd_mreq);
		nd.nd_mreq->m_len = 0;
		cacherep = RC_REPLY;
	}
	if (nd.nd_mrep != NULL)
		m_freem(nd.nd_mrep);

	if (nd.nd_cred != NULL)
		crfree(nd.nd_cred);

	if (cacherep == RC_DROPIT) {
		if (nd.nd_mreq != NULL)
			m_freem(nd.nd_mreq);
		svc_freereq(rqst);
		goto out;
	}

	if (nd.nd_mreq == NULL) {
		svcerr_decode(rqst);
		svc_freereq(rqst);
		goto out;
	}

	if (nd.nd_repstat & NFSERR_AUTHERR) {
		svcerr_auth(rqst, nd.nd_repstat & ~NFSERR_AUTHERR);
		if (nd.nd_mreq != NULL)
			m_freem(nd.nd_mreq);
	} else if (!svc_sendreply_mbuf(rqst, nd.nd_mreq)) {
		svcerr_systemerr(rqst);
	}
	if (rp != NULL) {
		nfsrvd_sentcache(rp, (rqst->rq_reply_seq != 0 ||
		    SVC_ACK(xprt, NULL)), rqst->rq_reply_seq);
	}
	svc_freereq(rqst);

out:
	td_softdep_cleanup(curthread);
	NFSEXITCODE(0);
}