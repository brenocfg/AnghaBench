#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_5__ {size_t cols; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 size_t CHLEN (size_t) ; 
 int O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 int /*<<< orphan*/  O_LIST ; 
 int /*<<< orphan*/  TAB_RESET ; 
 int /*<<< orphan*/  db_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 

size_t
vs_colpos(SCR *sp, recno_t lno, size_t cno)
{
	size_t chlen, curoff, len, llen, off, scno;
	int ch = 0, leftright, listset;
	CHAR_T *lp, *p;

	/* Need the line to go any further. */
	(void)db_get(sp, lno, 0, &lp, &llen);

	/* Missing or empty lines are easy. */
	if (lp == NULL || llen == 0)
		return (0);

	/* Store away the values of the list and leftright edit options. */
	listset = O_ISSET(sp, O_LIST);
	leftright = O_ISSET(sp, O_LEFTRIGHT);

	/* Discard screen (logical) lines. */
	off = cno / sp->cols;
	cno %= sp->cols;
	for (scno = 0, p = lp, len = llen; off--;) {
		for (; len && scno < sp->cols; --len)
			scno += CHLEN(scno);

		/*
		 * If reached the end of the physical line, return the last
		 * physical character in the line.
		 */
		if (len == 0)
			return (llen - 1);

		/*
		 * If folding screens (the historic vi screen format), past
		 * the end of the current screen, and the character was a tab,
		 * reset the current screen column to 0.  Otherwise, the rest
		 * of the character is displayed in the next screen.
		 */
		if (leftright && ch == '\t')
			scno = 0;
		else
			scno -= sp->cols;
	}

	/* Step through the line until reach the right character or EOL. */
	for (curoff = scno; len--;) {
		chlen = CHLEN(curoff);

		/*
		 * If we've reached the specific character, there are three
		 * cases.
		 *
		 * 1: scno == cno, i.e. the current character ends at the
		 *    screen character we care about.
		 *	a: off < llen - 1, i.e. not the last character in
		 *	   the line, return the offset of the next character.
		 *	b: else return the offset of the last character.
		 * 2: scno != cno, i.e. this character overruns the character
		 *    we care about, return the offset of this character.
		 */
		if ((scno += chlen) >= cno) {
			off = p - lp;
			return (scno == cno ?
			    (off < llen - 1 ? off : llen - 1) : off - 1);
		}

		TAB_RESET;
	}

	/* No such character; return the start of the last character. */
	return (llen - 1);
}