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
struct xucred {int dummy; } ;
struct hostlist {struct hostlist* ht_next; struct grouplist* ht_grp; } ;
struct grouplist {scalar_t__ gr_numsecflavors; struct grouplist* gr_next; int /*<<< orphan*/  gr_secflavors; } ;
struct exportlist {scalar_t__ ex_numsecflavors; scalar_t__ ex_defnumsecflavors; int ex_defexflags; struct xucred ex_defanon; int /*<<< orphan*/  ex_secflavors; int /*<<< orphan*/  ex_defsecflavors; int /*<<< orphan*/  ex_flag; } ;
struct dirlist {int /*<<< orphan*/  dp_flag; struct hostlist* dp_hosts; struct dirlist* dp_left; struct dirlist* dp_right; int /*<<< orphan*/  dp_dirp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEFSET ; 
 int /*<<< orphan*/  EX_DEFSET ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct hostlist* get_ht () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_dlist(struct dirlist **dpp, struct dirlist *newdp, struct grouplist *grp,
	int flags, struct exportlist *ep, struct xucred *anoncrp, int exflags)
{
	struct dirlist *dp;
	struct hostlist *hp;
	int cmp;

	dp = *dpp;
	if (dp) {
		cmp = strcmp(dp->dp_dirp, newdp->dp_dirp);
		if (cmp > 0) {
			add_dlist(&dp->dp_left, newdp, grp, flags, ep, anoncrp,
			    exflags);
			return;
		} else if (cmp < 0) {
			add_dlist(&dp->dp_right, newdp, grp, flags, ep, anoncrp,
			    exflags);
			return;
		} else
			free((caddr_t)newdp);
	} else {
		dp = newdp;
		dp->dp_left = (struct dirlist *)NULL;
		*dpp = dp;
	}
	if (grp) {

		/*
		 * Hang all of the host(s) off of the directory point.
		 */
		do {
			hp = get_ht();
			hp->ht_grp = grp;
			hp->ht_next = dp->dp_hosts;
			dp->dp_hosts = hp;
			/* Save the security flavors list for this host set. */
			grp->gr_numsecflavors = ep->ex_numsecflavors;
			if (ep->ex_numsecflavors > 0)
				memcpy(grp->gr_secflavors, ep->ex_secflavors,
				    sizeof(ep->ex_secflavors));
			grp = grp->gr_next;
		} while (grp);
	} else {
		ep->ex_flag |= EX_DEFSET;
		dp->dp_flag |= DP_DEFSET;
		/* Save the default security flavors list. */
		ep->ex_defnumsecflavors = ep->ex_numsecflavors;
		if (ep->ex_numsecflavors > 0)
			memcpy(ep->ex_defsecflavors, ep->ex_secflavors,
			    sizeof(ep->ex_secflavors));
		ep->ex_defanon = *anoncrp;
		ep->ex_defexflags = exflags;
	}
}