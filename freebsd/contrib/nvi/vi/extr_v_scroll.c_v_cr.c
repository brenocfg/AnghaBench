#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lno; } ;
struct TYPE_6__ {TYPE_1__ m_start; } ;
typedef  TYPE_2__ VICMD ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_COMEDIT ; 
 int /*<<< orphan*/  SC_SCRIPT ; 
 int sscr_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int v_down (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int v_ecl_exec (int /*<<< orphan*/ *) ; 

int
v_cr(SCR *sp, VICMD *vp)
{
	/* If it's a colon command-line edit window, it's an ex command. */
	if (F_ISSET(sp, SC_COMEDIT))
		return (v_ecl_exec(sp));

	/* If it's a script window, exec the line. */
	if (F_ISSET(sp, SC_SCRIPT))
		return (sscr_exec(sp, vp->m_start.lno));

	/* Otherwise, it's the same as v_down(). */
	return (v_down(sp, vp));
}