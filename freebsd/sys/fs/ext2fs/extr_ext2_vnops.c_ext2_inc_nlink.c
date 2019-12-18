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
struct inode {int i_nlink; int /*<<< orphan*/  i_e2fs; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EMLINK ; 
 int /*<<< orphan*/  EXT2F_ROCOMPAT_DIR_NLINK ; 
 scalar_t__ EXT2_HAS_RO_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EXT4_LINK_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_inc_nlink(struct inode *ip)
{

	ip->i_nlink++;

	if (S_ISDIR(ip->i_mode) &&
	    EXT2_HAS_RO_COMPAT_FEATURE(ip->i_e2fs, EXT2F_ROCOMPAT_DIR_NLINK) &&
	    ip->i_nlink > 1) {
		if (ip->i_nlink >= EXT4_LINK_MAX || ip->i_nlink == 2)
			ip->i_nlink = 1;
	} else if (ip->i_nlink > EXT4_LINK_MAX) {
		ip->i_nlink--;
		return (EMLINK);
	}

	return (0);
}