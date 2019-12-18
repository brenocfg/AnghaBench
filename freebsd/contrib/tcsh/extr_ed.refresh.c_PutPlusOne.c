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
typedef  int Char ;

/* Variables and functions */
 int CHAR_DBWIDTH ; 
 scalar_t__ CursorH ; 
 size_t CursorV ; 
 int** Display ; 
 int LITERAL ; 
 int LIT_FACTOR ; 
 int MARGIN_AUTO ; 
 int MARGIN_MAGIC ; 
 int /*<<< orphan*/  OldvcV ; 
 int T_Margin ; 
 scalar_t__ TermH ; 
 int* litptr ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  putwraw (int) ; 

__attribute__((used)) static void
PutPlusOne(Char c, int width)
{
    while (width > 1 && CursorH + width > TermH)
	PutPlusOne(' ', 1);
    if ((c & LITERAL) != 0) {
	Char *d;
	for (d = litptr + (c & ~LITERAL) * LIT_FACTOR; *d; d++)
	    (void) putwraw(*d);
    } else {
	(void) putwraw(c);
    }
    Display[CursorV][CursorH++] = (Char) c;
    while (--width > 0)
	Display[CursorV][CursorH++] = CHAR_DBWIDTH;
    if (CursorH >= TermH) {	/* if we must overflow */
	CursorH = 0;
	CursorV++;
	OldvcV++;
	if (T_Margin & MARGIN_AUTO) {
	    if (T_Margin & MARGIN_MAGIC) {
		(void) putraw(' ');
		(void) putraw('\b');
	    }
	}
	else {
	    (void) putraw('\r');
	    (void) putraw('\n');
	}
    }
}