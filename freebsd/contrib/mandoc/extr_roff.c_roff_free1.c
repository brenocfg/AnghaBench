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
struct roff {scalar_t__ mstackpos; int rstackpos; TYPE_1__* xtab; int /*<<< orphan*/ * xmbtab; int /*<<< orphan*/ * rentab; int /*<<< orphan*/ * strtab; int /*<<< orphan*/ * regtab; scalar_t__ rstacksz; TYPE_1__* rstack; scalar_t__ last; int /*<<< orphan*/ * eqn; int /*<<< orphan*/  last_eqn; int /*<<< orphan*/ * tbl; int /*<<< orphan*/  last_tbl; int /*<<< orphan*/  first_tbl; } ;
struct TYPE_2__ {struct TYPE_2__* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  eqn_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  roff_freereg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roff_freestr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roff_userret (struct roff*) ; 
 int /*<<< orphan*/  roffnode_pop (struct roff*) ; 
 int /*<<< orphan*/  tbl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
roff_free1(struct roff *r)
{
	int		 i;

	tbl_free(r->first_tbl);
	r->first_tbl = r->last_tbl = r->tbl = NULL;

	eqn_free(r->last_eqn);
	r->last_eqn = r->eqn = NULL;

	while (r->mstackpos >= 0)
		roff_userret(r);

	while (r->last)
		roffnode_pop(r);

	free (r->rstack);
	r->rstack = NULL;
	r->rstacksz = 0;
	r->rstackpos = -1;

	roff_freereg(r->regtab);
	r->regtab = NULL;

	roff_freestr(r->strtab);
	roff_freestr(r->rentab);
	roff_freestr(r->xmbtab);
	r->strtab = r->rentab = r->xmbtab = NULL;

	if (r->xtab)
		for (i = 0; i < 128; i++)
			free(r->xtab[i].p);
	free(r->xtab);
	r->xtab = NULL;
}