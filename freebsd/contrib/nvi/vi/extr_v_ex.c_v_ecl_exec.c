#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int lno; int /*<<< orphan*/  ccl_parent; int /*<<< orphan*/  nextdisp; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BERR ; 
 int /*<<< orphan*/  SC_EXIT ; 
 int /*<<< orphan*/  VIM_EMPTY ; 
 scalar_t__ db_get (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ex_run_str (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v_emsg (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
v_ecl_exec(SCR *sp)
{
	size_t len;
	CHAR_T *p;

	if (db_get(sp, sp->lno, 0, &p, &len) && sp->lno == 1) {
		v_emsg(sp, NULL, VIM_EMPTY);
		return (1);
	}
	if (len == 0) {
		msgq(sp, M_BERR, "307|No ex command to execute");
		return (1);
	}
	
	/* Push the command on the command stack. */
	if (ex_run_str(sp, NULL, p, len, 0, 0))
		return (1);

	/* Set up the switch. */
	sp->nextdisp = sp->ccl_parent;
	F_SET(sp, SC_EXIT);
	return (0);
}