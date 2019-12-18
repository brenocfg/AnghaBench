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
struct TYPE_3__ {size_t len; size_t ai; size_t cno; char* lb; scalar_t__ offset; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 size_t COL_OFF (size_t,size_t) ; 
 int /*<<< orphan*/  MEMMOVE (char*,char*,size_t) ; 
 int /*<<< orphan*/  O_TABSTOP ; 
 size_t O_VAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isblank (char) ; 

__attribute__((used)) static void
txt_ai_resolve(SCR *sp, TEXT *tp, int *changedp)
{
	u_long ts;
	int del;
	size_t cno, len, new, old, scno, spaces, tab_after_sp, tabs;
	CHAR_T *p;

	*changedp = 0;

	/*
	 * If the line is empty, has an offset, or no autoindent
	 * characters, we're done.
	 */
	if (!tp->len || tp->offset || !tp->ai)
		return;

	/*
	 * If the length is less than or equal to the autoindent
	 * characters, delete them.
	 */
	if (tp->len <= tp->ai) {
		tp->ai = tp->cno = tp->len = 0;
		return;
	}

	/*
	 * The autoindent characters plus any leading <blank> characters
	 * in the line are resolved into the minimum number of characters.
	 * Historic practice.
	 */
	ts = O_VAL(sp, O_TABSTOP);

	/* Figure out the last <blank> screen column. */
	for (p = tp->lb, scno = 0, len = tp->len,
	    spaces = tab_after_sp = 0; len-- && isblank(*p); ++p)
		if (*p == '\t') {
			if (spaces)
				tab_after_sp = 1;
			scno += COL_OFF(scno, ts);
		} else {
			++spaces;
			++scno;
		}

	/*
	 * If there are no spaces, or no tabs after spaces and less than
	 * ts spaces, it's already minimal.
	 */
	if (!spaces || (!tab_after_sp && spaces < ts))
		return;

	/* Count up spaces/tabs needed to get to the target. */
	for (cno = 0, tabs = 0; cno + COL_OFF(cno, ts) <= scno; ++tabs)
		cno += COL_OFF(cno, ts);
	spaces = scno - cno;

	/*
	 * Figure out how many characters we're dropping -- if we're not
	 * dropping any, it's already minimal, we're done.
	 */
	old = p - tp->lb;
	new = spaces + tabs;
	if (old == new)
		return;

	/* Shift the rest of the characters down, adjust the counts. */
	del = old - new;
	MEMMOVE(p - del, p, tp->len - old);
	tp->len -= del;
	tp->cno -= del;

	/* Fill in space/tab characters. */
	for (p = tp->lb; tabs--;)
		*p++ = '\t';
	while (spaces--)
		*p++ = ' ';
	*changedp = 1;
}