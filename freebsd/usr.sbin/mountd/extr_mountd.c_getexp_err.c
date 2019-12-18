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
struct grouplist {struct grouplist* gr_next; } ;
struct exportlist {int ex_flag; } ;

/* Variables and functions */
 int EX_LINKED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int OP_QUIET ; 
 int /*<<< orphan*/  free_exp (struct exportlist*) ; 
 int /*<<< orphan*/  free_grp (struct grouplist*) ; 
 int /*<<< orphan*/  line ; 
 int opt_flags ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
getexp_err(struct exportlist *ep, struct grouplist *grp, const char *reason)
{
	struct grouplist *tgrp;

	if (!(opt_flags & OP_QUIET)) {
		if (reason != NULL)
			syslog(LOG_ERR, "bad exports list line '%s': %s", line,
			    reason);
		else
			syslog(LOG_ERR, "bad exports list line '%s'", line);
	}
	if (ep && (ep->ex_flag & EX_LINKED) == 0)
		free_exp(ep);
	while (grp) {
		tgrp = grp;
		grp = grp->gr_next;
		free_grp(tgrp);
	}
}