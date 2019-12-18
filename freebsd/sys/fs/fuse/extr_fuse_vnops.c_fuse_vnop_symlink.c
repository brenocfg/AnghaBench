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
struct vop_symlink_args {char* a_target; struct componentname* a_cnp; struct vnode** a_vpp; struct vnode* a_dvp; } ;
struct vnode {int dummy; } ;
struct fuse_dispatcher {char* indata; } ;
struct componentname {size_t cn_namelen; char const* cn_nameptr; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FUSE_SYMLINK ; 
 int /*<<< orphan*/  VLNK ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,size_t) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fuse_internal_newentry_core (struct vnode*,struct vnode**,struct componentname*,int /*<<< orphan*/ ,struct fuse_dispatcher*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int
fuse_vnop_symlink(struct vop_symlink_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vnode **vpp = ap->a_vpp;
	struct componentname *cnp = ap->a_cnp;
	const char *target = ap->a_target;

	struct fuse_dispatcher fdi;

	int err;
	size_t len;

	if (fuse_isdeadfs(dvp)) {
		return ENXIO;
	}
	/*
	 * Unlike the other creator type calls, here we have to create a message
	 * where the name of the new entry comes first, and the data describing
	 * the entry comes second.
	 * Hence we can't rely on our handy fuse_internal_newentry() routine,
	 * but put together the message manually and just call the core part.
	 */

	len = strlen(target) + 1;
	fdisp_init(&fdi, len + cnp->cn_namelen + 1);
	fdisp_make_vp(&fdi, FUSE_SYMLINK, dvp, curthread, NULL);

	memcpy(fdi.indata, cnp->cn_nameptr, cnp->cn_namelen);
	((char *)fdi.indata)[cnp->cn_namelen] = '\0';
	memcpy((char *)fdi.indata + cnp->cn_namelen + 1, target, len);

	err = fuse_internal_newentry_core(dvp, vpp, cnp, VLNK, &fdi);
	fdisp_destroy(&fdi);
	return err;
}