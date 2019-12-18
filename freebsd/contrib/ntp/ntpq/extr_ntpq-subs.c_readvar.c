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
struct varlist {int dummy; } ;
struct parse {int nargs; TYPE_1__* argval; } ;
typedef  scalar_t__ associd_t ;
struct TYPE_2__ {scalar_t__ uval; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READVAR ; 
 int MAXLIST ; 
 int TYPE_PEER ; 
 int TYPE_SYS ; 
 int /*<<< orphan*/  ZERO (struct varlist*) ; 
 scalar_t__ checkassocid (scalar_t__) ; 
 int /*<<< orphan*/  doaddvlist (struct varlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doclearvlist (struct varlist*) ; 
 int /*<<< orphan*/  dolist (struct varlist*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
readvar(
	struct parse *pcmd,
	FILE *fp
	)
{
	associd_t	associd;
	size_t		tmpcount;
	size_t		u;
	int		type;
	struct varlist	tmplist[MAXLIST];


	/* HMS: uval? */
	if (pcmd->nargs == 0 || pcmd->argval[0].uval == 0)
		associd = 0;
	else if ((associd = checkassocid(pcmd->argval[0].uval)) == 0)
		return;

	ZERO(tmplist);
	if (pcmd->nargs > 1) {
		tmpcount = pcmd->nargs - 1;
		for (u = 0; u < tmpcount; u++)
			doaddvlist(tmplist, pcmd->argval[1 + u].string);
	}

	type = (0 == associd)
		   ? TYPE_SYS
		   : TYPE_PEER;
	dolist(tmplist, associd, CTL_OP_READVAR, type, fp);

	doclearvlist(tmplist);
}