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
struct nameidata {int /*<<< orphan*/ * ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  enum symfollow { ____Placeholder_symfollow } symfollow ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int LK_RETRY ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATVP (struct nameidata*,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vn_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vref (int /*<<< orphan*/ *) ; 

int
lookupnameat(char *dirname, enum uio_seg seg, enum symfollow follow,
    vnode_t **dirvpp, vnode_t **compvpp, vnode_t *startvp)
{
	struct nameidata nd;
	int error, ltype;

	ASSERT(dirvpp == NULL);

	vref(startvp);
	ltype = VOP_ISLOCKED(startvp);
	VOP_UNLOCK(startvp, 0);
	NDINIT_ATVP(&nd, LOOKUP, LOCKLEAF | follow, seg, dirname,
	    startvp, curthread);
	error = namei(&nd);
	*compvpp = nd.ni_vp;
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vn_lock(startvp, ltype | LK_RETRY);
	return (error);
}