#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct varlist {int dummy; } ;
struct parse {int nargs; TYPE_1__* argval; } ;
struct TYPE_4__ {int /*<<< orphan*/  assid; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; int /*<<< orphan*/  uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READVAR ; 
 int MAXLIST ; 
 int /*<<< orphan*/  TYPE_PEER ; 
 int /*<<< orphan*/  ZERO (struct varlist*) ; 
 TYPE_2__* assoc_cache ; 
 int /*<<< orphan*/  doaddvlist (struct varlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doclearvlist (struct varlist*) ; 
 int /*<<< orphan*/  dolist (struct varlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  findassidrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 struct varlist* g_varlist ; 

__attribute__((used)) static void
mreadvar(
	struct parse *pcmd,
	FILE *fp
	)
{
	int i;
	int from;
	int to;
	struct varlist tmplist[MAXLIST];
	struct varlist *pvars;

	if (!findassidrange(pcmd->argval[0].uval, pcmd->argval[1].uval,
				&from, &to, fp))
		return;

	ZERO(tmplist);
	if (pcmd->nargs >= 3) {
		doaddvlist(tmplist, pcmd->argval[2].string);
		pvars = tmplist;
	} else {
		pvars = g_varlist;
	}

	for (i = from; i <= to; i++) {
		if (!dolist(pvars, assoc_cache[i].assid, CTL_OP_READVAR,
			    TYPE_PEER, fp))
			break;
	}

	if (pvars == tmplist)
		doclearvlist(tmplist);

	return;
}