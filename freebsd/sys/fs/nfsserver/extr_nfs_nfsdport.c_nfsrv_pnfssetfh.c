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
struct vnode {int dummy; } ;
struct pnfsdsfile {int /*<<< orphan*/  dsf_fh; } ;
struct nfsnode {TYPE_1__* n_fhp; } ;
struct TYPE_2__ {int /*<<< orphan*/  nfh_fh; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  EXTATTR_NAMESPACE_SYSTEM ; 
 int /*<<< orphan*/  IO_NODELOCKED ; 
 scalar_t__ LK_EXCLUSIVE ; 
 int /*<<< orphan*/  NFSBCOPY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,int) ; 
 scalar_t__ NFSVOPISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  NFSX_MYFH ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int vn_extattr_set (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsrv_pnfssetfh(struct vnode *vp, struct pnfsdsfile *pf, char *devid,
    char *fnamep, struct vnode *nvp, NFSPROC_T *p)
{
	struct nfsnode *np;
	int ret;

	np = VTONFS(nvp);
	NFSBCOPY(np->n_fhp->nfh_fh, &pf->dsf_fh, NFSX_MYFH);
	/*
	 * We can only do a vn_set_extattr() if the vnode is exclusively
	 * locked and vn_start_write() has been done.  If devid != NULL or
	 * fnamep != NULL or the vnode is shared locked, vn_start_write()
	 * may not have been done.
	 * If not done now, it will be done on a future call.
	 */
	if (devid == NULL && fnamep == NULL && NFSVOPISLOCKED(vp) ==
	    LK_EXCLUSIVE)
		ret = vn_extattr_set(vp, IO_NODELOCKED,
		    EXTATTR_NAMESPACE_SYSTEM, "pnfsd.dsfile", sizeof(*pf),
		    (char *)pf, p);
	NFSD_DEBUG(4, "eo nfsrv_pnfssetfh=%d\n", ret);
}