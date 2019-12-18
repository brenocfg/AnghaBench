#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct TYPE_5__ {int acl_cnt; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;
typedef  TYPE_1__ NFSACL_T ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ACL_TYPE_NFS4 ; 
 int ENOENT ; 
 int NFSERR_ATTRNOTSUPP ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 int VOP_SETACL (struct vnode*,int /*<<< orphan*/ ,TYPE_1__*,struct ucred*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_supportsnfsv4acls (struct vnode*) ; 
 int nfsrv_dssetacl (struct vnode*,TYPE_1__*,struct ucred*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsrv_useacl ; 

int
nfsrv_setacl(struct vnode *vp, NFSACL_T *aclp, struct ucred *cred, NFSPROC_T *p)
{
	int error;

	if (nfsrv_useacl == 0 || nfs_supportsnfsv4acls(vp) == 0) {
		error = NFSERR_ATTRNOTSUPP;
		goto out;
	}
	/*
	 * With NFSv4 ACLs, chmod(2) may need to add additional entries.
	 * Make sure it has enough room for that - splitting every entry
	 * into two and appending "canonical six" entries at the end.
	 * Cribbed out of kern/vfs_acl.c - Rick M.
	 */
	if (aclp->acl_cnt > (ACL_MAX_ENTRIES - 6) / 2) {
		error = NFSERR_ATTRNOTSUPP;
		goto out;
	}
	error = VOP_SETACL(vp, ACL_TYPE_NFS4, aclp, cred, p);
	if (error == 0) {
		error = nfsrv_dssetacl(vp, aclp, cred, p);
		if (error == ENOENT)
			error = 0;
	}

out:
	NFSEXITCODE(error);
	return (error);
}