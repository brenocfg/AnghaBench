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
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int is_in_cmdlist(struct cmdnames *c, const char *s)
{
	int i;
	for (i = 0; i < c->cnt; i++)
		if (!strcmp(s, c->names[i]->name))
			return 1;
	return 0;
}