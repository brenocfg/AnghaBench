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
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
typedef  scalar_t__ associd_t ;
struct TYPE_2__ {scalar_t__ uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READCLOCK ; 
 int /*<<< orphan*/  TYPE_CLOCK ; 
 scalar_t__ checkassocid (scalar_t__) ; 
 int /*<<< orphan*/  dolist (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_varlist ; 

__attribute__((used)) static void
clocklist(
	struct parse *pcmd,
	FILE *fp
	)
{
	associd_t associd;

	/* HMS: uval? */
	if (pcmd->nargs == 0) {
		associd = 0;
	} else {
		if (pcmd->argval[0].uval == 0)
			associd = 0;
		else if ((associd = checkassocid(pcmd->argval[0].uval)) == 0)
			return;
	}

	dolist(g_varlist, associd, CTL_OP_READCLOCK, TYPE_CLOCK, fp);
}