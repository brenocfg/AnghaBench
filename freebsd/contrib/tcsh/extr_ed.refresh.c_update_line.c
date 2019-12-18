#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char Char ;

/* Variables and functions */
 char CHAR_DBWIDTH ; 
 int /*<<< orphan*/  ClearEOL (int) ; 
 int CursorH ; 
 int /*<<< orphan*/  DeleteChars (int) ; 
 int /*<<< orphan*/  Insert_write (char*,int) ; 
 int MIN_END_KEEP ; 
 scalar_t__ MarkIsSet ; 
 int /*<<< orphan*/  MoveToChar (int) ; 
 int /*<<< orphan*/  MoveToLine (int) ; 
 int /*<<< orphan*/  STRhighlight ; 
 char* Strend (char*) ; 
 int /*<<< orphan*/  T_CanDel ; 
 int /*<<< orphan*/  T_CanIns ; 
 int TermH ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintstr (char*,char*,char*) ; 
 int /*<<< orphan*/  reprintf (char*,...) ; 
 int /*<<< orphan*/  so_write (char*,int) ; 
 int /*<<< orphan*/  str_cp (char*,char*,int) ; 
 int /*<<< orphan*/  str_delete (char*,int,int,int) ; 
 int /*<<< orphan*/  str_insert (char*,int,int,char*,int) ; 

__attribute__((used)) static void			/* could be changed to make it smarter */
update_line(Char *old, Char *new, int cur_line)
{
    Char *o, *n, *p, c;
    Char  *ofd, *ols, *oe, *nfd, *nls, *ne;
    Char  *osb, *ose, *nsb, *nse;
    int     fx, sx;

    /*
     * find first diff (won't be CHAR_DBWIDTH in either line)
     */
    for (o = old, n = new; *o && (*o == *n); o++, n++)
	continue;
    ofd = o;
    nfd = n;

    /*
     * Find the end of both old and new
     */
    o = Strend(o);

    /* 
     * Remove any trailing blanks off of the end, being careful not to
     * back up past the beginning.
     */
    if (!(adrof(STRhighlight) && MarkIsSet)) {
    while (ofd < o) {
	if (o[-1] != ' ')
	    break;
	o--;
    }
    }
    oe = o;
    *oe = (Char) 0;

    n = Strend(n);

    /* remove blanks from end of new */
    if (!(adrof(STRhighlight) && MarkIsSet)) {
    while (nfd < n) {
	if (n[-1] != ' ')
	    break;
	n--;
    }
    }
    ne = n;
    *ne = (Char) 0;
  
    /*
     * if no diff, continue to next line of redraw
     */
    if (*ofd == '\0' && *nfd == '\0') {
#ifdef DEBUG_UPDATE
	reprintf("no difference.\r\n");
#endif /* DEBUG_UPDATE */
	return;
    }

    /*
     * find last same pointer
     */
    while ((o > ofd) && (n > nfd) && (*--o == *--n))
	continue;
    if (*o != *n) {
	o++;
	n++;
    }
    while (*o == CHAR_DBWIDTH) {
	o++;
	n++;
    }
    ols = o;
    nls = n;

    /*
     * find same begining and same end
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
		for (o = ofd, p = n; p < nls && o < ols && *o == *p; o++, p++)
		    continue;
		/*
		 * if the new match is longer and it's worth keeping, then we
		 * take it
		 */
		if (((nse - nsb) < (p - n)) && (2 * (p - n) > n - nfd)) {
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
		for (n = nfd, p = o; p < ols && n < nls && *p == *n; p++, n++)
		    continue;
		/*
		 * if the new match is longer and it's worth keeping, then we
		 * take it
		 */
		if (((ose - osb) < (p - o)) && (2 * (p - o) > o - ofd)) {
		    nsb = nfd;
		    nse = n;
		    osb = o;
		    ose = p;
		}
	    }
	}
    }
#ifdef notdef
    /*
     * If `last same' is before `same end' re-adjust
     */
    if (ols < ose)
	ols = ose;
    if (nls < nse)
	nls = nse;
#endif

    /*
     * Pragmatics I: If old trailing whitespace or not enough characters to
     * save to be worth it, then don't save the last same info.
     */
    if ((oe - ols) < MIN_END_KEEP) {
	ols = oe;
	nls = ne;
    }

    /*
     * Pragmatics II: if the terminal isn't smart enough, make the data dumber
     * so the smart update doesn't try anything fancy
     */

    /*
     * fx is the number of characters we need to insert/delete: in the
     * beginning to bring the two same begins together
     */
    fx = (int) ((nsb - nfd) - (osb - ofd));
    /*
     * sx is the number of characters we need to insert/delete: in the end to
     * bring the two same last parts together
     */
    sx = (int) ((nls - nse) - (ols - ose));

    if (!T_CanIns) {
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
    if (!T_CanDel) {
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
    fx = (int) ((nsb - nfd) - (osb - ofd));
    sx = (int) ((nls - nse) - (ols - ose));

#ifdef DEBUG_UPDATE
    reprintf("\n");
    reprintf("ofd %d, osb %d, ose %d, ols %d, oe %d\n",
	    ofd - old, osb - old, ose - old, ols - old, oe - old);
    reprintf("nfd %d, nsb %d, nse %d, nls %d, ne %d\n",
	    nfd - new, nsb - new, nse - new, nls - new, ne - new);
    reprintf("xxx-xxx:\"00000000001111111111222222222233333333334\"\r\n");
    reprintf("xxx-xxx:\"01234567890123456789012345678901234567890\"\r\n");
    dprintstr("old- oe", old, oe);
    dprintstr("new- ne", new, ne);
    dprintstr("old-ofd", old, ofd);
    dprintstr("new-nfd", new, nfd);
    dprintstr("ofd-osb", ofd, osb);
    dprintstr("nfd-nsb", nfd, nsb);
    dprintstr("osb-ose", osb, ose);
    dprintstr("nsb-nse", nsb, nse);
    dprintstr("ose-ols", ose, ols);
    dprintstr("nse-nls", nse, nls);
    dprintstr("ols- oe", ols, oe);
    dprintstr("nls- ne", nls, ne);
#endif /* DEBUG_UPDATE */

    /*
     * CursorV to this line cur_line MUST be in this routine so that if we
     * don't have to change the line, we don't move to it. CursorH to first
     * diff char
     */
    MoveToLine(cur_line);

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
     * fx is the difference in length between the the chars between nfd and
     * nsb, and the chars between ofd and osb, and is thus the number of
     * characters to delete if < 0 (new is shorter than old, as above),
     * or insert (new is longer than short).
     *
     * sx is the same for the second differences.
     */

    /*
     * if we have a net insert on the first difference, AND inserting the net
     * amount ((nsb-nfd) - (osb-ofd)) won't push the last useful character
     * (which is ne if nls != ne, otherwise is nse) off the edge of the screen
     * (TermH - 1) else we do the deletes first so that we keep everything we
     * need to.
     */

    /*
     * if the last same is the same like the end, there is no last same part,
     * otherwise we want to keep the last same part set p to the last useful
     * old character
     */
    p = (ols != oe) ? oe : ose;

    /*
     * if (There is a diffence in the beginning) && (we need to insert
     * characters) && (the number of characters to insert is less than the term
     * width) We need to do an insert! else if (we need to delete characters)
     * We need to delete characters! else No insert or delete
     */
    if ((nsb != nfd) && fx > 0 && ((p - old) + fx < TermH)) {
#ifdef DEBUG_UPDATE
	reprintf("first diff insert at %d...\r\n", nfd - new);
#endif  /* DEBUG_UPDATE */
	/*
	 * Move to the first char to insert, where the first diff is.
	 */
	MoveToChar(nfd - new);
	/*
	 * Check if we have stuff to keep at end
	 */
	if (nsb != ne) {
#ifdef DEBUG_UPDATE
	    reprintf("with stuff to keep at end\r\n");
#endif  /* DEBUG_UPDATE */
	    /*
	     * insert fx chars of new starting at nfd
	     */
	    if (fx > 0) {
#ifdef DEBUG_UPDATE
		if (!T_CanIns)
		    reprintf("   ERROR: cannot insert in early first diff\n");
#endif  /* DEBUG_UPDATE */
		Insert_write(nfd, fx);
		str_insert(old, (int) (ofd - old), TermH, nfd, fx);
	    }
	    /*
	     * write (nsb-nfd) - fx chars of new starting at (nfd + fx)
	     */
	    so_write(nfd + fx, (nsb - nfd) - fx);
	    str_cp(ofd + fx, nfd + fx, (int) ((nsb - nfd) - fx));
	}
	else {
#ifdef DEBUG_UPDATE
	    reprintf("without anything to save\r\n");
#endif  /* DEBUG_UPDATE */
	    so_write(nfd, (nsb - nfd));
	    str_cp(ofd, nfd, (int) (nsb - nfd));
	    /*
	     * Done
	     */
	    return;
	}
    }
    else if (fx < 0) {
#ifdef DEBUG_UPDATE
	reprintf("first diff delete at %d...\r\n", ofd - old);
#endif  /* DEBUG_UPDATE */
	/*
	 * move to the first char to delete where the first diff is
	 */
	MoveToChar(ofd - old);
	/*
	 * Check if we have stuff to save
	 */
	if (osb != oe) {
#ifdef DEBUG_UPDATE
	    reprintf("with stuff to save at end\r\n");
#endif  /* DEBUG_UPDATE */
	    /*
	     * fx is less than zero *always* here but we check for code
	     * symmetry
	     */
	    if (fx < 0) {
#ifdef DEBUG_UPDATE
		if (!T_CanDel)
		    reprintf("   ERROR: cannot delete in first diff\n");
#endif /* DEBUG_UPDATE */
		DeleteChars(-fx);
		str_delete(old, (int) (ofd - old), TermH, -fx);
	    }
	    /*
	     * write (nsb-nfd) chars of new starting at nfd
	     */
	    so_write(nfd, (nsb - nfd));
	    str_cp(ofd, nfd, (int) (nsb - nfd));

	}
	else {
#ifdef DEBUG_UPDATE
	    reprintf("but with nothing left to save\r\n");
#endif  /* DEBUG_UPDATE */
	    /*
	     * write (nsb-nfd) chars of new starting at nfd
	     */
	    so_write(nfd, (nsb - nfd));
#ifdef DEBUG_REFRESH
	    reprintf("cleareol %d\n", (oe - old) - (ne - new));
#endif  /* DEBUG_UPDATE */
#ifndef WINNT_NATIVE
	    ClearEOL((oe - old) - (ne - new));
#else
	    /*
	     * The calculation above does not work too well on NT
	     */
	    ClearEOL(TermH - CursorH);
#endif /*WINNT_NATIVE*/
	    /*
	     * Done
	     */
	    return;
	}
    }
    else
	fx = 0;

    if (sx < 0) {
#ifdef DEBUG_UPDATE
	reprintf("second diff delete at %d...\r\n", (ose - old) + fx);
#endif  /* DEBUG_UPDATE */
	/*
	 * Check if we have stuff to delete
	 */
	/*
	 * fx is the number of characters inserted (+) or deleted (-)
	 */

	MoveToChar((ose - old) + fx);
	/*
	 * Check if we have stuff to save
	 */
	if (ols != oe) {
#ifdef DEBUG_UPDATE
	    reprintf("with stuff to save at end\r\n");
#endif  /* DEBUG_UPDATE */
	    /*
	     * Again a duplicate test.
	     */
	    if (sx < 0) {
#ifdef DEBUG_UPDATE
		if (!T_CanDel)
		    reprintf("   ERROR: cannot delete in second diff\n");
#endif  /* DEBUG_UPDATE */
		DeleteChars(-sx);
	    }

	    /*
	     * write (nls-nse) chars of new starting at nse
	     */
	    so_write(nse, (nls - nse));
	}
	else {
	    int olen = (int) (oe - old + fx);
	    if (olen > TermH)
		olen = TermH;
#ifdef DEBUG_UPDATE
	    reprintf("but with nothing left to save\r\n");
#endif /* DEBUG_UPDATE */
	    so_write(nse, (nls - nse));
#ifdef DEBUG_REFRESH
	    reprintf("cleareol %d\n", olen - (ne - new));
#endif /* DEBUG_UPDATE */
#ifndef WINNT_NATIVE
	    ClearEOL(olen - (ne - new));
#else
	    /*
	     * The calculation above does not work too well on NT
	     */
	    ClearEOL(TermH - CursorH);
#endif /*WINNT_NATIVE*/
	}
    }

    /*
     * if we have a first insert AND WE HAVEN'T ALREADY DONE IT...
     */
    if ((nsb != nfd) && (osb - ofd) <= (nsb - nfd) && (fx == 0)) {
#ifdef DEBUG_UPDATE
	reprintf("late first diff insert at %d...\r\n", nfd - new);
#endif /* DEBUG_UPDATE */

	MoveToChar(nfd - new);
	/*
	 * Check if we have stuff to keep at the end
	 */
	if (nsb != ne) {
#ifdef DEBUG_UPDATE
	    reprintf("with stuff to keep at end\r\n");
#endif /* DEBUG_UPDATE */
	    /* 
	     * We have to recalculate fx here because we set it
	     * to zero above as a flag saying that we hadn't done
	     * an early first insert.
	     */
	    fx = (int) ((nsb - nfd) - (osb - ofd));
	    if (fx > 0) {
		/*
		 * insert fx chars of new starting at nfd
		 */
#ifdef DEBUG_UPDATE
		if (!T_CanIns)
		    reprintf("   ERROR: cannot insert in late first diff\n");
#endif /* DEBUG_UPDATE */
		Insert_write(nfd, fx);
		str_insert(old, (int) (ofd - old), TermH, nfd, fx);
	    }

	    /*
	     * write (nsb-nfd) - fx chars of new starting at (nfd + fx)
	     */
	    so_write(nfd + fx, (nsb - nfd) - fx);
	    str_cp(ofd + fx, nfd + fx, (int) ((nsb - nfd) - fx));
	}
	else {
#ifdef DEBUG_UPDATE
	    reprintf("without anything to save\r\n");
#endif /* DEBUG_UPDATE */
	    so_write(nfd, (nsb - nfd));
	    str_cp(ofd, nfd, (int) (nsb - nfd));
	}
    }

    /*
     * line is now NEW up to nse
     */
    if (sx >= 0) {
#ifdef DEBUG_UPDATE
	reprintf("second diff insert at %d...\r\n", nse - new);
#endif /* DEBUG_UPDATE */
	MoveToChar(nse - new);
	if (ols != oe) {
#ifdef DEBUG_UPDATE
	    reprintf("with stuff to keep at end\r\n");
#endif /* DEBUG_UPDATE */
	    if (sx > 0) {
		/* insert sx chars of new starting at nse */
#ifdef DEBUG_UPDATE
		if (!T_CanIns)
		    reprintf("   ERROR: cannot insert in second diff\n");
#endif /* DEBUG_UPDATE */
		Insert_write(nse, sx);
	    }

	    /*
	     * write (nls-nse) - sx chars of new starting at (nse + sx)
	     */
	    so_write(nse + sx, (nls - nse) - sx);
	}
	else {
#ifdef DEBUG_UPDATE
	    reprintf("without anything to save\r\n");
#endif /* DEBUG_UPDATE */
	    so_write(nse, (nls - nse));

	    /*
             * No need to do a clear-to-end here because we were doing
	     * a second insert, so we will have over written all of the
	     * old string.
	     */
	}
    }
#ifdef DEBUG_UPDATE
    reprintf("done.\r\n");
#endif /* DEBUG_UPDATE */
}