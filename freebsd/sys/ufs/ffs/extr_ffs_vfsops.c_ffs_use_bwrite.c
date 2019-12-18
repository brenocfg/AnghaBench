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
typedef  int /*<<< orphan*/  u_int ;
struct ufsmount {int /*<<< orphan*/  um_mountp; int /*<<< orphan*/  um_devvp; struct fs* um_fs; } ;
struct fs {scalar_t__ fs_sblockloc; scalar_t__ fs_magic; int fs_old_flags; char* fs_fsmnt; int /*<<< orphan*/  fs_ckhash; scalar_t__ fs_sbsize; } ;
struct devfd {scalar_t__ waitfor; int error; scalar_t__ suspended; struct buf* sbbp; struct ufsmount* ump; } ;
struct buf {int /*<<< orphan*/  b_flags; scalar_t__ b_data; } ;
typedef  scalar_t__ off_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_VALIDSUSPWRT ; 
 int FS_FLAGS_UPDATED ; 
 scalar_t__ FS_UFS1_MAGIC ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 scalar_t__ MNT_WAIT ; 
 scalar_t__ MOUNTEDSOFTDEP (int /*<<< orphan*/ ) ; 
 scalar_t__ SBLOCK_UFS1 ; 
 scalar_t__ SBLOCK_UFS2 ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 int /*<<< orphan*/  bcopy (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  btodb (scalar_t__) ; 
 int bwrite (struct buf*) ; 
 int /*<<< orphan*/  ffs_calc_sbhash (struct fs*) ; 
 int /*<<< orphan*/  ffs_oldfscompat_write (struct fs*,struct ufsmount*) ; 
 struct buf* getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  softdep_setup_sbupdate (struct ufsmount*,struct fs*,struct buf*) ; 

__attribute__((used)) static int
ffs_use_bwrite(void *devfd, off_t loc, void *buf, int size)
{
	struct devfd *devfdp;
	struct ufsmount *ump;
	struct buf *bp;
	struct fs *fs;
	int error;

	devfdp = devfd;
	ump = devfdp->ump;
	fs = ump->um_fs;
	/*
	 * Writing the superblock summary information.
	 */
	if (loc != fs->fs_sblockloc) {
		bp = getblk(ump->um_devvp, btodb(loc), size, 0, 0, 0);
		bcopy(buf, bp->b_data, (u_int)size);
		if (devfdp->suspended)
			bp->b_flags |= B_VALIDSUSPWRT;
		if (devfdp->waitfor != MNT_WAIT)
			bawrite(bp);
		else if ((error = bwrite(bp)) != 0)
			devfdp->error = error;
		return (0);
	}
	/*
	 * Writing the superblock itself. We need to do special checks for it.
	 */
	bp = devfdp->sbbp;
	if (devfdp->error != 0) {
		brelse(bp);
		return (devfdp->error);
	}
	if (fs->fs_magic == FS_UFS1_MAGIC && fs->fs_sblockloc != SBLOCK_UFS1 &&
	    (fs->fs_old_flags & FS_FLAGS_UPDATED) == 0) {
		printf("WARNING: %s: correcting fs_sblockloc from %jd to %d\n",
		    fs->fs_fsmnt, fs->fs_sblockloc, SBLOCK_UFS1);
		fs->fs_sblockloc = SBLOCK_UFS1;
	}
	if (fs->fs_magic == FS_UFS2_MAGIC && fs->fs_sblockloc != SBLOCK_UFS2 &&
	    (fs->fs_old_flags & FS_FLAGS_UPDATED) == 0) {
		printf("WARNING: %s: correcting fs_sblockloc from %jd to %d\n",
		    fs->fs_fsmnt, fs->fs_sblockloc, SBLOCK_UFS2);
		fs->fs_sblockloc = SBLOCK_UFS2;
	}
	if (MOUNTEDSOFTDEP(ump->um_mountp))
		softdep_setup_sbupdate(ump, (struct fs *)bp->b_data, bp);
	bcopy((caddr_t)fs, bp->b_data, (u_int)fs->fs_sbsize);
	fs = (struct fs *)bp->b_data;
	ffs_oldfscompat_write(fs, ump);
	/*
	 * Because we may have made changes to the superblock, we need to
	 * recompute its check-hash.
	 */
	fs->fs_ckhash = ffs_calc_sbhash(fs);
	if (devfdp->suspended)
		bp->b_flags |= B_VALIDSUSPWRT;
	if (devfdp->waitfor != MNT_WAIT)
		bawrite(bp);
	else if ((error = bwrite(bp)) != 0)
		devfdp->error = error;
	return (devfdp->error);
}