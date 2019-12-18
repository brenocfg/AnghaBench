#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; struct cdev* v_rdev; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct cdev {TYPE_1__* si_devsw; } ;
struct TYPE_2__ {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct thread*) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 scalar_t__ VCHR ; 
 int VOP_ACCESS (struct vnode*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int VREAD ; 
 int VWRITE ; 
 int /*<<< orphan*/  dev_ref (struct cdev*) ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 scalar_t__ fuse_enforce_dev_perms ; 
 int mac_check_vnode_open (int /*<<< orphan*/ ,struct vnode*,int) ; 
 int namei (struct nameidata*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
fuse_getdevice(const char *fspec, struct thread *td, struct cdev **fdevp)
{
	struct nameidata nd, *ndp = &nd;
	struct vnode *devvp;
	struct cdev *fdev;
	int err;

	/*
	 * Not an update, or updating the name: look up the name
	 * and verify that it refers to a sensible disk device.
	 */

	NDINIT(ndp, LOOKUP, FOLLOW, UIO_SYSSPACE, fspec, td);
	if ((err = namei(ndp)) != 0)
		return err;
	NDFREE(ndp, NDF_ONLY_PNBUF);
	devvp = ndp->ni_vp;

	if (devvp->v_type != VCHR) {
		vrele(devvp);
		return ENXIO;
	}
	fdev = devvp->v_rdev;
	dev_ref(fdev);

	if (fuse_enforce_dev_perms) {
		/*
	         * Check if mounter can open the fuse device.
	         *
	         * This has significance only if we are doing a secondary mount
	         * which doesn't involve actually opening fuse devices, but we
	         * still want to enforce the permissions of the device (in
	         * order to keep control over the circle of fuse users).
	         *
	         * (In case of primary mounts, we are either the superuser so
	         * we can do anything anyway, or we can mount only if the
	         * device is already opened by us, ie. we are permitted to open
	         * the device.)
	         */
#if 0
#ifdef MAC
		err = mac_check_vnode_open(td->td_ucred, devvp, VREAD | VWRITE);
		if (!err)
#endif
#endif /* 0 */
			err = VOP_ACCESS(devvp, VREAD | VWRITE, td->td_ucred, td);
		if (err) {
			vrele(devvp);
			dev_rel(fdev);
			return err;
		}
	}
	/*
	 * according to coda code, no extra lock is needed --
	 * although in sys/vnode.h this field is marked "v"
	 */
	vrele(devvp);

	if (!fdev->si_devsw ||
	    strcmp("fuse", fdev->si_devsw->d_name)) {
		dev_rel(fdev);
		return ENXIO;
	}
	*fdevp = fdev;

	return 0;
}