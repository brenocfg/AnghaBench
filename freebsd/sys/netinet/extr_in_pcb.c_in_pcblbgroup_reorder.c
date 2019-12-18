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
struct inpcblbgrouphead {int dummy; } ;
struct inpcblbgroup {int il_inpcnt; int il_inpsiz; int /*<<< orphan*/ * il_inp; } ;

/* Variables and functions */
 int INPCBLBGROUP_SIZMIN ; 
 struct inpcblbgroup* in_pcblbgroup_resize (struct inpcblbgrouphead*,struct inpcblbgroup*,int) ; 

__attribute__((used)) static void
in_pcblbgroup_reorder(struct inpcblbgrouphead *hdr, struct inpcblbgroup **grpp,
    int i)
{
	struct inpcblbgroup *grp, *new_grp;

	grp = *grpp;
	for (; i + 1 < grp->il_inpcnt; ++i)
		grp->il_inp[i] = grp->il_inp[i + 1];
	grp->il_inpcnt--;

	if (grp->il_inpsiz > INPCBLBGROUP_SIZMIN &&
	    grp->il_inpcnt <= grp->il_inpsiz / 4) {
		/* Shrink this group. */
		new_grp = in_pcblbgroup_resize(hdr, grp, grp->il_inpsiz / 2);
		if (new_grp != NULL)
			*grpp = new_grp;
	}
}