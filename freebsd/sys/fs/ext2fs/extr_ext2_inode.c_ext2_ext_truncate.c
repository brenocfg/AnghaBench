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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct m_ext2fs {int e2fs_maxfilesize; int e2fs_bsize; } ;
struct inode {int i_size; int i_flag; struct m_ext2fs* i_e2fs; } ;
struct buf {int b_bufsize; int /*<<< orphan*/  b_flags; scalar_t__ b_data; } ;
typedef  int off_t ;
typedef  int int32_t ;

/* Variables and functions */
 int BA_CLRBUF ; 
 int /*<<< orphan*/  B_CLUSTEROK ; 
 scalar_t__ DOINGASYNC (struct vnode*) ; 
 int EFBIG ; 
 int IN_CHANGE ; 
 int IN_UPDATE ; 
 int IO_SYNC ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  allocbuf (struct buf*,int) ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int blkoff (struct m_ext2fs*,int) ; 
 int blksize (struct m_ext2fs*,struct inode*,int) ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 int /*<<< orphan*/  bzero (char*,int /*<<< orphan*/ ) ; 
 int ext2_balloc (struct inode*,int,int,struct ucred*,struct buf**,int) ; 
 int ext2_update (struct vnode*,int) ; 
 int ext4_ext_remove_space (struct inode*,int,int,struct ucred*,struct thread*) ; 
 int lblkno (struct m_ext2fs*,int) ; 
 int /*<<< orphan*/  vnode_pager_setsize (struct vnode*,int) ; 
 int vtruncbuf (struct vnode*,int,int) ; 

__attribute__((used)) static int
ext2_ext_truncate(struct vnode *vp, off_t length, int flags,
    struct ucred *cred, struct thread *td)
{
	struct vnode *ovp = vp;
	int32_t lastblock;
	struct m_ext2fs *fs;
	struct inode *oip;
	struct buf *bp;
	uint32_t lbn, offset;
	int error, size;
	off_t osize;

	oip = VTOI(ovp);
	fs = oip->i_e2fs;
	osize = oip->i_size;

	if (osize < length) {
		if (length > oip->i_e2fs->e2fs_maxfilesize) {
			return (EFBIG);
		}
		vnode_pager_setsize(ovp, length);
		offset = blkoff(fs, length - 1);
		lbn = lblkno(fs, length - 1);
		flags |= BA_CLRBUF;
		error = ext2_balloc(oip, lbn, offset + 1, cred, &bp, flags);
		if (error) {
			vnode_pager_setsize(vp, osize);
			return (error);
		}
		oip->i_size = length;
		if (bp->b_bufsize == fs->e2fs_bsize)
			bp->b_flags |= B_CLUSTEROK;
		if (flags & IO_SYNC)
			bwrite(bp);
		else if (DOINGASYNC(ovp))
			bdwrite(bp);
		else
			bawrite(bp);
		oip->i_flag |= IN_CHANGE | IN_UPDATE;
		return (ext2_update(ovp, !DOINGASYNC(ovp)));
	}

	lastblock = (length + fs->e2fs_bsize - 1) / fs->e2fs_bsize;
	error = ext4_ext_remove_space(oip, lastblock, flags, cred, td);
	if (error)
		return (error);

	offset = blkoff(fs, length);
	if (offset == 0) {
		oip->i_size = length;
	} else {
		lbn = lblkno(fs, length);
		flags |= BA_CLRBUF;
		error = ext2_balloc(oip, lbn, offset, cred, &bp, flags);
		if (error) {
			return (error);
		}
		oip->i_size = length;
		size = blksize(fs, oip, lbn);
		bzero((char *)bp->b_data + offset, (u_int)(size - offset));
		allocbuf(bp, size);
		if (bp->b_bufsize == fs->e2fs_bsize)
			bp->b_flags |= B_CLUSTEROK;
		if (flags & IO_SYNC)
			bwrite(bp);
		else if (DOINGASYNC(ovp))
			bdwrite(bp);
		else
			bawrite(bp);
	}

	oip->i_size = osize;
	error = vtruncbuf(ovp, length, (int)fs->e2fs_bsize);
	if (error)
		return (error);

	vnode_pager_setsize(ovp, length);

	oip->i_size = length;
	oip->i_flag |= IN_CHANGE | IN_UPDATE;
	error = ext2_update(ovp, !DOINGASYNC(ovp));

	return (error);
}