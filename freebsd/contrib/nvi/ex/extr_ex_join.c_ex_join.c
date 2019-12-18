#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_19__ {scalar_t__ lno; } ;
struct TYPE_18__ {scalar_t__ lno; } ;
struct TYPE_21__ {int addrcnt; TYPE_2__ addr1; TYPE_1__ addr2; int /*<<< orphan*/  iflags; } ;
struct TYPE_20__ {int cno; scalar_t__ lno; int /*<<< orphan*/ * rptlines; } ;
typedef  TYPE_3__ SCR ;
typedef  TYPE_4__ EXCMD ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SPACE_RETW (TYPE_3__*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  E_ADDR_DEF ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_SPACEW (TYPE_3__*,char*,size_t) ; 
 scalar_t__ F_ISSET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SPACE_RETW (TYPE_3__*,char*,size_t,int) ; 
 int /*<<< orphan*/  L (char*) ; 
 size_t L_JOINED ; 
 int /*<<< orphan*/  MEMCPY (char*,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  NEEDFILE (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ STRCHR (int /*<<< orphan*/ ,int) ; 
 scalar_t__ db_delete (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  db_exist (TYPE_3__*,scalar_t__) ; 
 scalar_t__ db_get (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,char**,size_t*) ; 
 scalar_t__ db_set (TYPE_3__*,scalar_t__,char*,int) ; 
 scalar_t__ isblank (char) ; 
 int /*<<< orphan*/  msgq (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

int
ex_join(SCR *sp, EXCMD *cmdp)
{
	recno_t from, to;
	size_t blen, clen, len, tlen;
	int echar = 0, extra, first;
	CHAR_T *bp, *tbp = NULL;
	CHAR_T *p;

	NEEDFILE(sp, cmdp);

	from = cmdp->addr1.lno;
	to = cmdp->addr2.lno;

	/* Check for no lines to join. */
	if (!db_exist(sp, from + 1)) {
		msgq(sp, M_ERR, "131|No following lines to join");
		return (1);
	}

	GET_SPACE_RETW(sp, bp, blen, 256);

	/*
	 * The count for the join command was off-by-one,
	 * historically, to other counts for other commands.
	 */
	if (F_ISSET(cmdp, E_ADDR_DEF) || cmdp->addrcnt == 1)
		++cmdp->addr2.lno;

	clen = tlen = 0;
	for (first = 1,
	    from = cmdp->addr1.lno, to = cmdp->addr2.lno; from <= to; ++from) {
		/*
		 * Get next line.  Historic versions of vi allowed "10J" while
		 * less than 10 lines from the end-of-file, so we do too.
		 */
		if (db_get(sp, from, 0, &p, &len)) {
			cmdp->addr2.lno = from - 1;
			break;
		}

		/* Empty lines just go away. */
		if (len == 0)
			continue;

		/*
		 * Get more space if necessary.  Note, tlen isn't the length
		 * of the new line, it's roughly the amount of space needed.
		 * tbp - bp is the length of the new line.
		 */
		tlen += len + 2;
		ADD_SPACE_RETW(sp, bp, blen, tlen);
		tbp = bp + clen;

		/*
		 * Historic practice:
		 *
		 * If force specified, join without modification.
		 * If the current line ends with whitespace, strip leading
		 *    whitespace from the joined line.
		 * If the next line starts with a ), do nothing.
		 * If the current line ends with ., insert two spaces.
		 * Else, insert one space.
		 *
		 * One change -- add ? and ! to the list of characters for
		 * which we insert two spaces.  I expect that POSIX 1003.2
		 * will require this as well.
		 *
		 * Echar is the last character in the last line joined.
		 */
		extra = 0;
		if (!first && !FL_ISSET(cmdp->iflags, E_C_FORCE)) {
			if (isblank(echar))
				for (; len && isblank(*p); --len, ++p);
			else if (p[0] != ')') {
				if (STRCHR(L(".?!"), echar)) {
					*tbp++ = ' ';
					++clen;
					extra = 1;
				}
				*tbp++ = ' ';
				++clen;
				for (; len && isblank(*p); --len, ++p);
			}
		}

		if (len != 0) {
			MEMCPY(tbp, p, len);
			tbp += len;
			clen += len;
			echar = p[len - 1];
		} else
			echar = ' ';

		/*
		 * Historic practice for vi was to put the cursor at the first
		 * inserted whitespace character, if there was one, or the
		 * first character of the joined line, if there wasn't, or the
		 * last character of the line if joined to an empty line.  If
		 * a count was specified, the cursor was moved as described
		 * for the first line joined, ignoring subsequent lines.  If
		 * the join was a ':' command, the cursor was placed at the
		 * first non-blank character of the line unless the cursor was
		 * "attracted" to the end of line when the command was executed
		 * in which case it moved to the new end of line.  There are
		 * probably several more special cases, but frankly, my dear,
		 * I don't give a damn.  This implementation puts the cursor
		 * on the first inserted whitespace character, the first
		 * character of the joined line, or the last character of the
		 * line regardless.  Note, if the cursor isn't on the joined
		 * line (possible with : commands), it is reset to the starting
		 * line.
		 */
		if (first) {
			sp->cno = (tbp - bp) - (1 + extra);
			first = 0;
		} else
			sp->cno = (tbp - bp) - len - (1 + extra);
	}
	sp->lno = cmdp->addr1.lno;

	/* Delete the joined lines. */
	for (from = cmdp->addr1.lno, to = cmdp->addr2.lno; to > from; --to)
		if (db_delete(sp, to))
			goto err;

	/* If the original line changed, reset it. */
	if (!first && db_set(sp, from, bp, tbp - bp)) {
err:		FREE_SPACEW(sp, bp, blen);
		return (1);
	}
	FREE_SPACEW(sp, bp, blen);

	sp->rptlines[L_JOINED] += (cmdp->addr2.lno - cmdp->addr1.lno) + 1;
	return (0);
}