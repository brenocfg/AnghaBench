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
struct netgrp {char** ng_str; struct netgrp* ng_next; } ;
struct linelist {char* l_groupname; char* l_line; struct linelist* l_next; } ;
struct TYPE_2__ {char* grname; struct netgrp* gr; } ;

/* Variables and functions */
 size_t NG_DOM ; 
 size_t NG_HOST ; 
 size_t NG_USER ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ grouphead ; 
 struct linelist* linehead ; 

void
__endnetgrent(void)
{
	struct linelist *lp, *olp;
	struct netgrp *gp, *ogp;

	lp = linehead;
	while (lp) {
		olp = lp;
		lp = lp->l_next;
		free(olp->l_groupname);
		free(olp->l_line);
		free((char *)olp);
	}
	linehead = (struct linelist *)0;
	if (grouphead.grname) {
		free(grouphead.grname);
		grouphead.grname = (char *)0;
	}
	gp = grouphead.gr;
	while (gp) {
		ogp = gp;
		gp = gp->ng_next;
		if (ogp->ng_str[NG_HOST])
			free(ogp->ng_str[NG_HOST]);
		if (ogp->ng_str[NG_USER])
			free(ogp->ng_str[NG_USER]);
		if (ogp->ng_str[NG_DOM])
			free(ogp->ng_str[NG_DOM]);
		free((char *)ogp);
	}
	grouphead.gr = (struct netgrp *)0;
}