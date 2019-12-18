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
typedef  int u_char ;
struct fs {scalar_t__ fs_fragshift; } ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 

int
ffs_isblock(struct fs *fs, u_char *cp, int32_t h)
{
	u_char mask;

	switch ((int)fs->fs_fragshift) {
	case 3:
		return (cp[h] == 0xff);
	case 2:
		mask = 0x0f << ((h & 0x1) << 2);
		return ((cp[h >> 1] & mask) == mask);
	case 1:
		mask = 0x03 << ((h & 0x3) << 1);
		return ((cp[h >> 2] & mask) == mask);
	case 0:
		mask = 0x01 << (h & 0x7);
		return ((cp[h >> 3] & mask) == mask);
	default:
		panic("ffs_isblock: unknown fs_fragshift %d",
		    (int)fs->fs_fragshift);
	}
}