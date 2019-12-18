#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ prog_t ;

/* Variables and functions */
 TYPE_1__* progs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

prog_t *find_prog(char *str)
{
	prog_t *p;

	for (p = progs; p != NULL; p = p->next)
		if (!strcmp(p->name, str))
			return p;

	return NULL;
}