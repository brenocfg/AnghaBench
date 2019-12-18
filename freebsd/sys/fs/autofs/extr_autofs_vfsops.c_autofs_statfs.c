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
struct statfs {scalar_t__ f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; scalar_t__ f_blocks; scalar_t__ f_iosize; int /*<<< orphan*/  f_bsize; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_BLKSIZE ; 

__attribute__((used)) static int
autofs_statfs(struct mount *mp, struct statfs *sbp)
{

	sbp->f_bsize = S_BLKSIZE;
	sbp->f_iosize = 0;
	sbp->f_blocks = 0;
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = 0;
	sbp->f_ffree = 0;

	return (0);
}