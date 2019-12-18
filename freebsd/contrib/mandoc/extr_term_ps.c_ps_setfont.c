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
struct termp {scalar_t__ type; TYPE_1__* ps; } ;
typedef  enum termfont { ____Placeholder_termfont } termfont ;
struct TYPE_2__ {int lastf; int flags; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int PS_NEWPAGE ; 
 int TERMFONT__MAX ; 
 scalar_t__ TERMTYPE_PS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ps_printf (struct termp*,char*,int,...) ; 

__attribute__((used)) static void
ps_setfont(struct termp *p, enum termfont f)
{

	assert(f < TERMFONT__MAX);
	p->ps->lastf = f;

	/*
	 * If we're still at the top of the page, let the font-setting
	 * be delayed until we actually have stuff to print.
	 */

	if (PS_NEWPAGE & p->ps->flags)
		return;

	if (TERMTYPE_PS == p->type)
		ps_printf(p, "f%d\n", (int)f);
	else
		ps_printf(p, "/F%d %zu Tf\n",
		    (int)f, p->ps->scale);
}