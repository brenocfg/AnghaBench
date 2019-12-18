#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_14__ {int h; } ;
struct TYPE_15__ {TYPE_1__ t_size; } ;
struct TYPE_16__ {TYPE_2__ el_terminal; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  ELRE_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EL_CAN_DELETE ; 
 int /*<<< orphan*/  EL_CAN_INSERT ; 
 int MIN_END_KEEP ; 
 int /*<<< orphan*/  __F ; 
 int /*<<< orphan*/  re__strncopy (char*,char*,size_t) ; 
 int /*<<< orphan*/  re_clear_eol (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  re_delete (TYPE_3__*,char*,int,int,int) ; 
 int /*<<< orphan*/  re_insert (TYPE_3__*,char*,int,int,char*,int) ; 
 int /*<<< orphan*/  re_printstr (TYPE_3__*,char*,char*,char*) ; 
 int /*<<< orphan*/  terminal_deletechars (TYPE_3__*,int) ; 
 int /*<<< orphan*/  terminal_insertwrite (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  terminal_move_to_char (TYPE_3__*,int) ; 
 int /*<<< orphan*/  terminal_move_to_line (TYPE_3__*,int) ; 
 int /*<<< orphan*/  terminal_overwrite (TYPE_3__*,char*,size_t) ; 

__attribute__((used)) static void
re_update_line(EditLine *el, wchar_t *old, wchar_t *new, int i)
{
	wchar_t *o, *n, *p, c;
	wchar_t *ofd, *ols, *oe, *nfd, *nls, *ne;
	wchar_t *osb, *ose, *nsb, *nse;
	int fx, sx;
	size_t len;

	/*
         * find first diff
         */
	for (o = old, n = new; *o && (*o == *n); o++, n++)
		continue;
	ofd = o;
	nfd = n;

	/*
         * Find the end of both old and new
         */
	while (*o)
		o++;
	/*
         * Remove any trailing blanks off of the end, being careful not to
         * back up past the beginning.
         */
	while (ofd < o) {
		if (o[-1] != ' ')
			break;
		o--;
	}
	oe = o;
	*oe = '\0';

	while (*n)
		n++;

	/* remove blanks from end of new */
	while (nfd < n) {
		if (n[-1] != ' ')
			break;
		n--;
	}
	ne = n;
	*ne = '\0';

	/*
         * if no diff, continue to next line of redraw
         */
	if (*ofd == '\0' && *nfd == '\0') {
		ELRE_DEBUG(1, (__F, "no difference.\r\n"));
		return;
	}
	/*
         * find last same pointer
         */
	while ((o > ofd) && (n > nfd) && (*--o == *--n))
		continue;
	ols = ++o;
	nls = ++n;

	/*
         * find same beginning and same end
         */
	osb = ols;
	nsb = nls;
	ose = ols;
	nse = nls;

	/*
         * case 1: insert: scan from nfd to nls looking for *ofd
         */
	if (*ofd) {
		for (c = *ofd, n = nfd; n < nls; n++) {
			if (c == *n) {
				for (o = ofd, p = n;
				    p < nls && o < ols && *o == *p;
				    o++, p++)
					continue;
				/*
				 * if the new match is longer and it's worth
				 * keeping, then we take it
				 */
				if (((nse - nsb) < (p - n)) &&
				    (2 * (p - n) > n - nfd)) {
					nsb = n;
					nse = p;
					osb = ofd;
					ose = o;
				}
			}
		}
	}
	/*
         * case 2: delete: scan from ofd to ols looking for *nfd
         */
	if (*nfd) {
		for (c = *nfd, o = ofd; o < ols; o++) {
			if (c == *o) {
				for (n = nfd, p = o;
				    p < ols && n < nls && *p == *n;
				    p++, n++)
					continue;
				/*
				 * if the new match is longer and it's worth
				 * keeping, then we take it
				 */
				if (((ose - osb) < (p - o)) &&
				    (2 * (p - o) > o - ofd)) {
					nsb = nfd;
					nse = n;
					osb = o;
					ose = p;
				}
			}
		}
	}
	/*
         * Pragmatics I: If old trailing whitespace or not enough characters to
         * save to be worth it, then don't save the last same info.
         */
	if ((oe - ols) < MIN_END_KEEP) {
		ols = oe;
		nls = ne;
	}
	/*
         * Pragmatics II: if the terminal isn't smart enough, make the data
         * dumber so the smart update doesn't try anything fancy
         */

	/*
         * fx is the number of characters we need to insert/delete: in the
         * beginning to bring the two same begins together
         */
	fx = (int)((nsb - nfd) - (osb - ofd));
	/*
         * sx is the number of characters we need to insert/delete: in the
         * end to bring the two same last parts together
         */
	sx = (int)((nls - nse) - (ols - ose));

	if (!EL_CAN_INSERT) {
		if (fx > 0) {
			osb = ols;
			ose = ols;
			nsb = nls;
			nse = nls;
		}
		if (sx > 0) {
			ols = oe;
			nls = ne;
		}
		if ((ols - ofd) < (nls - nfd)) {
			ols = oe;
			nls = ne;
		}
	}
	if (!EL_CAN_DELETE) {
		if (fx < 0) {
			osb = ols;
			ose = ols;
			nsb = nls;
			nse = nls;
		}
		if (sx < 0) {
			ols = oe;
			nls = ne;
		}
		if ((ols - ofd) > (nls - nfd)) {
			ols = oe;
			nls = ne;
		}
	}
	/*
         * Pragmatics III: make sure the middle shifted pointers are correct if
         * they don't point to anything (we may have moved ols or nls).
         */
	/* if the change isn't worth it, don't bother */
	/* was: if (osb == ose) */
	if ((ose - osb) < MIN_END_KEEP) {
		osb = ols;
		ose = ols;
		nsb = nls;
		nse = nls;
	}
	/*
         * Now that we are done with pragmatics we recompute fx, sx
         */
	fx = (int)((nsb - nfd) - (osb - ofd));
	sx = (int)((nls - nse) - (ols - ose));

	ELRE_DEBUG(1, (__F, "fx %d, sx %d\n", fx, sx));
	ELRE_DEBUG(1, (__F, "ofd %td, osb %td, ose %td, ols %td, oe %td\n",
		ofd - old, osb - old, ose - old, ols - old, oe - old));
	ELRE_DEBUG(1, (__F, "nfd %td, nsb %td, nse %td, nls %td, ne %td\n",
		nfd - new, nsb - new, nse - new, nls - new, ne - new));
	ELRE_DEBUG(1, (__F,
		"xxx-xxx:\"00000000001111111111222222222233333333334\"\r\n"));
	ELRE_DEBUG(1, (__F,
		"xxx-xxx:\"01234567890123456789012345678901234567890\"\r\n"));
#ifdef DEBUG_REFRESH
	re_printstr(el, "old- oe", old, oe);
	re_printstr(el, "new- ne", new, ne);
	re_printstr(el, "old-ofd", old, ofd);
	re_printstr(el, "new-nfd", new, nfd);
	re_printstr(el, "ofd-osb", ofd, osb);
	re_printstr(el, "nfd-nsb", nfd, nsb);
	re_printstr(el, "osb-ose", osb, ose);
	re_printstr(el, "nsb-nse", nsb, nse);
	re_printstr(el, "ose-ols", ose, ols);
	re_printstr(el, "nse-nls", nse, nls);
	re_printstr(el, "ols- oe", ols, oe);
	re_printstr(el, "nls- ne", nls, ne);
#endif /* DEBUG_REFRESH */

	/*
         * el_cursor.v to this line i MUST be in this routine so that if we
         * don't have to change the line, we don't move to it. el_cursor.h to
         * first diff char
         */
	terminal_move_to_line(el, i);

	/*
         * at this point we have something like this:
         *
         * /old                  /ofd    /osb               /ose    /ols     /oe
         * v.....................v       v..................v       v........v
         * eddie> Oh, my fredded gruntle-buggy is to me, as foo var lurgid as
         * eddie> Oh, my fredded quiux buggy is to me, as gruntle-lurgid as
         * ^.....................^     ^..................^       ^........^
         * \new                  \nfd  \nsb               \nse     \nls    \ne
         *
         * fx is the difference in length between the chars between nfd and
         * nsb, and the chars between ofd and osb, and is thus the number of
         * characters to delete if < 0 (new is shorter than old, as above),
         * or insert (new is longer than short).
         *
         * sx is the same for the second differences.
         */

	/*
         * if we have a net insert on the first difference, AND inserting the
         * net amount ((nsb-nfd) - (osb-ofd)) won't push the last useful
         * character (which is ne if nls != ne, otherwise is nse) off the edge
	 * of the screen (el->el_terminal.t_size.h) else we do the deletes first
	 * so that we keep everything we need to.
         */

	/*
         * if the last same is the same like the end, there is no last same
         * part, otherwise we want to keep the last same part set p to the
         * last useful old character
         */
	p = (ols != oe) ? oe : ose;

	/*
         * if (There is a diffence in the beginning) && (we need to insert
         *   characters) && (the number of characters to insert is less than
         *   the term width)
	 *	We need to do an insert!
	 * else if (we need to delete characters)
	 *	We need to delete characters!
	 * else
	 *	No insert or delete
         */
	if ((nsb != nfd) && fx > 0 &&
	    ((p - old) + fx <= el->el_terminal.t_size.h)) {
		ELRE_DEBUG(1,
		    (__F, "first diff insert at %td...\r\n", nfd - new));
		/*
		 * Move to the first char to insert, where the first diff is.
		 */
		terminal_move_to_char(el, (int)(nfd - new));
		/*
		 * Check if we have stuff to keep at end
		 */
		if (nsb != ne) {
			ELRE_DEBUG(1, (__F, "with stuff to keep at end\r\n"));
			/*
		         * insert fx chars of new starting at nfd
		         */
			if (fx > 0) {
				ELRE_DEBUG(!EL_CAN_INSERT, (__F,
				"ERROR: cannot insert in early first diff\n"));
				terminal_insertwrite(el, nfd, fx);
				re_insert(el, old, (int)(ofd - old),
				    el->el_terminal.t_size.h, nfd, fx);
			}
			/*
		         * write (nsb-nfd) - fx chars of new starting at
		         * (nfd + fx)
			 */
			len = (size_t) ((nsb - nfd) - fx);
			terminal_overwrite(el, (nfd + fx), len);
			re__strncopy(ofd + fx, nfd + fx, len);
		} else {
			ELRE_DEBUG(1, (__F, "without anything to save\r\n"));
			len = (size_t)(nsb - nfd);
			terminal_overwrite(el, nfd, len);
			re__strncopy(ofd, nfd, len);
			/*
		         * Done
		         */
			return;
		}
	} else if (fx < 0) {
		ELRE_DEBUG(1,
		    (__F, "first diff delete at %td...\r\n", ofd - old));
		/*
		 * move to the first char to delete where the first diff is
		 */
		terminal_move_to_char(el, (int)(ofd - old));
		/*
		 * Check if we have stuff to save
		 */
		if (osb != oe) {
			ELRE_DEBUG(1, (__F, "with stuff to save at end\r\n"));
			/*
		         * fx is less than zero *always* here but we check
		         * for code symmetry
		         */
			if (fx < 0) {
				ELRE_DEBUG(!EL_CAN_DELETE, (__F,
				    "ERROR: cannot delete in first diff\n"));
				terminal_deletechars(el, -fx);
				re_delete(el, old, (int)(ofd - old),
				    el->el_terminal.t_size.h, -fx);
			}
			/*
		         * write (nsb-nfd) chars of new starting at nfd
		         */
			len = (size_t) (nsb - nfd);
			terminal_overwrite(el, nfd, len);
			re__strncopy(ofd, nfd, len);

		} else {
			ELRE_DEBUG(1, (__F,
			    "but with nothing left to save\r\n"));
			/*
		         * write (nsb-nfd) chars of new starting at nfd
		         */
			terminal_overwrite(el, nfd, (size_t)(nsb - nfd));
			re_clear_eol(el, fx, sx,
			    (int)((oe - old) - (ne - new)));
			/*
		         * Done
		         */
			return;
		}
	} else
		fx = 0;

	if (sx < 0 && (ose - old) + fx < el->el_terminal.t_size.h) {
		ELRE_DEBUG(1, (__F,
		    "second diff delete at %td...\r\n", (ose - old) + fx));
		/*
		 * Check if we have stuff to delete
		 */
		/*
		 * fx is the number of characters inserted (+) or deleted (-)
		 */

		terminal_move_to_char(el, (int)((ose - old) + fx));
		/*
		 * Check if we have stuff to save
		 */
		if (ols != oe) {
			ELRE_DEBUG(1, (__F, "with stuff to save at end\r\n"));
			/*
		         * Again a duplicate test.
		         */
			if (sx < 0) {
				ELRE_DEBUG(!EL_CAN_DELETE, (__F,
				    "ERROR: cannot delete in second diff\n"));
				terminal_deletechars(el, -sx);
			}
			/*
		         * write (nls-nse) chars of new starting at nse
		         */
			terminal_overwrite(el, nse, (size_t)(nls - nse));
		} else {
			ELRE_DEBUG(1, (__F,
			    "but with nothing left to save\r\n"));
			terminal_overwrite(el, nse, (size_t)(nls - nse));
			re_clear_eol(el, fx, sx,
			    (int)((oe - old) - (ne - new)));
		}
	}
	/*
         * if we have a first insert AND WE HAVEN'T ALREADY DONE IT...
         */
	if ((nsb != nfd) && (osb - ofd) <= (nsb - nfd) && (fx == 0)) {
		ELRE_DEBUG(1, (__F, "late first diff insert at %td...\r\n",
		    nfd - new));

		terminal_move_to_char(el, (int)(nfd - new));
		/*
		 * Check if we have stuff to keep at the end
		 */
		if (nsb != ne) {
			ELRE_DEBUG(1, (__F, "with stuff to keep at end\r\n"));
			/*
		         * We have to recalculate fx here because we set it
		         * to zero above as a flag saying that we hadn't done
		         * an early first insert.
		         */
			fx = (int)((nsb - nfd) - (osb - ofd));
			if (fx > 0) {
				/*
				 * insert fx chars of new starting at nfd
				 */
				ELRE_DEBUG(!EL_CAN_INSERT, (__F,
				 "ERROR: cannot insert in late first diff\n"));
				terminal_insertwrite(el, nfd, fx);
				re_insert(el, old, (int)(ofd - old),
				    el->el_terminal.t_size.h, nfd, fx);
			}
			/*
		         * write (nsb-nfd) - fx chars of new starting at
		         * (nfd + fx)
			 */
			len = (size_t) ((nsb - nfd) - fx);
			terminal_overwrite(el, (nfd + fx), len);
			re__strncopy(ofd + fx, nfd + fx, len);
		} else {
			ELRE_DEBUG(1, (__F, "without anything to save\r\n"));
			len = (size_t) (nsb - nfd);
			terminal_overwrite(el, nfd, len);
			re__strncopy(ofd, nfd, len);
		}
	}
	/*
         * line is now NEW up to nse
         */
	if (sx >= 0) {
		ELRE_DEBUG(1, (__F,
		    "second diff insert at %d...\r\n", (int)(nse - new)));
		terminal_move_to_char(el, (int)(nse - new));
		if (ols != oe) {
			ELRE_DEBUG(1, (__F, "with stuff to keep at end\r\n"));
			if (sx > 0) {
				/* insert sx chars of new starting at nse */
				ELRE_DEBUG(!EL_CAN_INSERT, (__F,
				    "ERROR: cannot insert in second diff\n"));
				terminal_insertwrite(el, nse, sx);
			}
			/*
		         * write (nls-nse) - sx chars of new starting at
			 * (nse + sx)
		         */
			terminal_overwrite(el, (nse + sx),
			    (size_t)((nls - nse) - sx));
		} else {
			ELRE_DEBUG(1, (__F, "without anything to save\r\n"));
			terminal_overwrite(el, nse, (size_t)(nls - nse));

			/*
	                 * No need to do a clear-to-end here because we were
	                 * doing a second insert, so we will have over
	                 * written all of the old string.
		         */
		}
	}
	ELRE_DEBUG(1, (__F, "done.\r\n"));
}