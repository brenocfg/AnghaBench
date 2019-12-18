#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_19__ {int lno; } ;
struct TYPE_22__ {int /*<<< orphan*/  iflags; int /*<<< orphan*/  count; TYPE_1__ addr1; } ;
struct TYPE_21__ {int lno; TYPE_2__* ep; int /*<<< orphan*/  refcnt; struct TYPE_21__* frp; int /*<<< orphan*/  cno; } ;
struct TYPE_20__ {int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ EXCMD ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (TYPE_3__*,char*,size_t,int /*<<< orphan*/ *,size_t) ; 
 int CH_NOMAP ; 
 int CH_QUOTED ; 
#define  E_C_CARAT 134 
 int E_C_COUNT ; 
#define  E_C_DASH 133 
#define  E_C_DOT 132 
#define  E_C_HASH 131 
#define  E_C_LIST 130 
#define  E_C_PLUS 129 
#define  E_C_PRINT 128 
 int FL_ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FR_CURSORSET ; 
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  O_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LIST ; 
 int /*<<< orphan*/  O_NUMBER ; 
 int /*<<< orphan*/  O_OPEN ; 
 int /*<<< orphan*/  O_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int SC_EX ; 
 int /*<<< orphan*/  SC_EX_GLOBAL ; 
 int /*<<< orphan*/  SC_EX_WAIT_NO ; 
 int SC_SCR_EX ; 
 int /*<<< orphan*/  SC_SCR_EXWROTE ; 
 int /*<<< orphan*/  SC_VI ; 
 scalar_t__ ex_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ex_puts (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msgq (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nonblank (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 size_t snprintf (char*,int,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  v_event_push (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 scalar_t__ vi (TYPE_3__**) ; 

int
ex_visual(SCR *sp, EXCMD *cmdp)
{
	SCR *tsp;
	size_t len;
	int pos;
	char buf[256];
	size_t wlen;
	CHAR_T *wp;

	/* If open option off, disallow visual command. */
	if (!O_ISSET(sp, O_OPEN)) {
		msgq(sp, M_ERR,
	    "175|The visual command requires that the open option be set");
		return (1);
	}

	/* Move to the address. */
	sp->lno = cmdp->addr1.lno == 0 ? 1 : cmdp->addr1.lno;

	/*
	 * Push a command based on the line position flags.  If no
	 * flag specified, the line goes at the top of the screen.
	 */
	switch (FL_ISSET(cmdp->iflags,
	    E_C_CARAT | E_C_DASH | E_C_DOT | E_C_PLUS)) {
	case E_C_CARAT:
		pos = '^';
		break;
	case E_C_DASH:
		pos = '-';
		break;
	case E_C_DOT:
		pos = '.';
		break;
	case E_C_PLUS:
		pos = '+';
		break;
	default:
		sp->frp->lno = sp->lno;
		sp->frp->cno = 0;
		(void)nonblank(sp, sp->lno, &sp->cno);
		F_SET(sp->frp, FR_CURSORSET);
		goto nopush;
	}

	if (FL_ISSET(cmdp->iflags, E_C_COUNT))
		len = snprintf(buf, sizeof(buf),
		     "%luz%c%lu", (u_long)sp->lno, pos, cmdp->count);
	else
		len = snprintf(buf, sizeof(buf), "%luz%c", (u_long)sp->lno, pos);
	CHAR2INT(sp, buf, len, wp, wlen);
	(void)v_event_push(sp, NULL, wp, wlen, CH_NOMAP | CH_QUOTED);

	/*
	 * !!!
	 * Historically, if no line address was specified, the [p#l] flags
	 * caused the cursor to be moved to the last line of the file, which
	 * was then positioned as described above.  This seems useless, so
	 * I haven't implemented it.
	 */
	switch (FL_ISSET(cmdp->iflags, E_C_HASH | E_C_LIST | E_C_PRINT)) {
	case E_C_HASH:
		O_SET(sp, O_NUMBER);
		break;
	case E_C_LIST:
		O_SET(sp, O_LIST);
		break;
	case E_C_PRINT:
		break;
	}

nopush:	/*
	 * !!!
	 * You can call the visual part of the editor from within an ex
	 * global command.
	 *
	 * XXX
	 * Historically, undoing a visual session was a single undo command,
	 * i.e. you could undo all of the changes you made in visual mode.
	 * We don't get this right; I'm waiting for the new logging code to
	 * be available.
	 *
	 * It's explicit, don't have to wait for the user, unless there's
	 * already a reason to wait.
	 */
	if (!F_ISSET(sp, SC_SCR_EXWROTE))
		F_SET(sp, SC_EX_WAIT_NO);

	if (F_ISSET(sp, SC_EX_GLOBAL)) {
		/*
		 * When the vi screen(s) exit, we don't want to lose our hold
		 * on this screen or this file, otherwise we're going to fail
		 * fairly spectacularly.
		 */
		++sp->refcnt;
		++sp->ep->refcnt;
		/* XXXX where is this decremented ? */

		/*
		 * Fake up a screen pointer -- vi doesn't get to change our
		 * underlying file, regardless.
		 */
		tsp = sp;
		if (vi(&tsp))
			return (1);

		/*
		 * !!!
		 * Historically, if the user exited the vi screen(s) using an
		 * ex quit command (e.g. :wq, :q) ex/vi exited, it was only if
		 * they exited vi using the Q command that ex continued.  Some
		 * early versions of nvi continued in ex regardless, but users
		 * didn't like the semantic.
		 *
		 * Reset the screen.
		 */
		if (ex_init(sp))
			return (1);

		/* Move out of the vi screen. */
		(void)ex_puts(sp, "\n");
	} else {
		F_CLR(sp, SC_EX | SC_SCR_EX);
		F_SET(sp, SC_VI);
	}
	return (0);
}