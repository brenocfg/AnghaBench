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
struct stat {int /*<<< orphan*/  st_spare; scalar_t__ st_padding1; scalar_t__ st_padding0; int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_birthtim; scalar_t__ st_btim_ext; scalar_t__ st_ctim_ext; scalar_t__ st_mtim_ext; scalar_t__ st_atim_ext; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;
struct freebsd11_stat {int /*<<< orphan*/  st_gen; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_birthtim; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
__stat11_to_stat(const struct freebsd11_stat *sb11, struct stat *sb)
{

	sb->st_dev = sb11->st_dev;
	sb->st_ino = sb11->st_ino;
	sb->st_nlink = sb11->st_nlink;
	sb->st_mode = sb11->st_mode;
	sb->st_uid = sb11->st_uid;
	sb->st_gid = sb11->st_gid;
	sb->st_rdev = sb11->st_rdev;
	sb->st_atim = sb11->st_atim;
	sb->st_mtim = sb11->st_mtim;
	sb->st_ctim = sb11->st_ctim;
#ifdef __STAT_TIME_T_EXT
	sb->st_atim_ext = 0;
	sb->st_mtim_ext = 0;
	sb->st_ctim_ext = 0;
	sb->st_btim_ext = 0;
#endif
	sb->st_birthtim = sb11->st_birthtim;
	sb->st_size = sb11->st_size;
	sb->st_blocks = sb11->st_blocks;
	sb->st_blksize = sb11->st_blksize;
	sb->st_flags = sb11->st_flags;
	sb->st_gen = sb11->st_gen;
	sb->st_padding0 = 0;
	sb->st_padding1 = 0;
	memset(sb->st_spare, 0, sizeof(sb->st_spare));
}