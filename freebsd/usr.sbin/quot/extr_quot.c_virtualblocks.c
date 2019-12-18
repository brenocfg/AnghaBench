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
typedef  union dinode {int dummy; } dinode ;
struct fs {int fs_bsize; } ;
typedef  int off_t ;

/* Variables and functions */
 int DIP (struct fs*,union dinode*,int /*<<< orphan*/ ) ; 
 int NINDIR (struct fs*) ; 
 int UFS_NDADDR ; 
 int blkroundup (struct fs*,int) ; 
 int /*<<< orphan*/  di_size ; 
 int fragroundup (struct fs*,int) ; 
 int lblkno (struct fs*,int) ; 

__attribute__((used)) static int virtualblocks(struct fs *super, union dinode *dp)
{
	off_t nblk, sz;

	sz = DIP(super, dp, di_size);
#ifdef	COMPAT
	if (lblkno(super,sz) >= UFS_NDADDR) {
		nblk = blkroundup(super,sz);
		if (sz == nblk)
			nblk += super->fs_bsize;
	}

	return sz / 1024;

#else	/* COMPAT */

	if (lblkno(super,sz) >= UFS_NDADDR) {
		nblk = blkroundup(super,sz);
		sz = lblkno(super,nblk);
		sz = (sz - UFS_NDADDR + NINDIR(super) - 1) / NINDIR(super);
		while (sz > 0) {
			nblk += sz * super->fs_bsize;
			/* sz - 1 rounded up */
			sz = (sz - 1 + NINDIR(super) - 1) / NINDIR(super);
		}
	} else
		nblk = fragroundup(super,sz);

	return nblk / 512;
#endif	/* COMPAT */
}