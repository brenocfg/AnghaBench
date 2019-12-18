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
 int Cursor ; 
 int InputBuf ; 
 int /*<<< orphan*/ * LastChar ; 
 int Mark ; 
 int /*<<< orphan*/  TCSHOP_INSERT ; 
 int /*<<< orphan*/  UndoAction ; 
 int /*<<< orphan*/ * UndoBuf ; 
 int UndoPtr ; 
 int UndoSize ; 
 scalar_t__ VImode ; 

void
c_delbefore(int num)		/* delete before dot, with bounds checking */
{
    Char *cp, *kp = NULL;

    if (num > Cursor - InputBuf)
	num = (int) (Cursor - InputBuf);	/* bounds check */

    if (num > 0) {			/* if I can delete anything */
	if (VImode) {
	    kp = UndoBuf;		/* Set Up for VI undo command */
	    UndoAction = TCSHOP_INSERT;
	    UndoSize = num;
	    UndoPtr  = Cursor - num;
	    for (cp = Cursor - num; cp <= LastChar; cp++) {
		*kp++ = *cp;
		*cp = cp[num];
	    }
	}
	else
	    for (cp = Cursor - num; cp + num <= LastChar; cp++)
		*cp = cp[num];
	LastChar -= num;
	Cursor -= num;
	/* Mark was within the range of the deleted word? */
	if (Mark && Mark > Cursor && Mark <= Cursor+num)
		Mark = Cursor;
	/* Mark after the deleted word? */
	else if (Mark && Mark > Cursor)
		Mark -= num;
    }
}