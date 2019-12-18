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
struct nfsrv_descript {int nd_repstat; int /*<<< orphan*/  nd_mrep; } ;
struct nfsmount {int dummy; } ;
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  nfsv4stateid_t ;
typedef  int /*<<< orphan*/  nfsattrbit_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFSATTRBIT_ACL ; 
 int /*<<< orphan*/  NFSCL_REQSTART (struct nfsrv_descript*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSHASNFSV4 (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSPROC_SETACL ; 
 int /*<<< orphan*/  NFSSETBIT_ATTRBIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSSTATEID_PUTSTATEID ; 
 int /*<<< orphan*/  NFSZERO_ATTRBIT (int /*<<< orphan*/ *) ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int nfscl_request (struct nfsrv_descript*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ucred*,void*) ; 
 int /*<<< orphan*/  nfsm_stateidtom (struct nfsrv_descript*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsv4_fillattr (struct nfsrv_descript*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acl*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsrpc_setaclrpc(vnode_t vp, struct ucred *cred, NFSPROC_T *p,
    struct acl *aclp, nfsv4stateid_t *stateidp, void *stuff)
{
	struct nfsrv_descript nfsd, *nd = &nfsd;
	int error;
	nfsattrbit_t attrbits;
	struct nfsmount *nmp = VFSTONFS(vnode_mount(vp));
	
	if (!NFSHASNFSV4(nmp))
		return (EOPNOTSUPP);
	NFSCL_REQSTART(nd, NFSPROC_SETACL, vp);
	nfsm_stateidtom(nd, stateidp, NFSSTATEID_PUTSTATEID);
	NFSZERO_ATTRBIT(&attrbits);
	NFSSETBIT_ATTRBIT(&attrbits, NFSATTRBIT_ACL);
	(void) nfsv4_fillattr(nd, vnode_mount(vp), vp, aclp, NULL, NULL, 0,
	    &attrbits, NULL, NULL, 0, 0, 0, 0, (uint64_t)0, NULL);
	error = nfscl_request(nd, vp, p, cred, stuff);
	if (error)
		return (error);
	/* Don't care about the pre/postop attributes */
	mbuf_freem(nd->nd_mrep);
	return (nd->nd_repstat);
}