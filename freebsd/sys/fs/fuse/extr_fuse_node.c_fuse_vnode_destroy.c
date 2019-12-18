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
struct vnode {struct fuse_vnode_data* v_data; } ;
struct fuse_vnode_data {int /*<<< orphan*/  handles; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_FUSEVN ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct fuse_vnode_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_node_count ; 

void
fuse_vnode_destroy(struct vnode *vp)
{
	struct fuse_vnode_data *fvdat = vp->v_data;

	vp->v_data = NULL;
	KASSERT(LIST_EMPTY(&fvdat->handles),
		("Destroying fuse vnode with open files!"));
	free(fvdat, M_FUSEVN);

	counter_u64_add(fuse_node_count, -1);
}