#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
struct TYPE_19__ {int lno; } ;
struct TYPE_18__ {int lno; } ;
struct TYPE_22__ {int count; TYPE_2__ addr2; TYPE_1__ addr1; int /*<<< orphan*/  iflags; } ;
struct TYPE_21__ {int lno; int /*<<< orphan*/  cno; } ;
struct TYPE_20__ {int lno; int /*<<< orphan*/  cno; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ MARK ;
typedef  TYPE_5__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  ABSMARK1 ; 
 int /*<<< orphan*/  E_ADDR_DEF ; 
#define  E_C_CARAT 132 
 int E_C_COUNT ; 
#define  E_C_DASH 131 
#define  E_C_DOT 130 
#define  E_C_EQUAL 129 
#define  E_C_PLUS 128 
 int FL_ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F_ISSET (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_3__*,TYPE_5__*) ; 
 int O_VAL (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_WINDOW ; 
 scalar_t__ db_last (TYPE_3__*,int*) ; 
 scalar_t__ ex_pr (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ex_puts (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mark_set (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 

int
ex_z(SCR *sp, EXCMD *cmdp)
{
	MARK abs;
	recno_t cnt, equals, lno;
	int eofcheck;

	NEEDFILE(sp, cmdp);

	/*
	 * !!!
	 * If no count specified, use either two times the size of the
	 * scrolling region, or the size of the window option.  POSIX
	 * 1003.2 claims that the latter is correct, but historic ex/vi
	 * documentation and practice appear to use the scrolling region.
	 * I'm using the window size as it means that the entire screen
	 * is used instead of losing a line to roundoff.  Note, we drop
	 * a line from the cnt if using the window size to leave room for
	 * the next ex prompt.
	 */
	if (FL_ISSET(cmdp->iflags, E_C_COUNT))
		cnt = cmdp->count;
	else
		cnt = O_VAL(sp, O_WINDOW) - 1;

	equals = 0;
	eofcheck = 0;
	lno = cmdp->addr1.lno;

	switch (FL_ISSET(cmdp->iflags,
	    E_C_CARAT | E_C_DASH | E_C_DOT | E_C_EQUAL | E_C_PLUS)) {
	case E_C_CARAT:		/* Display cnt * 2 before the line. */
		eofcheck = 1;
		if (lno > cnt * 2)
			cmdp->addr1.lno = (lno - cnt * 2) + 1;
		else
			cmdp->addr1.lno = 1;
		cmdp->addr2.lno = (cmdp->addr1.lno + cnt) - 1;
		break;
	case E_C_DASH:		/* Line goes at the bottom of the screen. */
		cmdp->addr1.lno = lno > cnt ? (lno - cnt) + 1 : 1;
		cmdp->addr2.lno = lno;
		break;
	case E_C_DOT:		/* Line goes in the middle of the screen. */
		/*
		 * !!!
		 * Historically, the "middleness" of the line overrode the
		 * count, so that "3z.19" or "3z.20" would display the first
		 * 12 lines of the file, i.e. (N - 1) / 2 lines before and
		 * after the specified line.
		 */
		eofcheck = 1;
		cnt = (cnt - 1) / 2;
		cmdp->addr1.lno = lno > cnt ? lno - cnt : 1;
		cmdp->addr2.lno = lno + cnt;

		/*
		 * !!!
		 * Historically, z. set the absolute cursor mark.
		 */
		abs.lno = sp->lno;
		abs.cno = sp->cno;
		(void)mark_set(sp, ABSMARK1, &abs, 1);
		break;
	case E_C_EQUAL:		/* Center with hyphens. */
		/*
		 * !!!
		 * Strangeness.  The '=' flag is like the '.' flag (see the
		 * above comment, it applies here as well) but with a special
		 * little hack.  Print out lines of hyphens before and after
		 * the specified line.  Additionally, the cursor remains set
		 * on that line.
		 */
		eofcheck = 1;
		cnt = (cnt - 1) / 2;
		cmdp->addr1.lno = lno > cnt ? lno - cnt : 1;
		cmdp->addr2.lno = lno - 1;
		if (ex_pr(sp, cmdp))
			return (1);
		(void)ex_puts(sp, "----------------------------------------\n");
		cmdp->addr2.lno = cmdp->addr1.lno = equals = lno;
		if (ex_pr(sp, cmdp))
			return (1);
		(void)ex_puts(sp, "----------------------------------------\n");
		cmdp->addr1.lno = lno + 1;
		cmdp->addr2.lno = (lno + cnt) - 1;
		break;
	default:
		/* If no line specified, move to the next one. */
		if (F_ISSET(cmdp, E_ADDR_DEF))
			++lno;
		/* FALLTHROUGH */
	case E_C_PLUS:		/* Line goes at the top of the screen. */
		eofcheck = 1;
		cmdp->addr1.lno = lno;
		cmdp->addr2.lno = (lno + cnt) - 1;
		break;
	}

	if (eofcheck) {
		if (db_last(sp, &lno))
			return (1);
		if (cmdp->addr2.lno > lno)
			cmdp->addr2.lno = lno;
	}

	if (ex_pr(sp, cmdp))
		return (1);
	if (equals)
		sp->lno = equals;
	return (0);
}