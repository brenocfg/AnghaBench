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
struct mount {int dummy; } ;
struct fuse_entry_out {int /*<<< orphan*/  attr_valid_nsec; int /*<<< orphan*/  attr_valid; int /*<<< orphan*/  attr; int /*<<< orphan*/  nodeid; } ;
struct fuse_dispatcher {struct fuse_entry_out* answ; } ;
struct componentname {int /*<<< orphan*/  cn_cred; int /*<<< orphan*/  cn_thread; } ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fuse_internal_cache_attrs (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fuse_internal_checkentry (struct fuse_entry_out*,int) ; 
 int /*<<< orphan*/  fuse_internal_forget_send (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_vnode_clear_attr_cache (struct vnode*) ; 
 int fuse_vnode_get (struct mount*,struct fuse_entry_out*,int /*<<< orphan*/ ,struct vnode*,struct vnode**,struct componentname*,int) ; 
 struct mount* vnode_mount (struct vnode*) ; 

int
fuse_internal_newentry_core(struct vnode *dvp,
    struct vnode **vpp,
    struct componentname *cnp,
    enum vtype vtyp,
    struct fuse_dispatcher *fdip)
{
	int err = 0;
	struct fuse_entry_out *feo;
	struct mount *mp = vnode_mount(dvp);

	if ((err = fdisp_wait_answ(fdip))) {
		return err;
	}
	feo = fdip->answ;

	if ((err = fuse_internal_checkentry(feo, vtyp))) {
		return err;
	}
	err = fuse_vnode_get(mp, feo, feo->nodeid, dvp, vpp, cnp, vtyp);
	if (err) {
		fuse_internal_forget_send(mp, cnp->cn_thread, cnp->cn_cred,
		    feo->nodeid, 1);
		return err;
	}

	/* 
	 * Purge the parent's attribute cache because the daemon should've
	 * updated its mtime and ctime
	 */
	fuse_vnode_clear_attr_cache(dvp);

	fuse_internal_cache_attrs(*vpp, &feo->attr, feo->attr_valid,
		feo->attr_valid_nsec, NULL);

	return err;
}