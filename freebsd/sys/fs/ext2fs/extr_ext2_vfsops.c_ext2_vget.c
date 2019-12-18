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
struct vnode {int /*<<< orphan*/  v_vnlock; struct inode* v_data; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct m_ext2fs {scalar_t__ e2fs_bsize; } ;
struct inode {int i_flag; scalar_t__* i_db; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; scalar_t__ i_next_alloc_goal; scalar_t__ i_next_alloc_block; int /*<<< orphan*/  i_block_group; int /*<<< orphan*/  i_number; struct ext2mount* i_ump; struct m_ext2fs* i_e2fs; struct vnode* i_vnode; } ;
struct ext2mount {int /*<<< orphan*/  um_devvp; struct m_ext2fs* um_e2fs; } ;
struct ext2fs_dinode {int dummy; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 unsigned int EXT2_NDIR_BLOCKS ; 
 int IN_E4EXTENTS ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  M_EXT2NODE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NOCRED ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct ext2mount* VFSTOEXT2 (struct mount*) ; 
 int /*<<< orphan*/  bqrelse (struct buf*) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 struct thread* curthread ; 
 int ext2_ei2i (struct ext2fs_dinode*,struct inode*) ; 
 int /*<<< orphan*/  ext2_fifoops ; 
 int /*<<< orphan*/  ext2_print_inode (struct inode*) ; 
 int ext2_vinit (struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 int /*<<< orphan*/  ext2_vnodeops ; 
 int /*<<< orphan*/  ext4_ext_print_extent_tree_status (struct inode*) ; 
 int /*<<< orphan*/  free (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int getnewvnode (char*,struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 unsigned int howmany (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ino_to_cg (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_to_fsba (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int ino_to_fsbo (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct inode* malloc (int,int /*<<< orphan*/ ,int) ; 
 int vfs_hash_get (struct mount*,int /*<<< orphan*/ ,int,struct thread*,struct vnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vfs_hash_insert (struct vnode*,int /*<<< orphan*/ ,int,struct thread*,struct vnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

__attribute__((used)) static int
ext2_vget(struct mount *mp, ino_t ino, int flags, struct vnode **vpp)
{
	struct m_ext2fs *fs;
	struct inode *ip;
	struct ext2mount *ump;
	struct buf *bp;
	struct vnode *vp;
	struct thread *td;
	unsigned int i, used_blocks;
	int error;

	td = curthread;
	error = vfs_hash_get(mp, ino, flags, td, vpp, NULL, NULL);
	if (error || *vpp != NULL)
		return (error);

	ump = VFSTOEXT2(mp);
	ip = malloc(sizeof(struct inode), M_EXT2NODE, M_WAITOK | M_ZERO);

	/* Allocate a new vnode/inode. */
	if ((error = getnewvnode("ext2fs", mp, &ext2_vnodeops, &vp)) != 0) {
		*vpp = NULL;
		free(ip, M_EXT2NODE);
		return (error);
	}
	vp->v_data = ip;
	ip->i_vnode = vp;
	ip->i_e2fs = fs = ump->um_e2fs;
	ip->i_ump = ump;
	ip->i_number = ino;

	lockmgr(vp->v_vnlock, LK_EXCLUSIVE, NULL);
	error = insmntque(vp, mp);
	if (error != 0) {
		free(ip, M_EXT2NODE);
		*vpp = NULL;
		return (error);
	}
	error = vfs_hash_insert(vp, ino, flags, td, vpp, NULL, NULL);
	if (error || *vpp != NULL)
		return (error);

	/* Read in the disk contents for the inode, copy into the inode. */
	if ((error = bread(ump->um_devvp, fsbtodb(fs, ino_to_fsba(fs, ino)),
	    (int)fs->e2fs_bsize, NOCRED, &bp)) != 0) {
		/*
		 * The inode does not contain anything useful, so it would
		 * be misleading to leave it on its hash chain. With mode
		 * still zero, it will be unlinked and returned to the free
		 * list by vput().
		 */
		brelse(bp);
		vput(vp);
		*vpp = NULL;
		return (error);
	}
	/* convert ext2 inode to dinode */
	error = ext2_ei2i((struct ext2fs_dinode *)((char *)bp->b_data +
	    EXT2_INODE_SIZE(fs) * ino_to_fsbo(fs, ino)), ip);
	if (error) {
		brelse(bp);
		vput(vp);
		*vpp = NULL;
		return (error);
	}
	ip->i_block_group = ino_to_cg(fs, ino);
	ip->i_next_alloc_block = 0;
	ip->i_next_alloc_goal = 0;

	/*
	 * Now we want to make sure that block pointers for unused
	 * blocks are zeroed out - ext2_balloc depends on this
	 * although for regular files and directories only
	 *
	 * If IN_E4EXTENTS is enabled, unused blocks are not zeroed
	 * out because we could corrupt the extent tree.
	 */
	if (!(ip->i_flag & IN_E4EXTENTS) &&
	    (S_ISDIR(ip->i_mode) || S_ISREG(ip->i_mode))) {
		used_blocks = howmany(ip->i_size, fs->e2fs_bsize);
		for (i = used_blocks; i < EXT2_NDIR_BLOCKS; i++)
			ip->i_db[i] = 0;
	}
#ifdef EXT2FS_PRINT_EXTENTS
	ext2_print_inode(ip);
	ext4_ext_print_extent_tree_status(ip);
#endif
	bqrelse(bp);

	/*
	 * Initialize the vnode from the inode, check for aliases.
	 * Note that the underlying vnode may have changed.
	 */
	if ((error = ext2_vinit(mp, &ext2_fifoops, &vp)) != 0) {
		vput(vp);
		*vpp = NULL;
		return (error);
	}

	/*
	 * Finish inode initialization.
	 */

	*vpp = vp;
	return (0);
}