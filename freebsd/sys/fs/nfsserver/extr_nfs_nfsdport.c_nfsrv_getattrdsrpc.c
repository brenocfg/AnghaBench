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
typedef  int /*<<< orphan*/  u_int8_t ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct nfsvattr {int dummy; } ;
struct nfsrv_descript {int nd_repstat; int /*<<< orphan*/  nd_mrep; } ;
struct nfsmount {int /*<<< orphan*/  nm_sockreq; } ;
typedef  int /*<<< orphan*/  nfsattrbit_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 scalar_t__ LK_EXCLUSIVE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NFSATTRBIT_CHANGE ; 
 int /*<<< orphan*/  NFSATTRBIT_SIZE ; 
 int /*<<< orphan*/  NFSATTRBIT_TIMEACCESS ; 
 int /*<<< orphan*/  NFSATTRBIT_TIMEMODIFY ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  NFSPROC_GETATTR ; 
 int /*<<< orphan*/  NFSSETBIT_ATTRBIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSZERO_ATTRBIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 scalar_t__ VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  free (struct nfsrv_descript*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 struct nfsrv_descript* malloc (int,int /*<<< orphan*/ ,int) ; 
 int newnfs_request (struct nfsrv_descript*,struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfscl_reqstart (struct nfsrv_descript*,int /*<<< orphan*/ ,struct nfsmount*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsrv_putattrbit (struct nfsrv_descript*,int /*<<< orphan*/ *) ; 
 int nfsrv_setextattr (struct vnode*,struct nfsvattr*,int /*<<< orphan*/ *) ; 
 int nfsv4_loadattr (struct nfsrv_descript*,int /*<<< orphan*/ *,struct nfsvattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsrv_getattrdsrpc(fhandle_t *fhp, struct ucred *cred, NFSPROC_T *p,
    struct vnode *vp, struct nfsmount *nmp, struct nfsvattr *nap)
{
	struct nfsrv_descript *nd;
	int error;
	nfsattrbit_t attrbits;
	
	NFSD_DEBUG(4, "in nfsrv_getattrdsrpc\n");
	nd = malloc(sizeof(*nd), M_TEMP, M_WAITOK | M_ZERO);
	nfscl_reqstart(nd, NFSPROC_GETATTR, nmp, (u_int8_t *)fhp,
	    sizeof(fhandle_t), NULL, NULL, 0, 0);
	NFSZERO_ATTRBIT(&attrbits);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_SIZE);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_CHANGE);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_TIMEACCESS);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_TIMEMODIFY);
	(void) nfsrv_putattrbit(nd, &attrbits);
	error = newnfs_request(nd, nmp, NULL, &nmp->nm_sockreq, NULL, p, cred,
	    NFS_PROG, NFS_VER4, NULL, 1, NULL, NULL);
	if (error != 0) {
		free(nd, M_TEMP);
		return (error);
	}
	NFSD_DEBUG(4, "nfsrv_getattrdsrpc: aft getattrrpc=%d\n",
	    nd->nd_repstat);
	if (nd->nd_repstat == 0) {
		error = nfsv4_loadattr(nd, NULL, nap, NULL, NULL, 0,
		    NULL, NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL,
		    NULL, NULL);
		/*
		 * We can only save the updated values in the extended
		 * attribute if the vp is exclusively locked.
		 * This should happen when any of the following operations
		 * occur on the vnode:
		 *    Close, Delegreturn, LayoutCommit, LayoutReturn
		 * As such, the updated extended attribute should get saved
		 * before nfsrv_checkdsattr() returns 0 and allows the cached
		 * attributes to be returned without calling this function.
		 */
		if (error == 0 && VOP_ISLOCKED(vp) == LK_EXCLUSIVE) {
			error = nfsrv_setextattr(vp, nap, p);
			NFSD_DEBUG(4, "nfsrv_getattrdsrpc: aft setextat=%d\n",
			    error);
		}
	} else
		error = nd->nd_repstat;
	m_freem(nd->nd_mrep);
	free(nd, M_TEMP);
	NFSD_DEBUG(4, "nfsrv_getattrdsrpc error=%d\n", error);
	return (error);
}