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
struct fuse_vnode_data {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  FN_REVOKED ; 
 struct fuse_vnode_data* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 

void
fuse_internal_vnode_disappear(struct vnode *vp)
{
	struct fuse_vnode_data *fvdat = VTOFUD(vp);

	ASSERT_VOP_ELOCKED(vp, "fuse_internal_vnode_disappear");
	fvdat->flag |= FN_REVOKED;
	cache_purge(vp);
}