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

/* Variables and functions */
 scalar_t__ CHAR_DBWIDTH ; 
 int CursorH ; 
 size_t CursorV ; 
 scalar_t__** Display ; 
 scalar_t__ GoodStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUTPURE ; 
 int /*<<< orphan*/  Str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_LE ; 
 int /*<<< orphan*/  T_RI ; 
 scalar_t__ T_Tabs ; 
 int /*<<< orphan*/  T_ch ; 
 int TermH ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  so_write (scalar_t__*,int) ; 
 int /*<<< orphan*/  tgoto (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tputs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

void
MoveToChar(int where)		/* move to character position (where) */
{				/* as efficiently as possible */
    int     del;

mc_again:
    if (where == CursorH)
	return;

    if (where >= TermH) {
#ifdef DEBUG_SCREEN
	xprintf("MoveToChar: where is riduculous: %d\r\n", where);
	flush();
#endif /* DEBUG_SCREEN */
	return;
    }

    if (!where) {		/* if where is first column */
	(void) putraw('\r');	/* do a CR */
	CursorH = 0;
	return;
    }

    del = where - CursorH;

    if ((del < -4 || del > 4) && GoodStr(T_ch))
	/* go there directly */
	(void) tputs(tgoto(Str(T_ch), where, where), where, PUTPURE);
    else {
	int i;
	if (del > 0) {		/* moving forward */
	    if ((del > 4) && GoodStr(T_RI))
		(void) tputs(tgoto(Str(T_RI), del, del), del, PUTPURE);
	    else {
		/* if I can do tabs, use them */
		if (T_Tabs) {
		    if ((CursorH & 0370) != (where & ~0x7)
			&& Display[CursorV][where & ~0x7] != CHAR_DBWIDTH) {
			/* if not within tab stop */
			for (i = (CursorH & 0370); i < (where & ~0x7); i += 8)
			    (void) putraw('\t');	/* then tab over */
			CursorH = where & ~0x7;
			/* Note: considering that we often want to go to
			   TermH - 1 for the wrapping, it would be nice to
			   optimize this case by tabbing to the last column
			   - but this doesn't work for all terminals! */
		    }
		}
		/* it's usually cheaper to just write the chars, so we do. */

		/* NOTE THAT so_write() WILL CHANGE CursorH!!! */
		so_write(&Display[CursorV][CursorH], where - CursorH);

	    }
	}
	else {			/* del < 0 := moving backward */
	    if ((-del > 4) && GoodStr(T_LE))
		(void) tputs(tgoto(Str(T_LE), -del, -del), -del, PUTPURE);
	    else {		/* can't go directly there */
		/* if the "cost" is greater than the "cost" from col 0 */
		if (T_Tabs ? (-del > ((where >> 3) + (where & 07)))
		    : (-del > where)) {
		    (void) putraw('\r');	/* do a CR */
		    CursorH = 0;
		    goto mc_again;	/* and try again */
		}
		for (i = 0; i < -del; i++)
		    (void) putraw('\b');
	    }
	}
    }
    CursorH = where;		/* now where is here */
}