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
struct thread {int dummy; } ;
struct mount {int /*<<< orphan*/ * mnt_data; } ;
struct fuse_dispatcher {int dummy; } ;
struct fuse_data {struct cdev* fdev; int /*<<< orphan*/ * mp; struct vnode* vroot; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int FORCECLOSE ; 
 int /*<<< orphan*/  FUSE_DESTROY ; 
 int /*<<< orphan*/  FUSE_LOCK () ; 
 int /*<<< orphan*/  FUSE_UNLOCK () ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  dev_rel (struct cdev*) ; 
 scalar_t__ fdata_get_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  fdata_set_dead (struct fuse_data*) ; 
 int /*<<< orphan*/  fdata_trydestroy (struct fuse_data*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct mount*,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdisp_wait_answ (struct fuse_dispatcher*) ; 
 scalar_t__ fsess_isimpl (struct mount*,int /*<<< orphan*/ ) ; 
 struct fuse_data* fuse_get_mpdata (struct mount*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,struct thread*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
fuse_vfsop_unmount(struct mount *mp, int mntflags)
{
	int err = 0;
	int flags = 0;

	struct cdev *fdev;
	struct fuse_data *data;
	struct fuse_dispatcher fdi;
	struct thread *td = curthread;

	if (mntflags & MNT_FORCE) {
		flags |= FORCECLOSE;
	}
	data = fuse_get_mpdata(mp);
	if (!data) {
		panic("no private data for mount point?");
	}
	/* There is 1 extra root vnode reference (mp->mnt_data). */
	FUSE_LOCK();
	if (data->vroot != NULL) {
		struct vnode *vroot = data->vroot;

		data->vroot = NULL;
		FUSE_UNLOCK();
		vrele(vroot);
	} else
		FUSE_UNLOCK();
	err = vflush(mp, 0, flags, td);
	if (err) {
		return err;
	}
	if (fdata_get_dead(data)) {
		goto alreadydead;
	}
	if (fsess_isimpl(mp, FUSE_DESTROY)) {
		fdisp_init(&fdi, 0);
		fdisp_make(&fdi, FUSE_DESTROY, mp, 0, td, NULL);

		(void)fdisp_wait_answ(&fdi);
		fdisp_destroy(&fdi);
	}

	fdata_set_dead(data);

alreadydead:
	FUSE_LOCK();
	data->mp = NULL;
	fdev = data->fdev;
	fdata_trydestroy(data);
	FUSE_UNLOCK();

	MNT_ILOCK(mp);
	mp->mnt_data = NULL;
	MNT_IUNLOCK(mp);

	dev_rel(fdev);

	return 0;
}