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
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct TYPE_3__ {int cn_lkflags; int cn_flags; char* cn_nameptr; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/ * cn_thread; struct ucred* cn_cred; int /*<<< orphan*/  cn_nameiop; } ;
struct nameidata {TYPE_1__ ni_cnd; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 int ISLASTCN ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int NFSVOPLOCK (struct vnode*,int) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int SAVENAME ; 
 int VOP_LOOKUP (struct vnode*,struct vnode**,TYPE_1__*) ; 
 int VOP_REMOVE (struct vnode*,struct vnode*,TYPE_1__*) ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int /*<<< orphan*/  nfsvno_setpathbuf (struct nameidata*,char**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
nfsrv_dsremove(struct vnode *dvp, char *fname, struct ucred *tcred,
    NFSPROC_T *p)
{
	struct nameidata named;
	struct vnode *nvp;
	char *bufp;
	u_long *hashp;
	int error;

	error = NFSVOPLOCK(dvp, LK_EXCLUSIVE);
	if (error != 0)
		return (error);
	named.ni_cnd.cn_nameiop = DELETE;
	named.ni_cnd.cn_lkflags = LK_EXCLUSIVE | LK_RETRY;
	named.ni_cnd.cn_cred = tcred;
	named.ni_cnd.cn_thread = p;
	named.ni_cnd.cn_flags = ISLASTCN | LOCKPARENT | LOCKLEAF | SAVENAME;
	nfsvno_setpathbuf(&named, &bufp, &hashp);
	named.ni_cnd.cn_nameptr = bufp;
	named.ni_cnd.cn_namelen = strlen(fname);
	strlcpy(bufp, fname, NAME_MAX);
	NFSD_DEBUG(4, "nfsrv_pnfsremove: filename=%s\n", bufp);
	error = VOP_LOOKUP(dvp, &nvp, &named.ni_cnd);
	NFSD_DEBUG(4, "nfsrv_pnfsremove: aft LOOKUP=%d\n", error);
	if (error == 0) {
		error = VOP_REMOVE(dvp, nvp, &named.ni_cnd);
		vput(nvp);
	}
	NFSVOPUNLOCK(dvp, 0);
	nfsvno_relpathbuf(&named);
	if (error != 0)
		printf("pNFS: nfsrv_pnfsremove failed=%d\n", error);
	return (error);
}