#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_23__ {TYPE_1__* cmd; } ;
struct TYPE_22__ {int /*<<< orphan*/  (* scr_child ) (TYPE_2__*) ;int /*<<< orphan*/  (* scr_attr ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* scr_screen ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_21__ {TYPE_3__* gp; } ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ GS ;
typedef  TYPE_4__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_NOCANON ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_SHELL ; 
 char* O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_ALTERNATE ; 
 int /*<<< orphan*/  SC_EX ; 
 int SC_SCR_EX ; 
 int SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  SC_VI ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  ex_fflush (TYPE_2__*) ; 
 int /*<<< orphan*/  ex_puts (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  ex_wemsg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_str (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ opts_empty (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int proc_wait (TYPE_2__*,long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 scalar_t__ vfork () ; 

int
ex_exec_proc(SCR *sp, EXCMD *cmdp, char *cmd, const char *msg, int need_newline)
{
	GS *gp;
	const char *name;
	pid_t pid;

	gp = sp->gp;

	/* We'll need a shell. */
	if (opts_empty(sp, O_SHELL, 0))
		return (1);

	/* Enter ex mode. */
	if (F_ISSET(sp, SC_VI)) {
		if (gp->scr_screen(sp, SC_EX)) {
			ex_wemsg(sp, cmdp->cmd->name, EXM_NOCANON);
			return (1);
		}
		(void)gp->scr_attr(sp, SA_ALTERNATE, 0);
		F_SET(sp, SC_SCR_EX | SC_SCR_EXWROTE);
	}

	/* Put out additional newline, message. */
	if (need_newline)
		(void)ex_puts(sp, "\n");
	if (msg != NULL) {
		(void)ex_puts(sp, msg);
		(void)ex_puts(sp, "\n");
	}
	(void)ex_fflush(sp);

	switch (pid = vfork()) {
	case -1:			/* Error. */
		msgq(sp, M_SYSERR, "vfork");
		return (1);
	case 0:				/* Utility. */
		if (gp->scr_child)
			gp->scr_child(sp);
		if ((name = strrchr(O_STR(sp, O_SHELL), '/')) == NULL)
			name = O_STR(sp, O_SHELL);
		else
			++name;
		execl(O_STR(sp, O_SHELL), name, "-c", cmd, (char *)NULL);
		msgq_str(sp, M_SYSERR, O_STR(sp, O_SHELL), "execl: %s");
		_exit(127);
		/* NOTREACHED */
	default:			/* Parent. */
		return (proc_wait(sp, (long)pid, cmd, 0, 0));
	}
	/* NOTREACHED */
}