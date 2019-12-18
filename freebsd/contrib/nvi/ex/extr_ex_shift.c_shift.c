#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
typedef  enum which { ____Placeholder_which } which ;
struct TYPE_19__ {scalar_t__ lno; } ;
struct TYPE_20__ {scalar_t__ lno; } ;
struct TYPE_23__ {TYPE_11__ addr1; TYPE_12__ addr2; TYPE_1__** argv; } ;
struct TYPE_22__ {scalar_t__ lno; size_t cno; int /*<<< orphan*/ * rptlines; } ;
struct TYPE_21__ {char* bp; } ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXCMD ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SPACE_RETW (TYPE_2__*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  CUT_LINEMODE ; 
 int /*<<< orphan*/  DBG_FATAL ; 
 int /*<<< orphan*/  FREE_SPACEW (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_RETW (TYPE_2__*,char*,size_t,int) ; 
 size_t L_SHIFT ; 
 int /*<<< orphan*/  MEMCPY (char*,char*,size_t) ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  O_SHIFTWIDTH ; 
 int /*<<< orphan*/  O_TABSTOP ; 
 size_t O_VAL (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int RIGHT ; 
 scalar_t__ cut (TYPE_2__*,int /*<<< orphan*/ *,TYPE_11__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ db_get (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ db_set (TYPE_2__*,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nonblank (TYPE_2__*,scalar_t__,size_t*) ; 

__attribute__((used)) static int
shift(SCR *sp, EXCMD *cmdp, enum which rl)
{
	recno_t from, to;
	size_t blen, len, newcol, newidx, oldcol, oldidx, sw;
	int curset;
	CHAR_T *p;
	CHAR_T *bp, *tbp;

	NEEDFILE(sp, cmdp);

	if (O_VAL(sp, O_SHIFTWIDTH) == 0) {
		msgq(sp, M_INFO, "152|shiftwidth option set to 0");
		return (0);
	}

	/* Copy the lines being shifted into the unnamed buffer. */
	if (cut(sp, NULL, &cmdp->addr1, &cmdp->addr2, CUT_LINEMODE))
		return (1);

	/*
	 * The historic version of vi permitted the user to string any number
	 * of '>' or '<' characters together, resulting in an indent of the
	 * appropriate levels.  There's a special hack in ex_cmd() so that
	 * cmdp->argv[0] points to the string of '>' or '<' characters.
	 *
	 * Q: What's the difference between the people adding features
	 *    to vi and the Girl Scouts?
	 * A: The Girl Scouts have mint cookies and adult supervision.
	 */
	for (p = cmdp->argv[0]->bp, sw = 0; *p == '>' || *p == '<'; ++p)
		sw += O_VAL(sp, O_SHIFTWIDTH);

	GET_SPACE_RETW(sp, bp, blen, 256);

	curset = 0;
	for (from = cmdp->addr1.lno, to = cmdp->addr2.lno; from <= to; ++from) {
		if (db_get(sp, from, DBG_FATAL, &p, &len))
			goto err;
		if (!len) {
			if (sp->lno == from)
				curset = 1;
			continue;
		}

		/*
		 * Calculate the old indent amount and the number of
		 * characters it used.
		 */
		for (oldidx = 0, oldcol = 0; oldidx < len; ++oldidx)
			if (p[oldidx] == ' ')
				++oldcol;
			else if (p[oldidx] == '\t')
				oldcol += O_VAL(sp, O_TABSTOP) -
				    oldcol % O_VAL(sp, O_TABSTOP);
			else
				break;

		/* Calculate the new indent amount. */
		if (rl == RIGHT)
			newcol = oldcol + sw;
		else {
			newcol = oldcol < sw ? 0 : oldcol - sw;
			if (newcol == oldcol) {
				if (sp->lno == from)
					curset = 1;
				continue;
			}
		}

		/* Get a buffer that will hold the new line. */
		ADD_SPACE_RETW(sp, bp, blen, newcol + len);

		/*
		 * Build a new indent string and count the number of
		 * characters it uses.
		 */
		for (tbp = bp, newidx = 0;
		    newcol >= O_VAL(sp, O_TABSTOP); ++newidx) {
			*tbp++ = '\t';
			newcol -= O_VAL(sp, O_TABSTOP);
		}
		for (; newcol > 0; --newcol, ++newidx)
			*tbp++ = ' ';

		/* Add the original line. */
		MEMCPY(tbp, p + oldidx, len - oldidx);

		/* Set the replacement line. */
		if (db_set(sp, from, bp, (tbp + (len - oldidx)) - bp)) {
err:			FREE_SPACEW(sp, bp, blen);
			return (1);
		}

		/*
		 * !!!
		 * The shift command in historic vi had the usual bizarre
		 * collection of cursor semantics.  If called from vi, the
		 * cursor was repositioned to the first non-blank character
		 * of the lowest numbered line shifted.  If called from ex,
		 * the cursor was repositioned to the first non-blank of the
		 * highest numbered line shifted.  Here, if the cursor isn't
		 * part of the set of lines that are moved, move it to the
		 * first non-blank of the last line shifted.  (This makes
		 * ":3>>" in vi work reasonably.)  If the cursor is part of
		 * the shifted lines, it doesn't get moved at all.  This
		 * permits shifting of marked areas, i.e. ">'a." shifts the
		 * marked area twice, something that couldn't be done with
		 * historic vi.
		 */
		if (sp->lno == from) {
			curset = 1;
			if (newidx > oldidx)
				sp->cno += newidx - oldidx;
			else if (sp->cno >= oldidx - newidx)
				sp->cno -= oldidx - newidx;
		}
	}
	if (!curset) {
		sp->lno = to;
		sp->cno = 0;
		(void)nonblank(sp, to, &sp->cno);
	}

	FREE_SPACEW(sp, bp, blen);

	sp->rptlines[L_SHIFT] += cmdp->addr2.lno - cmdp->addr1.lno + 1;
	return (0);
}