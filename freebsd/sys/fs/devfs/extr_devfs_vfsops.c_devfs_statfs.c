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
struct statfs {int f_blocks; scalar_t__ f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; void* f_iosize; void* f_bsize; scalar_t__ f_flags; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 void* DEV_BSIZE ; 

__attribute__((used)) static int
devfs_statfs(struct mount *mp, struct statfs *sbp)
{

	sbp->f_flags = 0;
	sbp->f_bsize = DEV_BSIZE;
	sbp->f_iosize = DEV_BSIZE;
	sbp->f_blocks = 2;		/* 1K to keep df happy */
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = 0;
	sbp->f_ffree = 0;
	return (0);
}