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
struct cmdnames {int cnt; TYPE_1__** names; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void exclude_cmds(struct cmdnames *cmds, struct cmdnames *excludes)
{
	int ci, cj, ei;
	int cmp;

	ci = cj = ei = 0;
	while (ci < cmds->cnt && ei < excludes->cnt) {
		cmp = strcmp(cmds->names[ci]->name, excludes->names[ei]->name);
		if (cmp < 0)
			cmds->names[cj++] = cmds->names[ci++];
		else if (cmp == 0) {
			ei++;
			free(cmds->names[ci++]);
		} else if (cmp > 0)
			ei++;
	}

	while (ci < cmds->cnt)
		cmds->names[cj++] = cmds->names[ci++];

	cmds->cnt = cj;
}