#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct pnfsdsfile {int /*<<< orphan*/  dsf_filename; } ;
struct TYPE_2__ {int cn_lkflags; int cn_flags; char* cn_nameptr; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/ * cn_thread; struct ucred* cn_cred; int /*<<< orphan*/  cn_nameiop; } ;
struct nameidata {TYPE_1__ ni_cnd; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int ISLASTCN ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  NFSFREECRED (struct ucred*) ; 
 int SAVENAME ; 
 int VOP_LOOKUP (struct vnode*,struct vnode**,TYPE_1__*) ; 
 struct ucred* newnfs_getcred () ; 
 int /*<<< orphan*/  nfsvno_relpathbuf (struct nameidata*) ; 
 int /*<<< orphan*/  nfsvno_setpathbuf (struct nameidata*,char**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsrv_pnfslookupds(struct vnode *vp, struct vnode *dvp, struct pnfsdsfile *pf,
    struct vnode **nvpp, NFSPROC_T *p)
{
	struct nameidata named;
	struct ucred *tcred;
	char *bufp;
	u_long *hashp;
	struct vnode *nvp;
	int error;

	tcred = newnfs_getcred();
	named.ni_cnd.cn_nameiop = LOOKUP;
	named.ni_cnd.cn_lkflags = LK_SHARED | LK_RETRY;
	named.ni_cnd.cn_cred = tcred;
	named.ni_cnd.cn_thread = p;
	named.ni_cnd.cn_flags = ISLASTCN | LOCKPARENT | LOCKLEAF | SAVENAME;
	nfsvno_setpathbuf(&named, &bufp, &hashp);
	named.ni_cnd.cn_nameptr = bufp;
	named.ni_cnd.cn_namelen = strlen(pf->dsf_filename);
	strlcpy(bufp, pf->dsf_filename, NAME_MAX);
	NFSD_DEBUG(4, "nfsrv_pnfslookupds: filename=%s\n", bufp);
	error = VOP_LOOKUP(dvp, &nvp, &named.ni_cnd);
	NFSD_DEBUG(4, "nfsrv_pnfslookupds: aft LOOKUP=%d\n", error);
	NFSFREECRED(tcred);
	nfsvno_relpathbuf(&named);
	if (error == 0)
		*nvpp = nvp;
	NFSD_DEBUG(4, "eo nfsrv_pnfslookupds=%d\n", error);
	return (error);
}