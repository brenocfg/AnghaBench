#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* frp; TYPE_1__* gp; } ;
struct TYPE_14__ {int /*<<< orphan*/ * name; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* scr_rename ) (TYPE_3__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_3__ SCR ;
typedef  int /*<<< orphan*/  EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_SHELL ; 
 int /*<<< orphan*/  O_STR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EX_WAIT_NO ; 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int ex_exec_proc (TYPE_3__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msgq (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ opts_empty (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

int
ex_shell(SCR *sp, EXCMD *cmdp)
{
	int rval;
	char *buf;

	/* We'll need a shell. */
	if (opts_empty(sp, O_SHELL, 0))
		return (1);

	/*
	 * XXX
	 * Assumes all shells use -i.
	 */
	(void)asprintf(&buf, "%s -i", O_STR(sp, O_SHELL));
	if (buf == NULL) {
		msgq(sp, M_SYSERR, NULL);
		return (1);
	}

	/* Restore the window name. */
	(void)sp->gp->scr_rename(sp, NULL, 0);

	/* If we're still in a vi screen, move out explicitly. */
	rval = ex_exec_proc(sp, cmdp, buf, NULL, !F_ISSET(sp, SC_SCR_EXWROTE));
	free(buf);

	/* Set the window name. */
	(void)sp->gp->scr_rename(sp, sp->frp->name, 1);

	/*
	 * !!!
	 * Historically, vi didn't require a continue message after the
	 * return of the shell.  Match it.
	 */
	F_SET(sp, SC_EX_WAIT_NO);

	return (rval);
}