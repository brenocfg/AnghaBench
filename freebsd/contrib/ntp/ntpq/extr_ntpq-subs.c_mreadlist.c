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
struct parse {TYPE_1__* argval; } ;
struct TYPE_4__ {int /*<<< orphan*/  assid; } ;
struct TYPE_3__ {int /*<<< orphan*/  uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_READVAR ; 
 int /*<<< orphan*/  TYPE_PEER ; 
 TYPE_2__* assoc_cache ; 
 int /*<<< orphan*/  dolist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  findassidrange (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_varlist ; 

__attribute__((used)) static void
mreadlist(
	struct parse *pcmd,
	FILE *fp
	)
{
	int i;
	int from;
	int to;

	if (!findassidrange(pcmd->argval[0].uval, pcmd->argval[1].uval,
			    &from, &to, fp))
		return;

	for (i = from; i <= to; i++) {
		if (i != from)
			fprintf(fp, "\n");
		if (!dolist(g_varlist, assoc_cache[i].assid,
			    CTL_OP_READVAR, TYPE_PEER, fp))
			return;
	}
	return;
}