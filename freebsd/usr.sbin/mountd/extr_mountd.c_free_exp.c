#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grouplist {struct grouplist* gr_next; } ;
struct exportlist {struct grouplist* ex_grphead; int /*<<< orphan*/  ex_dirl; scalar_t__ ex_indexfile; scalar_t__ ex_fsdir; TYPE_1__* ex_defdir; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dp_hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_grp (struct grouplist*) ; 
 int /*<<< orphan*/  free_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_exp(struct exportlist *ep)
{
	struct grouplist *grp, *tgrp;

	if (ep->ex_defdir) {
		free_host(ep->ex_defdir->dp_hosts);
		free((caddr_t)ep->ex_defdir);
	}
	if (ep->ex_fsdir)
		free(ep->ex_fsdir);
	if (ep->ex_indexfile)
		free(ep->ex_indexfile);
	free_dir(ep->ex_dirl);
	grp = ep->ex_grphead;
	while (grp) {
		tgrp = grp;
		grp = grp->gr_next;
		free_grp(tgrp);
	}
	free((caddr_t)ep);
}