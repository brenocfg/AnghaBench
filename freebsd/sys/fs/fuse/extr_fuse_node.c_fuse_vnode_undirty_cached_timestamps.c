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
struct fuse_vnode_data {int flag; } ;

/* Variables and functions */
 int FN_CTIMECHANGE ; 
 int FN_MTIMECHANGE ; 
 struct fuse_vnode_data* VTOFUD (struct vnode*) ; 

void
fuse_vnode_undirty_cached_timestamps(struct vnode *vp)
{
	struct fuse_vnode_data *fvdat = VTOFUD(vp);

	fvdat->flag &= ~(FN_MTIMECHANGE | FN_CTIMECHANGE);
}