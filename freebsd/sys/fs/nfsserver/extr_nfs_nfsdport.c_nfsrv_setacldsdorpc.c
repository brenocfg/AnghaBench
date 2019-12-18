#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct nfsrv_descript {int nd_repstat; int /*<<< orphan*/  nd_mrep; } ;
struct nfsmount {int /*<<< orphan*/  nm_sockreq; } ;
struct acl {int dummy; } ;
struct TYPE_3__ {int* other; int seqid; } ;
typedef  TYPE_1__ nfsv4stateid_t ;
typedef  int /*<<< orphan*/  nfsattrbit_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NFSATTRBIT_ACL ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  NFSPROC_SETACL ; 
 int /*<<< orphan*/  NFSSETBIT_ATTRBIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSSTATEID_PUTSTATEID ; 
 int /*<<< orphan*/  NFSZERO_ATTRBIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_PROG ; 
 int /*<<< orphan*/  NFS_VER4 ; 
 int /*<<< orphan*/  free (struct nfsrv_descript*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 struct nfsrv_descript* malloc (int,int /*<<< orphan*/ ,int) ; 
 int newnfs_request (struct nfsrv_descript*,struct nfsmount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfscl_reqstart (struct nfsrv_descript*,int /*<<< orphan*/ ,struct nfsmount*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_stateidtom (struct nfsrv_descript*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsv4_fillattr (struct nfsrv_descript*,int /*<<< orphan*/ *,struct vnode*,struct acl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsrv_setacldsdorpc(fhandle_t *fhp, struct ucred *cred, NFSPROC_T *p,
    struct vnode *vp, struct nfsmount *nmp, struct acl *aclp)
{
	struct nfsrv_descript *nd;
	nfsv4stateid_t st;
	nfsattrbit_t attrbits;
	int error;

	NFSD_DEBUG(4, "in nfsrv_setacldsdorpc\n");
	nd = malloc(sizeof(*nd), M_TEMP, M_WAITOK | M_ZERO);
	/*
	 * Use a stateid where other is an alternating 01010 pattern and
	 * seqid is 0xffffffff.  This value is not defined as special by
	 * the RFC and is used by the FreeBSD NFS server to indicate an
	 * MDS->DS proxy operation.
	 */
	st.other[0] = 0x55555555;
	st.other[1] = 0x55555555;
	st.other[2] = 0x55555555;
	st.seqid = 0xffffffff;
	nfscl_reqstart(nd, NFSPROC_SETACL, nmp, (u_int8_t *)fhp, sizeof(*fhp),
	    NULL, NULL, 0, 0);
	nfsm_stateidtom(nd, &st, NFSSTATEID_PUTSTATEID);
	NFSZERO_ATTRBIT(&attrbits);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_ACL);
	/*
	 * The "vp" argument to nfsv4_fillattr() is only used for vnode_type(),
	 * so passing in the metadata "vp" will be ok, since it is of
	 * the same type (VREG).
	 */
	nfsv4_fillattr(nd, NULL, vp, aclp, NULL, NULL, 0, &attrbits, NULL,
	    NULL, 0, 0, 0, 0, 0, NULL);
	error = newnfs_request(nd, nmp, NULL, &nmp->nm_sockreq, NULL, p, cred,
	    NFS_PROG, NFS_VER4, NULL, 1, NULL, NULL);
	if (error != 0) {
		free(nd, M_TEMP);
		return (error);
	}
	NFSD_DEBUG(4, "nfsrv_setacldsdorpc: aft setaclrpc=%d\n",
	    nd->nd_repstat);
	error = nd->nd_repstat;
	m_freem(nd->nd_mrep);
	free(nd, M_TEMP);
	return (error);
}