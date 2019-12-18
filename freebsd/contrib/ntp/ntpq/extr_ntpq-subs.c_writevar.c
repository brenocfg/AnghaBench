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
struct varlist {int dummy; } ;
struct parse {TYPE_1__* argval; } ;
typedef  scalar_t__ associd_t ;
struct TYPE_2__ {scalar_t__ uval; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_WRITEVAR ; 
 int MAXLIST ; 
 int TYPE_PEER ; 
 int TYPE_SYS ; 
 int /*<<< orphan*/  ZERO (struct varlist*) ; 
 scalar_t__ checkassocid (scalar_t__) ; 
 char* currenthost ; 
 int /*<<< orphan*/  doaddvlist (struct varlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doclearvlist (struct varlist*) ; 
 int doquerylist (struct varlist*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,size_t*,char const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int numhosts ; 
 int /*<<< orphan*/  printvars (size_t,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
writevar(
	struct parse *pcmd,
	FILE *fp
	)
{
	const char *datap;
	int res;
	associd_t associd;
	int type;
	size_t dsize;
	u_short rstatus;
	struct varlist tmplist[MAXLIST];

	/* HMS: uval? */
	if (pcmd->argval[0].uval == 0)
		associd = 0;
	else if ((associd = checkassocid(pcmd->argval[0].uval)) == 0)
		return;

	ZERO(tmplist);
	doaddvlist(tmplist, pcmd->argval[1].string);

	res = doquerylist(tmplist, CTL_OP_WRITEVAR, associd, 1, &rstatus,
			  &dsize, &datap);

	doclearvlist(tmplist);

	if (res != 0)
		return;

	if (numhosts > 1)
		fprintf(fp, "server=%s ", currenthost);
	if (dsize == 0)
		fprintf(fp, "done! (no data returned)\n");
	else {
		fprintf(fp,"associd=%u ", associd);
		type = (0 == associd)
			   ? TYPE_SYS
			   : TYPE_PEER;
		printvars(dsize, datap, (int)rstatus, type, 0, fp);
	}
	return;
}