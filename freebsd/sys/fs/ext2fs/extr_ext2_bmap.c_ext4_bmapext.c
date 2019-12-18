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
struct m_ext2fs {int dummy; } ;
struct inode {scalar_t__ i_data; struct m_ext2fs* i_e2fs; } ;
struct ext4_extent_path {struct ext4_extent* ep_ext; } ;
struct ext4_extent_header {int eh_depth; } ;
struct ext4_extent {scalar_t__ e_blk; scalar_t__ e_len; scalar_t__ e_start_lo; scalar_t__ e_start_hi; } ;
typedef  int int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 struct inode* VTOI (struct vnode*) ; 
 int ext4_ext_find_extent (struct inode*,scalar_t__,struct ext4_extent_path**) ; 
 int /*<<< orphan*/  ext4_ext_path_free (struct ext4_extent_path*) ; 
 int fsbtodb (struct m_ext2fs*,scalar_t__) ; 

int
ext4_bmapext(struct vnode *vp, int32_t bn, int64_t *bnp, int *runp, int *runb)
{
	struct inode *ip;
	struct m_ext2fs *fs;
	struct ext4_extent_header *ehp;
	struct ext4_extent *ep;
	struct ext4_extent_path *path = NULL;
	daddr_t lbn;
	int error, depth;

	ip = VTOI(vp);
	fs = ip->i_e2fs;
	lbn = bn;
	ehp = (struct ext4_extent_header *)ip->i_data;
	depth = ehp->eh_depth;

	*bnp = -1;
	if (runp != NULL)
		*runp = 0;
	if (runb != NULL)
		*runb = 0;

	error = ext4_ext_find_extent(ip, lbn, &path);
	if (error)
		return (error);

	ep = path[depth].ep_ext;
	if(ep) {
		if (lbn < ep->e_blk) {
			if (runp != NULL)
				*runp = ep->e_blk - lbn - 1;
		} else if (ep->e_blk <= lbn && lbn < ep->e_blk + ep->e_len) {
			*bnp = fsbtodb(fs, lbn - ep->e_blk +
			    (ep->e_start_lo | (daddr_t)ep->e_start_hi << 32));
			if (runp != NULL)
				*runp = ep->e_len - (lbn - ep->e_blk) - 1;
			if (runb != NULL)
				*runb = lbn - ep->e_blk;
		} else {
			if (runb != NULL)
				*runb = ep->e_blk + lbn - ep->e_len;
		}
	}

	ext4_ext_path_free(path);

	return (error);
}