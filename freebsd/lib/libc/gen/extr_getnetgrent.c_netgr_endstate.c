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
struct netgrp {struct netgrp** ng_str; struct netgrp* ng_next; struct netgrp* l_line; struct netgrp* l_groupname; struct netgrp* l_next; } ;
struct netgr_state {int /*<<< orphan*/ * st_nextgrp; struct netgrp* st_gr; struct netgrp* st_grname; struct netgrp* st_linehead; } ;
struct linelist {struct linelist** ng_str; struct linelist* ng_next; struct linelist* l_line; struct linelist* l_groupname; struct linelist* l_next; } ;

/* Variables and functions */
 size_t NG_DOM ; 
 size_t NG_HOST ; 
 size_t NG_USER ; 
 int /*<<< orphan*/  free (struct netgrp*) ; 

__attribute__((used)) static void
netgr_endstate(void *arg)
{
	struct linelist *lp, *olp;
	struct netgrp *gp, *ogp;
	struct netgr_state *st;

	st = (struct netgr_state *)arg;
	lp = st->st_linehead;
	while (lp != NULL) {
		olp = lp;
		lp = lp->l_next;
		free(olp->l_groupname);
		free(olp->l_line);
		free(olp);
	}
	st->st_linehead = NULL;
	if (st->st_grname != NULL) {
		free(st->st_grname);
		st->st_grname = NULL;
	}
	gp = st->st_gr;
	while (gp != NULL) {
		ogp = gp;
		gp = gp->ng_next;
		free(ogp->ng_str[NG_HOST]);
		free(ogp->ng_str[NG_USER]);
		free(ogp->ng_str[NG_DOM]);
		free(ogp);
	}
	st->st_gr = NULL;
	st->st_nextgrp = NULL;
}