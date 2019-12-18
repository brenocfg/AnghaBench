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
typedef  scalar_t__ uint64_t ;
struct vnode {int v_type; struct fuse_vnode_data* v_data; int /*<<< orphan*/  v_vflag; } ;
struct fuse_vnode_data {int /*<<< orphan*/  cached_attrs; int /*<<< orphan*/  handles; scalar_t__ nid; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 scalar_t__ FUSE_ROOT_ID ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_node_count ; 
 int /*<<< orphan*/  vattr_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fuse_vnode_init(struct vnode *vp, struct fuse_vnode_data *fvdat,
    uint64_t nodeid, enum vtype vtyp)
{
	fvdat->nid = nodeid;
	LIST_INIT(&fvdat->handles);
	vattr_null(&fvdat->cached_attrs);
	if (nodeid == FUSE_ROOT_ID) {
		vp->v_vflag |= VV_ROOT;
	}
	vp->v_type = vtyp;
	vp->v_data = fvdat;

	counter_u64_add(fuse_node_count, 1);
}