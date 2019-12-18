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
struct nfsnode {int /*<<< orphan*/  n_excl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_SHARED ; 
 int NFSVOPISLOCKED (struct vnode*) ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

bool
ncl_excl_start(struct vnode *vp)
{
	struct nfsnode *np;
	int vn_lk;

	ASSERT_VOP_LOCKED(vp, "ncl_excl_start");
	vn_lk = NFSVOPISLOCKED(vp);
	if (vn_lk == LK_EXCLUSIVE)
		return (false);
	KASSERT(vn_lk == LK_SHARED,
	    ("ncl_excl_start: wrong vnode lock %d", vn_lk));
	/* Ensure exclusive access, this might block */
	np = VTONFS(vp);
	lockmgr(&np->n_excl, LK_EXCLUSIVE, NULL);
	return (true);
}