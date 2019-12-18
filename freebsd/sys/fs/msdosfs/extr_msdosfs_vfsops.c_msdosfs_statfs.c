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
struct statfs {scalar_t__ f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; scalar_t__ f_blocks; int /*<<< orphan*/  f_iosize; int /*<<< orphan*/  f_bsize; } ;
struct msdosfsmount {int /*<<< orphan*/  pm_RootDirEnts; int /*<<< orphan*/  pm_freeclustercount; scalar_t__ pm_maxcluster; int /*<<< orphan*/  pm_bpcluster; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 struct msdosfsmount* VFSTOMSDOSFS (struct mount*) ; 

__attribute__((used)) static int
msdosfs_statfs(struct mount *mp, struct statfs *sbp)
{
	struct msdosfsmount *pmp;

	pmp = VFSTOMSDOSFS(mp);
	sbp->f_bsize = pmp->pm_bpcluster;
	sbp->f_iosize = pmp->pm_bpcluster;
	sbp->f_blocks = pmp->pm_maxcluster + 1;
	sbp->f_bfree = pmp->pm_freeclustercount;
	sbp->f_bavail = pmp->pm_freeclustercount;
	sbp->f_files = pmp->pm_RootDirEnts;	/* XXX */
	sbp->f_ffree = 0;	/* what to put in here? */
	return (0);
}