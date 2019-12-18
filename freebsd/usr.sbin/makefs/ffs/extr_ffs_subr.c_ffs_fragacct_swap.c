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
struct fs {size_t fs_frag; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int NBBY ; 
 int* around ; 
 scalar_t__** fragtbl ; 
 int* inside ; 
 scalar_t__ ufs_rw32 (scalar_t__,int) ; 

void
ffs_fragacct_swap(struct fs *fs, int fragmap, int32_t fraglist[], int cnt, int needswap)
{
	int inblk;
	int field, subfield;
	int siz, pos;

	inblk = (int)(fragtbl[fs->fs_frag][fragmap]) << 1;
	fragmap <<= 1;
	for (siz = 1; siz < fs->fs_frag; siz++) {
		if ((inblk & (1 << (siz + (fs->fs_frag & (NBBY - 1))))) == 0)
			continue;
		field = around[siz];
		subfield = inside[siz];
		for (pos = siz; pos <= fs->fs_frag; pos++) {
			if ((fragmap & field) == subfield) {
				fraglist[siz] = ufs_rw32(
				    ufs_rw32(fraglist[siz], needswap) + cnt,
				    needswap);
				pos += siz;
				field <<= siz;
				subfield <<= siz;
			}
			field <<= 1;
			subfield <<= 1;
		}
	}
}