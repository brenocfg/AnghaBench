#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VICMD ;
struct TYPE_19__ {int /*<<< orphan*/  ccnt; int /*<<< orphan*/  tiq; int /*<<< orphan*/ * gp; } ;
struct TYPE_18__ {scalar_t__ term; int len; int /*<<< orphan*/  lb; } ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  GS ;

/* Variables and functions */
 int /*<<< orphan*/  EXCMD_RUNNING (int /*<<< orphan*/ *) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_CEDIT ; 
 int /*<<< orphan*/ * O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EX_WAIT_NO ; 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 scalar_t__ TERM_BS ; 
 scalar_t__ TERM_CEDIT ; 
 scalar_t__ TERM_OK ; 
 int TXT_BS ; 
 int TXT_CEDIT ; 
 int TXT_FILEC ; 
 int TXT_PROMPT ; 
 int /*<<< orphan*/  ex_cmd (TYPE_2__*) ; 
 int /*<<< orphan*/  ex_fflush (TYPE_2__*) ; 
 scalar_t__ ex_run_str (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int v_ecl (TYPE_2__*) ; 
 scalar_t__ v_ecl_log (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ v_ex_done (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ v_tcmd (TYPE_2__*,int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ vs_ex_resolve (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  vs_home (TYPE_2__*) ; 

int
v_ex(SCR *sp, VICMD *vp)
{
	GS *gp;
	TEXT *tp;
	int do_cedit, do_resolution, ifcontinue;

	gp = sp->gp;

	/*
	 * !!!
	 * If we put out more than a single line of messages, or ex trashes
	 * the screen, the user may continue entering ex commands.  We find
	 * this out when we do the screen/message resolution.  We can't enter
	 * completely into ex mode however, because the user can elect to
	 * return into vi mode by entering any key, i.e. we have to be in raw
	 * mode.
	 */
	for (do_cedit = do_resolution = 0;;) {
		/*
		 * !!!
		 * There may already be an ex command waiting to run.  If
		 * so, we continue with it.
		 */
		if (!EXCMD_RUNNING(gp)) {
			/* Get a command. */
			if (v_tcmd(sp, vp, ':',
			    TXT_BS | TXT_CEDIT | TXT_FILEC | TXT_PROMPT))
				return (1);
			tp = TAILQ_FIRST(sp->tiq);

			/*
			 * If the user entered a single <esc>, they want to
			 * edit their colon command history.  If they already
			 * entered some text, move it into the edit history.
			 */
			if (tp->term == TERM_CEDIT) {
				if (tp->len > 1 && v_ecl_log(sp, tp))
					return (1);
				do_cedit = 1;
				break;
			}

			/* If the user didn't enter anything, return. */
			if (tp->term == TERM_BS)
				break;

			/* If the user changed their mind, return. */
			if (tp->term != TERM_OK)
				break;

			/* Log the command. */
			if (O_STR(sp, O_CEDIT) != NULL && v_ecl_log(sp, tp))
				return (1);

			/* Push a command on the command stack. */
			if (ex_run_str(sp, NULL, tp->lb, tp->len, 0, 1))
				return (1);
		}

		/* Home the cursor. */
		vs_home(sp);

		/*
		 * !!!
		 * If the editor wrote the screen behind curses back, put out
		 * a <newline> so that we don't overwrite the user's command
		 * with its output or the next want-to-continue? message.  This
		 * doesn't belong here, but I can't find another place to put
		 * it.  See, we resolved the output from the last ex command,
		 * and the user entered another one.  This is the only place
		 * where we have control before the ex command writes output.
		 * We could get control in vs_msg(), but we have no way to know
		 * if command didn't put out any output when we try and resolve
		 * this command.  This fixes a bug where combinations of ex
		 * commands, e.g. ":set<CR>:!date<CR>:set" didn't look right.
		 */
		if (F_ISSET(sp, SC_SCR_EXWROTE))
			(void)putchar('\n');

		/* Call the ex parser. */
		(void)ex_cmd(sp);

		/* Flush ex messages. */
		(void)ex_fflush(sp);

		/* Resolve any messages. */
		if (vs_ex_resolve(sp, &ifcontinue))
			return (1);

		/*
		 * Continue or return.  If continuing, make sure that we
		 * eventually do resolution.
		 */
		if (!ifcontinue)
			break;
		do_resolution = 1;

		/* If we're continuing, it's a new command. */
		++sp->ccnt;
	}

	/*
	 * If the user previously continued an ex command, we have to do
	 * resolution to clean up the screen.  Don't wait, we already did
	 * that.
	 */
	if (do_resolution) {
		F_SET(sp, SC_EX_WAIT_NO);
		if (vs_ex_resolve(sp, &ifcontinue))
			return (1);
	}

	/* Cleanup from the ex command. */
	if (v_ex_done(sp, vp))
		return (1);

	/* The user may want to edit their colon command history. */
	if (do_cedit)
		return (v_ecl(sp));

	return (0);
}