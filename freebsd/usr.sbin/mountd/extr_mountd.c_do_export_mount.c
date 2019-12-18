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
struct statfs {int dummy; } ;
struct grouplist {struct grouplist* gr_next; int /*<<< orphan*/  gr_secflavors; int /*<<< orphan*/  gr_numsecflavors; int /*<<< orphan*/  gr_anon; int /*<<< orphan*/  gr_exflags; int /*<<< orphan*/  gr_type; } ;
struct exportlist {int ex_flag; int /*<<< orphan*/  ex_fsdir; struct grouplist* ex_grphead; int /*<<< orphan*/  ex_defsecflavors; int /*<<< orphan*/  ex_defnumsecflavors; int /*<<< orphan*/  ex_defanon; int /*<<< orphan*/  ex_defexflags; } ;

/* Variables and functions */
 int EX_DEFSET ; 
 int /*<<< orphan*/  GT_DEFAULT ; 
 int /*<<< orphan*/  LOGDEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int do_mount (struct exportlist*,struct grouplist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,struct statfs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_export_mount(struct exportlist *ep, struct statfs *fsp)
{
	struct grouplist *grp, defgrp;
	int ret;
	size_t dirlen;

	LOGDEBUG("do_export_mount=%s", ep->ex_fsdir);
	dirlen = strlen(ep->ex_fsdir);
	if ((ep->ex_flag & EX_DEFSET) != 0) {
		defgrp.gr_type = GT_DEFAULT;
		defgrp.gr_next = NULL;
		/* We have an entry for all other hosts/nets. */
		LOGDEBUG("ex_defexflags=0x%x", ep->ex_defexflags);
		ret = do_mount(ep, &defgrp, ep->ex_defexflags, &ep->ex_defanon,
		    ep->ex_fsdir, dirlen, fsp, ep->ex_defnumsecflavors,
		    ep->ex_defsecflavors);
		if (ret != 0)
			return (ret);
	}

	/* Do a mount for each group. */
	grp = ep->ex_grphead;
	while (grp != NULL) {
		LOGDEBUG("do mount gr_type=0x%x gr_exflags=0x%x",
		    grp->gr_type, grp->gr_exflags);
		ret = do_mount(ep, grp, grp->gr_exflags, &grp->gr_anon,
		    ep->ex_fsdir, dirlen, fsp, grp->gr_numsecflavors,
		    grp->gr_secflavors);
		if (ret != 0)
			return (ret);
		grp = grp->gr_next;
	}
	return (0);
}