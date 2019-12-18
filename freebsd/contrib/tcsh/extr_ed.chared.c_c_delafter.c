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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ * Cursor ; 
 int /*<<< orphan*/ * LastChar ; 
 int /*<<< orphan*/  MODE_INSERT ; 
 int /*<<< orphan*/ * Mark ; 
 int /*<<< orphan*/  TCSHOP_INSERT ; 
 int /*<<< orphan*/  UndoAction ; 
 int /*<<< orphan*/ * UndoBuf ; 
 int /*<<< orphan*/ * UndoPtr ; 
 int UndoSize ; 
 scalar_t__ VImode ; 
 int /*<<< orphan*/  inputmode ; 

void
c_delafter(int num)
{
    Char *cp, *kp = NULL;

    if (num > LastChar - Cursor)
	num = (int) (LastChar - Cursor);	/* bounds check */

    if (num > 0) {			/* if I can delete anything */
	if (VImode) {
	    kp = UndoBuf;		/* Set Up for VI undo command */
	    UndoAction = TCSHOP_INSERT;
	    UndoSize = num;
	    UndoPtr  = Cursor;
	    for (cp = Cursor; cp <= LastChar; cp++) {
		*kp++ = *cp;	/* Save deleted chars into undobuf */
		*cp = cp[num];
	    }
	}
	else
	    for (cp = Cursor; cp + num <= LastChar; cp++)
		*cp = cp[num];
	LastChar -= num;
	/* Mark was within the range of the deleted word? */
	if (Mark && Mark > Cursor && Mark <= Cursor+num)
		Mark = Cursor;
	/* Mark after the deleted word? */
	else if (Mark && Mark > Cursor)
		Mark -= num;
    }
#ifdef notdef
    else {
	/* 
	 * XXX: We don't want to do that. In emacs mode overwrite should be
	 * sticky. I am not sure how that affects vi mode 
	 */
	inputmode = MODE_INSERT;
    }
#endif /* notdef */
}