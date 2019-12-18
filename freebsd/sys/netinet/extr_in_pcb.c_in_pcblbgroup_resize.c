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
struct inpcblbgroup {int il_inpcnt; int il_inpsiz; int /*<<< orphan*/ * il_inp; int /*<<< orphan*/  il_dependladdr; int /*<<< orphan*/  il_lport; int /*<<< orphan*/  il_vflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct inpcblbgroup* in_pcblbgroup_alloc (struct inpcblbgrouphead*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_pcblbgroup_free (struct inpcblbgroup*) ; 

__attribute__((used)) static struct inpcblbgroup *
in_pcblbgroup_resize(struct inpcblbgrouphead *hdr,
    struct inpcblbgroup *old_grp, int size)
{
	struct inpcblbgroup *grp;
	int i;

	grp = in_pcblbgroup_alloc(hdr, old_grp->il_vflag,
	    old_grp->il_lport, &old_grp->il_dependladdr, size);
	if (grp == NULL)
		return (NULL);

	KASSERT(old_grp->il_inpcnt < grp->il_inpsiz,
	    ("invalid new local group size %d and old local group count %d",
	     grp->il_inpsiz, old_grp->il_inpcnt));

	for (i = 0; i < old_grp->il_inpcnt; ++i)
		grp->il_inp[i] = old_grp->il_inp[i];
	grp->il_inpcnt = old_grp->il_inpcnt;
	in_pcblbgroup_free(old_grp);
	return (grp);
}