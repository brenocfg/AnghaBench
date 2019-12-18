#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* c; } ;
struct TYPE_15__ {TYPE_1__ bp1; } ;
struct TYPE_17__ {TYPE_2__ ibcw; struct TYPE_17__* lastbcomm; struct TYPE_17__* ibp; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ex_private; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ EX_PRIVATE ;

/* Variables and functions */
 TYPE_4__* EXP (TYPE_3__*) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCRIPT ; 
 scalar_t__ argv_free (TYPE_3__*) ; 
 scalar_t__ cscope_end (TYPE_3__*) ; 
 scalar_t__ ex_tag_free (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ sscr_end (TYPE_3__*) ; 

int
ex_screen_end(SCR *sp)
{
	EX_PRIVATE *exp;
	int rval;

	if ((exp = EXP(sp)) == NULL)
		return (0);

	rval = 0;

	/* Close down script connections. */
	if (F_ISSET(sp, SC_SCRIPT) && sscr_end(sp))
		rval = 1;

	if (argv_free(sp))
		rval = 1;

	if (exp->ibp != NULL)
		free(exp->ibp);

	if (exp->lastbcomm != NULL)
		free(exp->lastbcomm);

	if (exp->ibcw.bp1.c != NULL)
		free(exp->ibcw.bp1.c);

	if (ex_tag_free(sp))
		rval = 1;

	if (cscope_end(sp))
		rval = 1;

	/* Free private memory. */
	free(exp);
	sp->ex_private = NULL;

	return (rval);
}