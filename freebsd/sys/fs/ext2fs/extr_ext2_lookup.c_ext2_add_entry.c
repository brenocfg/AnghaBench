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
typedef  int u_int ;
struct vnode {int dummy; } ;
struct inode {scalar_t__ i_offset; int i_count; scalar_t__ i_size; int i_flag; } ;
struct ext2fs_direct_2 {int e2d_reclen; scalar_t__ e2d_ino; int /*<<< orphan*/  e2d_namlen; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ DOINGASYNC (struct vnode*) ; 
 int EXT2_DIR_REC_LEN (int /*<<< orphan*/ ) ; 
 int IN_CHANGE ; 
 int IN_UPDATE ; 
 struct inode* VTOI (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bwrite (struct buf*) ; 
 int ext2_blkatoff (struct vnode*,int /*<<< orphan*/ ,char**,struct buf**) ; 
 int /*<<< orphan*/  ext2_dirent_csum_set (struct inode*,struct ext2fs_direct_2*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
ext2_add_entry(struct vnode *dvp, struct ext2fs_direct_2 *entry)
{
	struct ext2fs_direct_2 *ep, *nep;
	struct inode *dp;
	struct buf *bp;
	u_int dsize;
	int error, loc, newentrysize, spacefree;
	char *dirbuf;

	dp = VTOI(dvp);

	/*
	 * If dp->i_count is non-zero, then namei found space
	 * for the new entry in the range dp->i_offset to
	 * dp->i_offset + dp->i_count in the directory.
	 * To use this space, we may have to compact the entries located
	 * there, by copying them together towards the beginning of the
	 * block, leaving the free space in one usable chunk at the end.
	 */

	/*
	 * Increase size of directory if entry eats into new space.
	 * This should never push the size past a new multiple of
	 * DIRBLKSIZE.
	 *
	 * N.B. - THIS IS AN ARTIFACT OF 4.2 AND SHOULD NEVER HAPPEN.
	 */
	if (dp->i_offset + dp->i_count > dp->i_size)
		dp->i_size = dp->i_offset + dp->i_count;
	/*
	 * Get the block containing the space for the new directory entry.
	 */
	if ((error = ext2_blkatoff(dvp, (off_t)dp->i_offset, &dirbuf,
	    &bp)) != 0)
		return (error);
	/*
	 * Find space for the new entry. In the simple case, the entry at
	 * offset base will have the space. If it does not, then namei
	 * arranged that compacting the region dp->i_offset to
	 * dp->i_offset + dp->i_count would yield the
	 * space.
	 */
	newentrysize = EXT2_DIR_REC_LEN(entry->e2d_namlen);
	ep = (struct ext2fs_direct_2 *)dirbuf;
	dsize = EXT2_DIR_REC_LEN(ep->e2d_namlen);
	spacefree = ep->e2d_reclen - dsize;
	for (loc = ep->e2d_reclen; loc < dp->i_count; ) {
		nep = (struct ext2fs_direct_2 *)(dirbuf + loc);
		if (ep->e2d_ino) {
			/* trim the existing slot */
			ep->e2d_reclen = dsize;
			ep = (struct ext2fs_direct_2 *)((char *)ep + dsize);
		} else {
			/* overwrite; nothing there; header is ours */
			spacefree += dsize;
		}
		dsize = EXT2_DIR_REC_LEN(nep->e2d_namlen);
		spacefree += nep->e2d_reclen - dsize;
		loc += nep->e2d_reclen;
		bcopy((caddr_t)nep, (caddr_t)ep, dsize);
	}
	/*
	 * Update the pointer fields in the previous entry (if any),
	 * copy in the new entry, and write out the block.
	 */
	if (ep->e2d_ino == 0) {
		if (spacefree + dsize < newentrysize)
			panic("ext2_direnter: compact1");
		entry->e2d_reclen = spacefree + dsize;
	} else {
		if (spacefree < newentrysize)
			panic("ext2_direnter: compact2");
		entry->e2d_reclen = spacefree;
		ep->e2d_reclen = dsize;
		ep = (struct ext2fs_direct_2 *)((char *)ep + dsize);
	}
	bcopy((caddr_t)entry, (caddr_t)ep, (u_int)newentrysize);
	ext2_dirent_csum_set(dp, (struct ext2fs_direct_2 *)bp->b_data);
	if (DOINGASYNC(dvp)) {
		bdwrite(bp);
		error = 0;
	} else {
		error = bwrite(bp);
	}
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
	return (error);
}