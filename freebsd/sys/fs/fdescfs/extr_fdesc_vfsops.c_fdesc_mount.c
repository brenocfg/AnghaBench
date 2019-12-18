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
struct vnode {int /*<<< orphan*/  v_vflag; int /*<<< orphan*/  v_type; } ;
struct mount {int mnt_flag; struct fdescmount* mnt_data; int /*<<< orphan*/  mnt_optnew; } ;
struct fdescmount {struct vnode* f_root; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FD_ROOT ; 
 int /*<<< orphan*/  FMNT_LINRDLNKF ; 
 int /*<<< orphan*/  Froot ; 
 int MNT_ROOTFS ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  M_FDESCMNT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 int fdesc_allocvp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mount*,struct vnode**) ; 
 int /*<<< orphan*/  free (struct fdescmount*,int /*<<< orphan*/ ) ; 
 struct fdescmount* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getnewfsid (struct mount*) ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 

__attribute__((used)) static int
fdesc_mount(struct mount *mp)
{
	struct fdescmount *fmp;
	struct vnode *rvp;
	int error;

	/*
	 * Update is a no-op
	 */
	if (mp->mnt_flag & (MNT_UPDATE | MNT_ROOTFS))
		return (EOPNOTSUPP);

	fmp = malloc(sizeof(struct fdescmount),
				M_FDESCMNT, M_WAITOK);	/* XXX */

	/*
	 * We need to initialize a few bits of our local mount point struct to
	 * avoid confusion in allocvp.
	 */
	mp->mnt_data = fmp;
	fmp->flags = 0;
	if (vfs_getopt(mp->mnt_optnew, "linrdlnk", NULL, NULL) == 0)
		fmp->flags |= FMNT_LINRDLNKF;
	error = fdesc_allocvp(Froot, -1, FD_ROOT, mp, &rvp);
	if (error) {
		free(fmp, M_FDESCMNT);
		mp->mnt_data = NULL;
		return (error);
	}
	rvp->v_type = VDIR;
	rvp->v_vflag |= VV_ROOT;
	fmp->f_root = rvp;
	VOP_UNLOCK(rvp, 0);
	/* XXX -- don't mark as local to work around fts() problems */
	/*mp->mnt_flag |= MNT_LOCAL;*/
	vfs_getnewfsid(mp);

	vfs_mountedfrom(mp, "fdescfs");
	return (0);
}