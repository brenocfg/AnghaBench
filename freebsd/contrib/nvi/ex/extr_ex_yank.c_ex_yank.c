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
struct TYPE_4__ {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  buffer; int /*<<< orphan*/  iflags; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  CUT_LINEMODE ; 
 int /*<<< orphan*/  E_C_BUFFER ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cut (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ex_yank(SCR *sp, EXCMD *cmdp)
{
	NEEDFILE(sp, cmdp);

	/*
	 * !!!
	 * Historically, yanking lines in ex didn't count toward the
	 * number-of-lines-yanked report.
	 */
	return (cut(sp,
	    FL_ISSET(cmdp->iflags, E_C_BUFFER) ? &cmdp->buffer : NULL,
	    &cmdp->addr1, &cmdp->addr2, CUT_LINEMODE));
}