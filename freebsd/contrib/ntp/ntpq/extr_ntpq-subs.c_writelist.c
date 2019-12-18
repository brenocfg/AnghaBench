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
typedef  scalar_t__ u_short ;
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
typedef  scalar_t__ associd_t ;
struct TYPE_2__ {scalar_t__ uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_WRITEVAR ; 
 int /*<<< orphan*/  TYPE_PEER ; 
 int /*<<< orphan*/  TYPE_SYS ; 
 scalar_t__ checkassocid (scalar_t__) ; 
 char* currenthost ; 
 int doquerylist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,size_t*,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  g_varlist ; 
 int numhosts ; 
 int /*<<< orphan*/  printvars (size_t,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
writelist(
	struct parse *pcmd,
	FILE *fp
	)
{
	const char *datap;
	int res;
	associd_t associd;
	size_t dsize;
	u_short rstatus;

	if (pcmd->nargs == 0) {
		associd = 0;
	} else {
		/* HMS: Do we really want uval here? */
		if (pcmd->argval[0].uval == 0)
			associd = 0;
		else if ((associd = checkassocid(pcmd->argval[0].uval)) == 0)
			return;
	}

	res = doquerylist(g_varlist, CTL_OP_WRITEVAR, associd, 1, &rstatus,
			  &dsize, &datap);

	if (res != 0)
		return;

	if (numhosts > 1)
		(void) fprintf(fp, "server=%s ", currenthost);
	if (dsize == 0)
		(void) fprintf(fp, "done! (no data returned)\n");
	else {
		(void) fprintf(fp,"associd=%u ", associd);
		printvars(dsize, datap, (int)rstatus,
			  (associd != 0) ? TYPE_PEER : TYPE_SYS, 0, fp);
	}
	return;
}