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
struct vop_link_args {struct componentname* a_cnp; struct vnode* a_tdvp; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct vattr {scalar_t__ va_nlink; } ;
struct fuse_link_in {int /*<<< orphan*/  oldnodeid; } ;
struct fuse_entry_out {int /*<<< orphan*/  attr_valid_nsec; int /*<<< orphan*/  attr_valid; int /*<<< orphan*/  attr; } ;
struct fuse_dispatcher {struct fuse_entry_out* answ; } ;
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  fli ;

/* Variables and functions */
 int EMLINK ; 
 int ENXIO ; 
 int EXDEV ; 
 int /*<<< orphan*/  FUSE_LINK ; 
 scalar_t__ FUSE_LINK_MAX ; 
 int /*<<< orphan*/  VTOI (struct vnode*) ; 
 struct vattr* VTOVA (struct vnode*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int /*<<< orphan*/ ) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fuse_internal_cache_attrs (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fuse_internal_checkentry (struct fuse_entry_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_internal_newentry_makerequest (scalar_t__,int /*<<< orphan*/ ,struct componentname*,int /*<<< orphan*/ ,struct fuse_link_in*,int,struct fuse_dispatcher*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int /*<<< orphan*/  fuse_vnode_clear_attr_cache (struct vnode*) ; 
 scalar_t__ vnode_mount (struct vnode*) ; 
 int /*<<< orphan*/  vnode_vtype (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_link(struct vop_link_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct vnode *tdvp = ap->a_tdvp;
	struct componentname *cnp = ap->a_cnp;

	struct vattr *vap = VTOVA(vp);

	struct fuse_dispatcher fdi;
	struct fuse_entry_out *feo;
	struct fuse_link_in fli;

	int err;

	if (fuse_isdeadfs(vp)) {
		return ENXIO;
	}
	if (vnode_mount(tdvp) != vnode_mount(vp)) {
		return EXDEV;
	}

	/*
	 * This is a seatbelt check to protect naive userspace filesystems from
	 * themselves and the limitations of the FUSE IPC protocol.  If a
	 * filesystem does not allow attribute caching, assume it is capable of
	 * validating that nlink does not overflow.
	 */
	if (vap != NULL && vap->va_nlink >= FUSE_LINK_MAX)
		return EMLINK;
	fli.oldnodeid = VTOI(vp);

	fdisp_init(&fdi, 0);
	fuse_internal_newentry_makerequest(vnode_mount(tdvp), VTOI(tdvp), cnp,
	    FUSE_LINK, &fli, sizeof(fli), &fdi);
	if ((err = fdisp_wait_answ(&fdi))) {
		goto out;
	}
	feo = fdi.answ;

	err = fuse_internal_checkentry(feo, vnode_vtype(vp));
	if (!err) {
		/* 
		 * Purge the parent's attribute cache because the daemon
		 * should've updated its mtime and ctime
		 */
		fuse_vnode_clear_attr_cache(tdvp);
		fuse_internal_cache_attrs(vp, &feo->attr, feo->attr_valid,
			feo->attr_valid_nsec, NULL);
	}
out:
	fdisp_destroy(&fdi);
	return err;
}