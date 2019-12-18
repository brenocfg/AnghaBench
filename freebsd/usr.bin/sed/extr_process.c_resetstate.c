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
struct TYPE_2__ {struct s_command* c; } ;
struct s_command {char code; scalar_t__ startline; scalar_t__ a2; struct s_command* next; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  REPLACE ; 
 int /*<<< orphan*/  cspace (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s_command* prog ; 

void
resetstate(void)
{
	struct s_command *cp;

	/*
	 * Reset all in-range markers.
	 */
	for (cp = prog; cp; cp = cp->code == '{' ? cp->u.c : cp->next)
		if (cp->a2)
			cp->startline = 0;

	/*
	 * Clear out the hold space.
	 */
	cspace(&HS, "", 0, REPLACE);
}