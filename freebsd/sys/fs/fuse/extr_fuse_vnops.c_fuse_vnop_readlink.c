#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vop_readlink_args {struct ucred* a_cred; struct uio* a_uio; struct vnode* a_vp; } ;
struct vnode {int dummy; } ;
struct uio {int dummy; } ;
struct ucred {int dummy; } ;
struct fuse_dispatcher {char* answ; int /*<<< orphan*/  iosize; } ;
struct TYPE_7__ {int dataflags; } ;
struct TYPE_5__ {char* f_mntonname; } ;
struct TYPE_6__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int FSESS_PUSH_SYMLINKS_IN ; 
 int /*<<< orphan*/  FUSE_READLINK ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int /*<<< orphan*/ ) ; 
 int fdisp_simple_putget_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,struct ucred*) ; 
 TYPE_3__* fuse_get_mpdata (TYPE_2__*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int uiomove (char*,int /*<<< orphan*/ ,struct uio*) ; 
 int /*<<< orphan*/  vnode_islnk (struct vnode*) ; 
 TYPE_2__* vnode_mount (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_readlink(struct vop_readlink_args *ap)
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
	struct ucred *cred = ap->a_cred;

	struct fuse_dispatcher fdi;
	int err;

	if (fuse_isdeadfs(vp)) {
		return ENXIO;
	}
	if (!vnode_islnk(vp)) {
		return EINVAL;
	}
	fdisp_init(&fdi, 0);
	err = fdisp_simple_putget_vp(&fdi, FUSE_READLINK, vp, curthread, cred);
	if (err) {
		goto out;
	}
	if (((char *)fdi.answ)[0] == '/' &&
	    fuse_get_mpdata(vnode_mount(vp))->dataflags & FSESS_PUSH_SYMLINKS_IN) {
		char *mpth = vnode_mount(vp)->mnt_stat.f_mntonname;

		err = uiomove(mpth, strlen(mpth), uio);
	}
	if (!err) {
		err = uiomove(fdi.answ, fdi.iosize, uio);
	}
out:
	fdisp_destroy(&fdi);
	return err;
}