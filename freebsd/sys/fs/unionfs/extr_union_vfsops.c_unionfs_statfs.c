#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct unionfs_mount {TYPE_2__* um_uppervp; TYPE_1__* um_lowervp; } ;
struct statfs {int f_blocks; int f_bsize; int /*<<< orphan*/  f_ffree; scalar_t__ f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_iosize; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_type; } ;
struct mount {int dummy; } ;
typedef  int off_t ;
struct TYPE_4__ {int /*<<< orphan*/  v_mount; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 struct unionfs_mount* MOUNTTOUNIONFSMOUNT (struct mount*) ; 
 int /*<<< orphan*/  M_STATFS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UNIONFSDEBUG (char*,void*,void*,void*) ; 
 int VFS_STATFS (int /*<<< orphan*/ ,struct statfs*) ; 
 int /*<<< orphan*/  free (struct statfs*,int /*<<< orphan*/ ) ; 
 struct statfs* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unionfs_statfs(struct mount *mp, struct statfs *sbp)
{
	struct unionfs_mount *ump;
	int		error;
	struct statfs	*mstat;
	uint64_t	lbsize;

	ump = MOUNTTOUNIONFSMOUNT(mp);

	UNIONFSDEBUG("unionfs_statfs(mp = %p, lvp = %p, uvp = %p)\n",
	    (void *)mp, (void *)ump->um_lowervp, (void *)ump->um_uppervp);

	mstat = malloc(sizeof(struct statfs), M_STATFS, M_WAITOK | M_ZERO);

	error = VFS_STATFS(ump->um_lowervp->v_mount, mstat);
	if (error) {
		free(mstat, M_STATFS);
		return (error);
	}

	/* now copy across the "interesting" information and fake the rest */
	sbp->f_blocks = mstat->f_blocks;
	sbp->f_files = mstat->f_files;

	lbsize = mstat->f_bsize;

	error = VFS_STATFS(ump->um_uppervp->v_mount, mstat);
	if (error) {
		free(mstat, M_STATFS);
		return (error);
	}


	/*
	 * The FS type etc is copy from upper vfs.
	 * (write able vfs have priority)
	 */
	sbp->f_type = mstat->f_type;
	sbp->f_flags = mstat->f_flags;
	sbp->f_bsize = mstat->f_bsize;
	sbp->f_iosize = mstat->f_iosize;

	if (mstat->f_bsize != lbsize)
		sbp->f_blocks = ((off_t)sbp->f_blocks * lbsize) /
		    mstat->f_bsize;

	sbp->f_blocks += mstat->f_blocks;
	sbp->f_bfree = mstat->f_bfree;
	sbp->f_bavail = mstat->f_bavail;
	sbp->f_files += mstat->f_files;
	sbp->f_ffree = mstat->f_ffree;

	free(mstat, M_STATFS);
	return (0);
}