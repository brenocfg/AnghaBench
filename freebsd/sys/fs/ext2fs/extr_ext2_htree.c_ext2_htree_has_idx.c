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
struct inode {int i_flag; int /*<<< orphan*/  i_e2fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_COMPAT_DIRHASHINDEX ; 
 scalar_t__ EXT2_HAS_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IN_E3INDEX ; 

int
ext2_htree_has_idx(struct inode *ip)
{
	if (EXT2_HAS_COMPAT_FEATURE(ip->i_e2fs, EXT2F_COMPAT_DIRHASHINDEX) &&
	    ip->i_flag & IN_E3INDEX)
		return (1);
	else
		return (0);
}