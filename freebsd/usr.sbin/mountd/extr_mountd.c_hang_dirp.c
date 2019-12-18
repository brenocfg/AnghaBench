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
struct exportlist {scalar_t__ ex_defnumsecflavors; scalar_t__ ex_numsecflavors; int ex_defexflags; int /*<<< orphan*/  ex_dirl; int /*<<< orphan*/  ex_secflavors; struct dirlist* ex_defdir; struct xucred ex_defanon; int /*<<< orphan*/  ex_defsecflavors; int /*<<< orphan*/  ex_flag; } ;
struct dirlist {struct dirlist* dp_left; struct hostlist* dp_hosts; int /*<<< orphan*/  dp_flag; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEFSET ; 
 int /*<<< orphan*/  EX_DEFSET ; 
 int OP_ALLDIRS ; 
 int /*<<< orphan*/  add_dlist (int /*<<< orphan*/ *,struct dirlist*,struct grouplist*,int,struct exportlist*,struct xucred*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 struct hostlist* get_ht () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hang_dirp(struct dirlist *dp, struct grouplist *grp, struct exportlist *ep,
	int flags, struct xucred *anoncrp, int exflags)
{
	struct hostlist *hp;
	struct dirlist *dp2;

	if (flags & OP_ALLDIRS) {
		if (ep->ex_defdir)
			free((caddr_t)dp);
		else
			ep->ex_defdir = dp;
		if (grp == (struct grouplist *)NULL) {
			ep->ex_flag |= EX_DEFSET;
			ep->ex_defdir->dp_flag |= DP_DEFSET;
			/* Save the default security flavors list. */
			ep->ex_defnumsecflavors = ep->ex_numsecflavors;
			if (ep->ex_numsecflavors > 0)
				memcpy(ep->ex_defsecflavors, ep->ex_secflavors,
				    sizeof(ep->ex_secflavors));
			ep->ex_defanon = *anoncrp;
			ep->ex_defexflags = exflags;
		} else while (grp) {
			hp = get_ht();
			hp->ht_grp = grp;
			hp->ht_next = ep->ex_defdir->dp_hosts;
			ep->ex_defdir->dp_hosts = hp;
			/* Save the security flavors list for this host set. */
			grp->gr_numsecflavors = ep->ex_numsecflavors;
			if (ep->ex_numsecflavors > 0)
				memcpy(grp->gr_secflavors, ep->ex_secflavors,
				    sizeof(ep->ex_secflavors));
			grp = grp->gr_next;
		}
	} else {

		/*
		 * Loop through the directories adding them to the tree.
		 */
		while (dp) {
			dp2 = dp->dp_left;
			add_dlist(&ep->ex_dirl, dp, grp, flags, ep, anoncrp,
			    exflags);
			dp = dp2;
		}
	}
}