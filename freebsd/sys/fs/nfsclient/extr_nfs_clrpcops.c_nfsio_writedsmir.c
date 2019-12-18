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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct nfsfh {int dummy; } ;
struct nfsclwritedsdorpc {int iomode; int must_commit; int len; int vers; int minorvers; scalar_t__ inprog; int /*<<< orphan*/ * p; struct ucred* cred; struct mbuf* m; struct nfsfh* fhp; int /*<<< orphan*/  off; struct nfsclds* dsp; int /*<<< orphan*/ * stateidp; int /*<<< orphan*/  vp; scalar_t__ done; } ;
struct nfsclds {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*,int) ; 
 int nfs_pnfsio (int /*<<< orphan*/ ,struct nfsclwritedsdorpc*) ; 
 scalar_t__ nfs_pnfsiothreads ; 
 int nfsrpc_writedsmir (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,struct nfsclds*,int /*<<< orphan*/ ,int,struct nfsfh*,struct mbuf*,int,int,struct ucred*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_writedsmir ; 

__attribute__((used)) static int
nfsio_writedsmir(vnode_t vp, int *iomode, int *must_commit,
    nfsv4stateid_t *stateidp, struct nfsclds *dsp, uint64_t off, int len,
    struct nfsfh *fhp, struct mbuf *m, int vers, int minorvers,
    struct nfsclwritedsdorpc *drpc, struct ucred *cred, NFSPROC_T *p)
{
	int error, ret;

	error = 0;
	drpc->done = 0;
	drpc->vp = vp;
	drpc->iomode = *iomode;
	drpc->must_commit = *must_commit;
	drpc->stateidp = stateidp;
	drpc->dsp = dsp;
	drpc->off = off;
	drpc->len = len;
	drpc->fhp = fhp;
	drpc->m = m;
	drpc->vers = vers;
	drpc->minorvers = minorvers;
	drpc->cred = cred;
	drpc->p = p;
	drpc->inprog = 0;
	ret = EIO;
	if (nfs_pnfsiothreads != 0) {
		ret = nfs_pnfsio(start_writedsmir, drpc);
		NFSCL_DEBUG(4, "nfsio_writedsmir: nfs_pnfsio=%d\n", ret);
	}
	if (ret != 0)
		error = nfsrpc_writedsmir(vp, iomode, must_commit, stateidp,
		    dsp, off, len, fhp, m, vers, minorvers, cred, p);
	NFSCL_DEBUG(4, "nfsio_writedsmir: error=%d\n", error);
	return (error);
}