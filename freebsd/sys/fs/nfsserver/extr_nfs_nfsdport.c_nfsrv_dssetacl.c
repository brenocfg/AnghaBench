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
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  NFSPROC_SETACL ; 
 int nfsrv_proxyds (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acl*) ; 

__attribute__((used)) static int
nfsrv_dssetacl(struct vnode *vp, struct acl *aclp, struct ucred *cred,
    NFSPROC_T *p)
{
	int error;

	error = nfsrv_proxyds(vp, 0, 0, cred, p, NFSPROC_SETACL,
	    NULL, NULL, NULL, NULL, aclp);
	return (error);
}