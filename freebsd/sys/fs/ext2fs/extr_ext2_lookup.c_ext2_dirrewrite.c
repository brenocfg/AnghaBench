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
struct inode {int i_flag; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_e2fs; int /*<<< orphan*/  i_number; scalar_t__ i_offset; } ;
struct ext2fs_direct_2 {int /*<<< orphan*/  e2d_type; int /*<<< orphan*/  e2d_ino; } ;
struct componentname {int dummy; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTTOFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2F_INCOMPAT_FTYPE ; 
 int /*<<< orphan*/  EXT2_FT_UNKNOWN ; 
 scalar_t__ EXT2_HAS_INCOMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFTODT (int /*<<< orphan*/ ) ; 
 int IN_CHANGE ; 
 int IN_UPDATE ; 
 struct vnode* ITOV (struct inode*) ; 
 int bwrite (struct buf*) ; 
 int ext2_blkatoff (struct vnode*,int /*<<< orphan*/ ,char**,struct buf**) ; 
 int /*<<< orphan*/  ext2_dirent_csum_set (struct inode*,struct ext2fs_direct_2*) ; 

int
ext2_dirrewrite(struct inode *dp, struct inode *ip, struct componentname *cnp)
{
	struct buf *bp;
	struct ext2fs_direct_2 *ep;
	struct vnode *vdp = ITOV(dp);
	int error;

	if ((error = ext2_blkatoff(vdp, (off_t)dp->i_offset, (char **)&ep,
	    &bp)) != 0)
		return (error);
	ep->e2d_ino = ip->i_number;
	if (EXT2_HAS_INCOMPAT_FEATURE(ip->i_e2fs,
	    EXT2F_INCOMPAT_FTYPE))
		ep->e2d_type = DTTOFT(IFTODT(ip->i_mode));
	else
		ep->e2d_type = EXT2_FT_UNKNOWN;
	ext2_dirent_csum_set(dp, (struct ext2fs_direct_2 *)bp->b_data);
	error = bwrite(bp);
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
	return (error);
}