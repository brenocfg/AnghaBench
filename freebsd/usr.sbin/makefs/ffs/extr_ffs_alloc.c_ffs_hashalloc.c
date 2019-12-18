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
struct inode {struct fs* i_fs; } ;
struct fs {int fs_ncg; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 scalar_t__ stub1 (struct inode*,int,scalar_t__,int) ; 
 scalar_t__ stub2 (struct inode*,int,scalar_t__,int) ; 
 scalar_t__ stub3 (struct inode*,int,scalar_t__,int) ; 

__attribute__((used)) static daddr_t
ffs_hashalloc(struct inode *ip, u_int cg, daddr_t pref, int size,
    daddr_t (*allocator)(struct inode *, int, daddr_t, int))
{
	struct fs *fs;
	daddr_t result;
	u_int i, icg = cg;

	fs = ip->i_fs;
	/*
	 * 1: preferred cylinder group
	 */
	result = (*allocator)(ip, cg, pref, size);
	if (result)
		return (result);
	/*
	 * 2: quadratic rehash
	 */
	for (i = 1; i < fs->fs_ncg; i *= 2) {
		cg += i;
		if (cg >= fs->fs_ncg)
			cg -= fs->fs_ncg;
		result = (*allocator)(ip, cg, 0, size);
		if (result)
			return (result);
	}
	/*
	 * 3: brute force search
	 * Note that we start at i == 2, since 0 was checked initially,
	 * and 1 is always checked in the quadratic rehash.
	 */
	cg = (icg + 2) % fs->fs_ncg;
	for (i = 2; i < fs->fs_ncg; i++) {
		result = (*allocator)(ip, cg, 0, size);
		if (result)
			return (result);
		cg++;
		if (cg == fs->fs_ncg)
			cg = 0;
	}
	return (0);
}