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
struct mount {int mnt_flag; int /*<<< orphan*/ * mnt_data; } ;
struct m_ext2fs {int e2fs_ronly; int e2fs_gcount; struct m_ext2fs* e2fs; struct m_ext2fs* e2fs_contigdirs; struct m_ext2fs* e2fs_gd; struct m_ext2fs* e2fs_maxcluster; struct m_ext2fs* e2fs_clustersum; struct m_ext2fs* cs_sum; int /*<<< orphan*/  um_devvp; int /*<<< orphan*/  um_cp; int /*<<< orphan*/  e2fs_state; scalar_t__ e2fs_wasvalid; struct m_ext2fs* um_e2fs; } ;
struct ext2mount {int e2fs_ronly; int e2fs_gcount; struct ext2mount* e2fs; struct ext2mount* e2fs_contigdirs; struct ext2mount* e2fs_gd; struct ext2mount* e2fs_maxcluster; struct ext2mount* e2fs_clustersum; struct ext2mount* cs_sum; int /*<<< orphan*/  um_devvp; int /*<<< orphan*/  um_cp; int /*<<< orphan*/  e2fs_state; scalar_t__ e2fs_wasvalid; struct ext2mount* um_e2fs; } ;
struct csum {int e2fs_ronly; int e2fs_gcount; struct csum* e2fs; struct csum* e2fs_contigdirs; struct csum* e2fs_gd; struct csum* e2fs_maxcluster; struct csum* e2fs_clustersum; struct csum* cs_sum; int /*<<< orphan*/  um_devvp; int /*<<< orphan*/  um_cp; int /*<<< orphan*/  e2fs_state; scalar_t__ e2fs_wasvalid; struct csum* um_e2fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2FS_ISCLEAN ; 
 int EINVAL ; 
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_LOCAL ; 
 int MNT_ROOTFS ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  M_EXT2MNT ; 
 struct m_ext2fs* VFSTOEXT2 (struct mount*) ; 
 int /*<<< orphan*/  curthread ; 
 scalar_t__ ext2_cgupdate (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int ext2_flushfiles (struct mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_sbupdate (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_vfs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_unmount(struct mount *mp, int mntflags)
{
	struct ext2mount *ump;
	struct m_ext2fs *fs;
	struct csum *sump;
	int error, flags, i, ronly;

	flags = 0;
	if (mntflags & MNT_FORCE) {
		if (mp->mnt_flag & MNT_ROOTFS)
			return (EINVAL);
		flags |= FORCECLOSE;
	}
	if ((error = ext2_flushfiles(mp, flags, curthread)) != 0)
		return (error);
	ump = VFSTOEXT2(mp);
	fs = ump->um_e2fs;
	ronly = fs->e2fs_ronly;
	if (ronly == 0 && ext2_cgupdate(ump, MNT_WAIT) == 0) {
		if (fs->e2fs_wasvalid)
			fs->e2fs->e2fs_state |= E2FS_ISCLEAN;
		ext2_sbupdate(ump, MNT_WAIT);
	}

	g_topology_lock();
	g_vfs_close(ump->um_cp);
	g_topology_unlock();
	vrele(ump->um_devvp);
	sump = fs->e2fs_clustersum;
	for (i = 0; i < fs->e2fs_gcount; i++, sump++)
		free(sump->cs_sum, M_EXT2MNT);
	free(fs->e2fs_clustersum, M_EXT2MNT);
	free(fs->e2fs_maxcluster, M_EXT2MNT);
	free(fs->e2fs_gd, M_EXT2MNT);
	free(fs->e2fs_contigdirs, M_EXT2MNT);
	free(fs->e2fs, M_EXT2MNT);
	free(fs, M_EXT2MNT);
	free(ump, M_EXT2MNT);
	mp->mnt_data = NULL;
	MNT_ILOCK(mp);
	mp->mnt_flag &= ~MNT_LOCAL;
	MNT_IUNLOCK(mp);
	return (error);
}