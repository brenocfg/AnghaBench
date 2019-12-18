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
struct udf_mnt {int /*<<< orphan*/  part_len; int /*<<< orphan*/  bsize; } ;
struct statfs {scalar_t__ f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_iosize; int /*<<< orphan*/  f_bsize; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 struct udf_mnt* VFSTOUDFFS (struct mount*) ; 

__attribute__((used)) static int
udf_statfs(struct mount *mp, struct statfs *sbp)
{
	struct udf_mnt *udfmp;

	udfmp = VFSTOUDFFS(mp);

	sbp->f_bsize = udfmp->bsize;
	sbp->f_iosize = udfmp->bsize;
	sbp->f_blocks = udfmp->part_len;
	sbp->f_bfree = 0;
	sbp->f_bavail = 0;
	sbp->f_files = 0;
	sbp->f_ffree = 0;
	return 0;
}