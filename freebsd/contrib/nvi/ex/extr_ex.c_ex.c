#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_25__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_33__ {struct TYPE_33__* buf; int /*<<< orphan*/  len; int /*<<< orphan*/  mtype; } ;
struct TYPE_31__ {int if_lno; char* if_name; int clen; int /*<<< orphan*/  cp; } ;
struct TYPE_32__ {TYPE_25__ excmd; int /*<<< orphan*/  tiq; int /*<<< orphan*/  lno; int /*<<< orphan*/  msgq; int /*<<< orphan*/  (* scr_msg ) (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;struct TYPE_32__* gp; } ;
struct TYPE_30__ {int len; int /*<<< orphan*/  lb; } ;
typedef  TYPE_1__ TEXT ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ MSGS ;
typedef  TYPE_2__ GS ;
typedef  int /*<<< orphan*/  EX_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_EX_PARSER (TYPE_25__*) ; 
 int /*<<< orphan*/  CLR_INTERRUPT (TYPE_2__*) ; 
 int /*<<< orphan*/ * EXP (TYPE_2__*) ; 
 int /*<<< orphan*/  E_NRSEP ; 
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int) ; 
 int /*<<< orphan*/  F_INIT (TYPE_25__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int) ; 
 int G_SCRIPTED ; 
 int G_SRESTART ; 
 scalar_t__ INTERRUPTED (TYPE_2__*) ; 
 int /*<<< orphan*/  L (char*) ; 
 int /*<<< orphan*/  LF_INIT (int) ; 
 int /*<<< orphan*/  LF_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  O_BEAUTIFY ; 
 scalar_t__ O_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_PROMPT ; 
 int SC_EXIT ; 
 int SC_EXIT_FORCE ; 
 int SC_EX_SILENT ; 
 int SC_FSWITCH ; 
 int SC_SSWITCH ; 
 int SC_STATUS ; 
 int SC_VI ; 
 TYPE_3__* SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int TXT_BACKSLASH ; 
 int /*<<< orphan*/  TXT_BEAUTIFY ; 
 int TXT_CNTRLD ; 
 int TXT_CR ; 
 int /*<<< orphan*/  TXT_PROMPT ; 
 scalar_t__ ex_cmd (TYPE_2__*) ; 
 int /*<<< orphan*/  ex_fflush (TYPE_2__*) ; 
 scalar_t__ ex_init (TYPE_2__*) ; 
 int /*<<< orphan*/  ex_puts (TYPE_2__*,char*) ; 
 scalar_t__ ex_txt (TYPE_2__*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 scalar_t__ file_end (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_status (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q ; 
 int screen_end (TYPE_2__*) ; 
 TYPE_2__* screen_next (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
ex(SCR **spp)
{
	EX_PRIVATE *exp;
	GS *gp;
	MSGS *mp;
	SCR *sp;
	TEXT *tp;
	u_int32_t flags;

	sp = *spp;
	gp = sp->gp;
	exp = EXP(sp);

	/* Start the ex screen. */
	if (ex_init(sp))
		return (1);

	/* Flush any saved messages. */
	while ((mp = SLIST_FIRST(gp->msgq)) != NULL) {
		gp->scr_msg(sp, mp->mtype, mp->buf, mp->len);
		SLIST_REMOVE_HEAD(gp->msgq, q);
		free(mp->buf);
		free(mp);
	}

	/* If reading from a file, errors should have name and line info. */
	if (F_ISSET(gp, G_SCRIPTED)) {
		gp->excmd.if_lno = 1;
		gp->excmd.if_name = "script";
	}

	/*
	 * !!!
	 * Initialize the text flags.  The beautify edit option historically
	 * applied to ex command input read from a file.  In addition, the
	 * first time a ^H was discarded from the input, there was a message,
	 * "^H discarded", that was displayed.  We don't bother.
	 */
	LF_INIT(TXT_BACKSLASH | TXT_CNTRLD | TXT_CR);
	for (;; ++gp->excmd.if_lno) {
		/* Display status line and flush. */
		if (F_ISSET(sp, SC_STATUS)) {
			if (!F_ISSET(sp, SC_EX_SILENT))
				msgq_status(sp, sp->lno, 0);
			F_CLR(sp, SC_STATUS);
		}
		(void)ex_fflush(sp);

		/* Set the flags the user can reset. */
		if (O_ISSET(sp, O_BEAUTIFY))
			LF_SET(TXT_BEAUTIFY);
		if (O_ISSET(sp, O_PROMPT))
			LF_SET(TXT_PROMPT);

		/* Clear any current interrupts, and get a command. */
		CLR_INTERRUPT(sp);
		if (ex_txt(sp, sp->tiq, ':', flags))
			return (1);
		if (INTERRUPTED(sp)) {
			(void)ex_puts(sp, "\n");
			(void)ex_fflush(sp);
			continue;
		}

		/* Initialize the command structure. */
		CLEAR_EX_PARSER(&gp->excmd);

		/*
		 * If the user entered a single carriage return, send
		 * ex_cmd() a separator -- it discards single newlines.
		 */
		tp = TAILQ_FIRST(sp->tiq);
		if (tp->len == 0) {
			gp->excmd.cp = L(" ");	/* __TK__ why not |? */
			gp->excmd.clen = 1;
		} else {
			gp->excmd.cp = tp->lb;
			gp->excmd.clen = tp->len;
		}
		F_INIT(&gp->excmd, E_NRSEP);

		if (ex_cmd(sp) && F_ISSET(gp, G_SCRIPTED))
			return (1);

		if (INTERRUPTED(sp)) {
			CLR_INTERRUPT(sp);
			msgq(sp, M_ERR, "170|Interrupted");
		}

		/*
		 * If the last command caused a restart, or switched screens
		 * or into vi, return.
		 */
		if (F_ISSET(gp, G_SRESTART) || F_ISSET(sp, SC_SSWITCH | SC_VI)) {
			*spp = sp;
			break;
		}

		/* If the last command switched files, we don't care. */
		F_CLR(sp, SC_FSWITCH);

		/*
		 * If we're exiting this screen, move to the next one.  By
		 * definition, this means returning into vi, so return to the
		 * main editor loop.  The ordering is careful, don't discard
		 * the contents of sp until the end.
		 */
		if (F_ISSET(sp, SC_EXIT | SC_EXIT_FORCE)) {
			if (file_end(sp, NULL, F_ISSET(sp, SC_EXIT_FORCE)))
				return (1);
			*spp = screen_next(sp);
			return (screen_end(sp));
		}
	}
	return (0);
}