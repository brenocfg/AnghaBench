#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
struct TYPE_3__ {size_t len; char* lb; size_t ai; int /*<<< orphan*/  lb_len; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  BINC_RETW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t) ; 
 size_t COL_OFF (size_t,size_t) ; 
 int /*<<< orphan*/  O_SHIFTWIDTH ; 
 int /*<<< orphan*/  O_TABSTOP ; 
 size_t O_VAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_dent(SCR *sp, TEXT *tp)
{
	u_long sw, ts;
	size_t cno, off, scno, spaces, tabs;

	ts = O_VAL(sp, O_TABSTOP);
	sw = O_VAL(sp, O_SHIFTWIDTH);

	/* Get the current screen column. */
	for (off = scno = 0; off < tp->len; ++off)
		if (tp->lb[off] == '\t')
			scno += COL_OFF(scno, ts);
		else
			++scno;

	/* Get the previous shiftwidth column. */
	cno = scno--;
	scno -= scno % sw;

	/*
	 * Since we don't know what comes before the character(s) being
	 * deleted, we have to resolve the autoindent characters .  The
	 * example is a <tab>, which doesn't take up a full shiftwidth
	 * number of columns because it's preceded by <space>s.  This is
	 * easy to get if the user sets shiftwidth to a value less than
	 * tabstop, and then uses ^T to indent, and ^D to outdent.
	 *
	 * Count up spaces/tabs needed to get to the target.
	 */
	for (cno = 0, tabs = 0; cno + COL_OFF(cno, ts) <= scno; ++tabs)
		cno += COL_OFF(cno, ts);
	spaces = scno - cno;

	/* Make sure there's enough room. */
	BINC_RETW(sp, tp->lb, tp->lb_len, tabs + spaces + 1);

	/* Adjust the final ai character count. */
	tp->ai = tabs + spaces;

	/* Enter the replacement characters. */
	for (tp->len = 0; tabs > 0; --tabs)
		tp->lb[tp->len++] = '\t';
	for (; spaces > 0; --spaces)
		tp->lb[tp->len++] = ' ';
	return (0);
}