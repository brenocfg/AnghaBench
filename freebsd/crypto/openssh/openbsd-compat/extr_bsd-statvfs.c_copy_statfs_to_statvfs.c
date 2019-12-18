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
struct statvfs {int /*<<< orphan*/  f_namemax; scalar_t__ f_flag; scalar_t__ f_fsid; int /*<<< orphan*/  f_favail; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_frsize; int /*<<< orphan*/  f_bsize; } ;
struct statfs {scalar_t__ f_flags; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNAMELEN ; 

__attribute__((used)) static void
copy_statfs_to_statvfs(struct statvfs *to, struct statfs *from)
{
	to->f_bsize = from->f_bsize;
	to->f_frsize = from->f_bsize;	/* no exact equivalent */
	to->f_blocks = from->f_blocks;
	to->f_bfree = from->f_bfree;
	to->f_bavail = from->f_bavail;
	to->f_files = from->f_files;
	to->f_ffree = from->f_ffree;
	to->f_favail = from->f_ffree;	/* no exact equivalent */
	to->f_fsid = 0;			/* XXX fix me */
#ifdef HAVE_STRUCT_STATFS_F_FLAGS
	to->f_flag = from->f_flags;
#else
	to->f_flag = 0;
#endif
	to->f_namemax = MNAMELEN;
}