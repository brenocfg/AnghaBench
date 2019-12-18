#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct svc_req {scalar_t__ rq_proc; int /*<<< orphan*/  rq_xid; int /*<<< orphan*/  rq_addr; TYPE_1__* rq_args; } ;
struct nfsrv_descript {scalar_t__ nd_procnum; int nd_flag; int nd_repstat; TYPE_1__* nd_mreq; int /*<<< orphan*/ * nd_cred; TYPE_1__* nd_mrep; int /*<<< orphan*/  nd_nam2; int /*<<< orphan*/  nd_nam; TYPE_1__* nd_md; int /*<<< orphan*/  nd_dpos; } ;
typedef  int /*<<< orphan*/  nd ;
struct TYPE_6__ {scalar_t__ m_len; } ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int ND_NFSCB ; 
 int ND_NFSV4 ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,...) ; 
 int NFSERR_AUTHERR ; 
 int /*<<< orphan*/  NFSMGET (TYPE_1__*) ; 
 scalar_t__ NFSPROC_NULL ; 
 scalar_t__ NFSV4PROC_CBCOMPOUND ; 
 int RC_DROPIT ; 
 int RC_REPLY ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (TYPE_1__*) ; 
 int /*<<< orphan*/  mac_cred_associate_nfsd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nfsrv_descript*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtod (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_realign (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int nfs_cbproc (struct nfsrv_descript*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_freereq (struct svc_req*) ; 
 int /*<<< orphan*/  svc_getcred (struct svc_req*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  svc_getrpccaller (struct svc_req*) ; 
 int /*<<< orphan*/  svc_sendreply_mbuf (struct svc_req*,TYPE_1__*) ; 
 int /*<<< orphan*/  svcerr_auth (struct svc_req*,int) ; 
 int /*<<< orphan*/  svcerr_decode (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_noproc (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_systemerr (struct svc_req*) ; 
 int /*<<< orphan*/  svcerr_weakauth (struct svc_req*) ; 

__attribute__((used)) static void
nfscb_program(struct svc_req *rqst, SVCXPRT *xprt)
{
	struct nfsrv_descript nd;
	int cacherep, credflavor;

	memset(&nd, 0, sizeof(nd));
	if (rqst->rq_proc != NFSPROC_NULL &&
	    rqst->rq_proc != NFSV4PROC_CBCOMPOUND) {
		svcerr_noproc(rqst);
		svc_freereq(rqst);
		return;
	}
	nd.nd_procnum = rqst->rq_proc;
	nd.nd_flag = (ND_NFSCB | ND_NFSV4);

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

	NFSCL_DEBUG(1, "cbproc=%d\n",nd.nd_procnum);
	if (nd.nd_procnum != NFSPROC_NULL) {
		if (!svc_getcred(rqst, &nd.nd_cred, &credflavor)) {
			svcerr_weakauth(rqst);
			svc_freereq(rqst);
			m_freem(nd.nd_mrep);
			return;
		}

		/* For now, I don't care what credential flavor was used. */
#ifdef notyet
#ifdef MAC
		mac_cred_associate_nfsd(nd.nd_cred);
#endif
#endif
		cacherep = nfs_cbproc(&nd, rqst->rq_xid);
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
		return;
	}

	if (nd.nd_mreq == NULL) {
		svcerr_decode(rqst);
		svc_freereq(rqst);
		return;
	}

	if (nd.nd_repstat & NFSERR_AUTHERR) {
		svcerr_auth(rqst, nd.nd_repstat & ~NFSERR_AUTHERR);
		if (nd.nd_mreq != NULL)
			m_freem(nd.nd_mreq);
	} else if (!svc_sendreply_mbuf(rqst, nd.nd_mreq))
		svcerr_systemerr(rqst);
	else
		NFSCL_DEBUG(1, "cbrep sent\n");
	svc_freereq(rqst);
}