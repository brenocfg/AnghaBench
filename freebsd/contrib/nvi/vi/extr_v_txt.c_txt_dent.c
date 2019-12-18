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
typedef  size_t u_long ;
struct TYPE_4__ {size_t cno; char* lb; size_t ai; size_t offset; int /*<<< orphan*/  owrite; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 size_t COL_OFF (size_t,size_t) ; 
 size_t KEY_COL (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  O_SHIFTWIDTH ; 
 int /*<<< orphan*/  O_TABSTOP ; 
 size_t O_VAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txt_insch (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
txt_dent(SCR *sp, TEXT *tp, int isindent)
{
	CHAR_T ch;
	u_long sw, ts;
	size_t cno, current, spaces, target, tabs;
	int ai_reset;

	ts = O_VAL(sp, O_TABSTOP);
	sw = O_VAL(sp, O_SHIFTWIDTH);

	/*
	 * Since we don't know what precedes the character(s) being inserted
	 * (or deleted), the preceding whitespace characters must be resolved.
	 * An example is a <tab>, which doesn't need a full shiftwidth number
	 * of columns because it's preceded by <space>s.  This is easy to get
	 * if the user sets shiftwidth to a value less than tabstop (or worse,
	 * something for which tabstop isn't a multiple) and then uses ^T to
	 * indent, and ^D to outdent.
	 *
	 * Figure out the current and target screen columns.  In the historic
	 * vi, the autoindent column was NOT determined using display widths
	 * of characters as was the wrapmargin column.  For that reason, we
	 * can't use the vs_column() function, but have to calculate it here.
	 * This is slow, but it's normally only on the first few characters of
	 * a line.
	 */
	for (current = cno = 0; cno < tp->cno; ++cno)
		current += tp->lb[cno] == '\t' ?
		    COL_OFF(current, ts) : KEY_COL(sp, tp->lb[cno]);

	target = current;
	if (isindent)
		target += COL_OFF(target, sw);
	else {
		--target;
		target -= target % sw;
	}

	/*
	 * The AI characters will be turned into overwrite characters if the
	 * cursor immediately follows them.  We test both the cursor position
	 * and the indent flag because there's no single test.  (^T can only
	 * be detected by the cursor position, and while we know that the test
	 * is always true for ^D, the cursor can be in more than one place, as
	 * "0^D" and "^D" are different.)
	 */
	ai_reset = !isindent || tp->cno == tp->ai + tp->offset;

	/*
	 * Back up over any previous <blank> characters, changing them into
	 * overwrite characters (including any ai characters).  Then figure
	 * out the current screen column.
	 */
	for (; tp->cno > tp->offset &&
	    (tp->lb[tp->cno - 1] == ' ' || tp->lb[tp->cno - 1] == '\t');
	    --tp->cno, ++tp->owrite);
	for (current = cno = 0; cno < tp->cno; ++cno)
		current += tp->lb[cno] == '\t' ?
		    COL_OFF(current, ts) : KEY_COL(sp, tp->lb[cno]);

	/*
	 * If we didn't move up to or past the target, it's because there
	 * weren't enough characters to delete, e.g. the first character
	 * of the line was a tp->offset character, and the user entered
	 * ^D to move to the beginning of a line.  An example of this is:
	 *
	 *	:set ai sw=4<cr>i<space>a<esc>i^T^D
	 *
	 * Otherwise, count up the total spaces/tabs needed to get from the
	 * beginning of the line (or the last non-<blank> character) to the
	 * target.
	 */
	if (current >= target)
		spaces = tabs = 0;
	else {
		for (cno = current,
		    tabs = 0; cno + COL_OFF(cno, ts) <= target; ++tabs)
			cno += COL_OFF(cno, ts);
		spaces = target - cno;
	}

	/* If we overwrote ai characters, reset the ai count. */
	if (ai_reset)
		tp->ai = tabs + spaces;

	/*
	 * Call txt_insch() to insert each character, so that we get the
	 * correct effect when we add a <tab> to replace N <spaces>.
	 */
	for (ch = '\t'; tabs > 0; --tabs)
		(void)txt_insch(sp, tp, &ch, 0);
	for (ch = ' '; spaces > 0; --spaces)
		(void)txt_insch(sp, tp, &ch, 0);
	return (0);
}