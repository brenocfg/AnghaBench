#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct bufobj {int /*<<< orphan*/  bo_ops; struct g_consumer* bo_private; } ;
struct vnode {struct bufobj v_bufobj; struct cdev* v_rdev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * val; } ;
struct TYPE_6__ {TYPE_1__ f_fsid; } ;
struct mount {int mnt_iosize_max; int mnt_flag; int mnt_kern_flag; struct m_ext2fs* mnt_data; int /*<<< orphan*/  mnt_maxsymlinklen; TYPE_3__* mnt_vfc; TYPE_2__ mnt_stat; int /*<<< orphan*/  mnt_optnew; } ;
struct m_ext2fs {int e2fs_bsize; int e2fs_contigsumsize; int e2fs_gcount; int e2fs_ronly; int e2fs_wasvalid; int e2fs_state; int e2fs_fmod; struct m_ext2fs* um_e2fs; struct m_ext2fs* e2fs; struct m_ext2fs* e2fs_contigdirs; struct m_ext2fs* e2fs_gd; int /*<<< orphan*/  um_seqinc; scalar_t__ e2fs_log_bsize; scalar_t__ um_bptrtodb; int /*<<< orphan*/  um_nindir; struct g_consumer* um_cp; struct bufobj* um_bo; struct vnode* um_devvp; struct cdev* um_dev; struct mount* um_mountp; struct csum* e2fs_clustersum; int /*<<< orphan*/ * e2fs_maxcluster; } ;
struct g_consumer {TYPE_4__* provider; } ;
struct ext2mount {int e2fs_bsize; int e2fs_contigsumsize; int e2fs_gcount; int e2fs_ronly; int e2fs_wasvalid; int e2fs_state; int e2fs_fmod; struct ext2mount* um_e2fs; struct ext2mount* e2fs; struct ext2mount* e2fs_contigdirs; struct ext2mount* e2fs_gd; int /*<<< orphan*/  um_seqinc; scalar_t__ e2fs_log_bsize; scalar_t__ um_bptrtodb; int /*<<< orphan*/  um_nindir; struct g_consumer* um_cp; struct bufobj* um_bo; struct vnode* um_devvp; struct cdev* um_dev; struct mount* um_mountp; struct csum* e2fs_clustersum; int /*<<< orphan*/ * e2fs_maxcluster; } ;
struct ext2fs {int e2fs_state; } ;
struct csum {void* cs_sum; scalar_t__ cs_init; } ;
struct cdev {scalar_t__ si_iosize_max; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int sectorsize; } ;
struct TYPE_7__ {int /*<<< orphan*/  vfc_typenum; } ;

/* Variables and functions */
 int E2FS_ERRORS ; 
 int E2FS_ISCLEAN ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT2_ADDR_PER_BLOCK (struct m_ext2fs*) ; 
 int /*<<< orphan*/  EXT2_FRAGS_PER_BLOCK (struct m_ext2fs*) ; 
 int /*<<< orphan*/  EXT2_MAXCONTIG ; 
 int /*<<< orphan*/  EXT2_MAXSYMLINKLEN ; 
 int /*<<< orphan*/  EXT2_MTX (struct m_ext2fs*) ; 
 int /*<<< orphan*/  MAX (int,int) ; 
 int MAXPHYS ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MNTK_EXTENDED_SHARED ; 
 int MNTK_LOOKUP_SHARED ; 
 int MNTK_USES_BCACHE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_LOCAL ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_EXT2MNT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  SBLOCK ; 
 int SBSIZE ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct ext2fs*,struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int bread (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 scalar_t__ ext2_check_sb_compat (struct ext2fs*,struct cdev*,int) ; 
 int ext2_compute_sb_data (struct vnode*,struct m_ext2fs*,struct m_ext2fs*) ; 
 int /*<<< orphan*/  ext2_sbupdate (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_vfs_bufops ; 
 int /*<<< orphan*/  g_vfs_close (struct g_consumer*) ; 
 int g_vfs_open (struct vnode*,struct g_consumer**,char*,int) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int vfs_flagopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_mountfs(struct vnode *devvp, struct mount *mp)
{
	struct ext2mount *ump;
	struct buf *bp;
	struct m_ext2fs *fs;
	struct ext2fs *es;
	struct cdev *dev = devvp->v_rdev;
	struct g_consumer *cp;
	struct bufobj *bo;
	struct csum *sump;
	int error;
	int ronly;
	int i;
	u_long size;
	int32_t *lp;
	int32_t e2fs_maxcontig;

	ronly = vfs_flagopt(mp->mnt_optnew, "ro", NULL, 0);
	/* XXX: use VOP_ACESS to check FS perms */
	g_topology_lock();
	error = g_vfs_open(devvp, &cp, "ext2fs", ronly ? 0 : 1);
	g_topology_unlock();
	VOP_UNLOCK(devvp, 0);
	if (error)
		return (error);

	/* XXX: should we check for some sectorsize or 512 instead? */
	if (((SBSIZE % cp->provider->sectorsize) != 0) ||
	    (SBSIZE < cp->provider->sectorsize)) {
		g_topology_lock();
		g_vfs_close(cp);
		g_topology_unlock();
		return (EINVAL);
	}

	bo = &devvp->v_bufobj;
	bo->bo_private = cp;
	bo->bo_ops = g_vfs_bufops;
	if (devvp->v_rdev->si_iosize_max != 0)
		mp->mnt_iosize_max = devvp->v_rdev->si_iosize_max;
	if (mp->mnt_iosize_max > MAXPHYS)
		mp->mnt_iosize_max = MAXPHYS;

	bp = NULL;
	ump = NULL;
	if ((error = bread(devvp, SBLOCK, SBSIZE, NOCRED, &bp)) != 0)
		goto out;
	es = (struct ext2fs *)bp->b_data;
	if (ext2_check_sb_compat(es, dev, ronly) != 0) {
		error = EINVAL;		/* XXX needs translation */
		goto out;
	}
	if ((es->e2fs_state & E2FS_ISCLEAN) == 0 ||
	    (es->e2fs_state & E2FS_ERRORS)) {
		if (ronly || (mp->mnt_flag & MNT_FORCE)) {
			printf(
"WARNING: Filesystem was not properly dismounted\n");
		} else {
			printf(
"WARNING: R/W mount denied.  Filesystem is not clean - run fsck\n");
			error = EPERM;
			goto out;
		}
	}
	ump = malloc(sizeof(*ump), M_EXT2MNT, M_WAITOK | M_ZERO);

	/*
	 * I don't know whether this is the right strategy. Note that
	 * we dynamically allocate both an m_ext2fs and an ext2fs
	 * while Linux keeps the super block in a locked buffer.
	 */
	ump->um_e2fs = malloc(sizeof(struct m_ext2fs),
	    M_EXT2MNT, M_WAITOK | M_ZERO);
	ump->um_e2fs->e2fs = malloc(sizeof(struct ext2fs),
	    M_EXT2MNT, M_WAITOK);
	mtx_init(EXT2_MTX(ump), "EXT2FS", "EXT2FS Lock", MTX_DEF);
	bcopy(es, ump->um_e2fs->e2fs, (u_int)sizeof(struct ext2fs));
	if ((error = ext2_compute_sb_data(devvp, ump->um_e2fs->e2fs, ump->um_e2fs)))
		goto out;

	/*
	 * Calculate the maximum contiguous blocks and size of cluster summary
	 * array.  In FFS this is done by newfs; however, the superblock
	 * in ext2fs doesn't have these variables, so we can calculate
	 * them here.
	 */
	e2fs_maxcontig = MAX(1, MAXPHYS / ump->um_e2fs->e2fs_bsize);
	ump->um_e2fs->e2fs_contigsumsize = MIN(e2fs_maxcontig, EXT2_MAXCONTIG);
	if (ump->um_e2fs->e2fs_contigsumsize > 0) {
		size = ump->um_e2fs->e2fs_gcount * sizeof(int32_t);
		ump->um_e2fs->e2fs_maxcluster = malloc(size, M_EXT2MNT, M_WAITOK);
		size = ump->um_e2fs->e2fs_gcount * sizeof(struct csum);
		ump->um_e2fs->e2fs_clustersum = malloc(size, M_EXT2MNT, M_WAITOK);
		lp = ump->um_e2fs->e2fs_maxcluster;
		sump = ump->um_e2fs->e2fs_clustersum;
		for (i = 0; i < ump->um_e2fs->e2fs_gcount; i++, sump++) {
			*lp++ = ump->um_e2fs->e2fs_contigsumsize;
			sump->cs_init = 0;
			sump->cs_sum = malloc((ump->um_e2fs->e2fs_contigsumsize + 1) *
			    sizeof(int32_t), M_EXT2MNT, M_WAITOK | M_ZERO);
		}
	}

	brelse(bp);
	bp = NULL;
	fs = ump->um_e2fs;
	fs->e2fs_ronly = ronly;	/* ronly is set according to mnt_flags */

	/*
	 * If the fs is not mounted read-only, make sure the super block is
	 * always written back on a sync().
	 */
	fs->e2fs_wasvalid = fs->e2fs->e2fs_state & E2FS_ISCLEAN ? 1 : 0;
	if (ronly == 0) {
		fs->e2fs_fmod = 1;	/* mark it modified */
		fs->e2fs->e2fs_state &= ~E2FS_ISCLEAN;	/* set fs invalid */
	}
	mp->mnt_data = ump;
	mp->mnt_stat.f_fsid.val[0] = dev2udev(dev);
	mp->mnt_stat.f_fsid.val[1] = mp->mnt_vfc->vfc_typenum;
	mp->mnt_maxsymlinklen = EXT2_MAXSYMLINKLEN;
	MNT_ILOCK(mp);
	mp->mnt_flag |= MNT_LOCAL;
	MNT_IUNLOCK(mp);
	ump->um_mountp = mp;
	ump->um_dev = dev;
	ump->um_devvp = devvp;
	ump->um_bo = &devvp->v_bufobj;
	ump->um_cp = cp;

	/*
	 * Setting those two parameters allowed us to use
	 * ufs_bmap w/o changse!
	 */
	ump->um_nindir = EXT2_ADDR_PER_BLOCK(fs);
	ump->um_bptrtodb = fs->e2fs->e2fs_log_bsize + 1;
	ump->um_seqinc = EXT2_FRAGS_PER_BLOCK(fs);
	if (ronly == 0)
		ext2_sbupdate(ump, MNT_WAIT);
	/*
	 * Initialize filesystem stat information in mount struct.
	 */
	MNT_ILOCK(mp);
	mp->mnt_kern_flag |= MNTK_LOOKUP_SHARED | MNTK_EXTENDED_SHARED |
	    MNTK_USES_BCACHE;
	MNT_IUNLOCK(mp);
	return (0);
out:
	if (bp)
		brelse(bp);
	if (cp != NULL) {
		g_topology_lock();
		g_vfs_close(cp);
		g_topology_unlock();
	}
	if (ump) {
		mtx_destroy(EXT2_MTX(ump));
		free(ump->um_e2fs->e2fs_gd, M_EXT2MNT);
		free(ump->um_e2fs->e2fs_contigdirs, M_EXT2MNT);
		free(ump->um_e2fs->e2fs, M_EXT2MNT);
		free(ump->um_e2fs, M_EXT2MNT);
		free(ump, M_EXT2MNT);
		mp->mnt_data = NULL;
	}
	return (error);
}