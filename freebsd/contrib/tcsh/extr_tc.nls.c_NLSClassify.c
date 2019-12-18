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
 int CHAR ; 
 int INVALID_BYTE ; 
 scalar_t__ Iscntrl (int) ; 
 scalar_t__ Isprint (int) ; 
 int NLSCLASS_CTRL ; 
 int NLSCLASS_ILLEGAL ; 
 int NLSCLASS_ILLEGAL2 ; 
 int NLSCLASS_ILLEGAL3 ; 
 int NLSCLASS_ILLEGAL4 ; 
 int NLSCLASS_ILLEGAL5 ; 
 int NLSCLASS_NL ; 
 int NLSCLASS_TAB ; 
 int NLSWidth (int) ; 
 int QUOTE ; 

int
NLSClassify(Char c, int nocomb, int drawPrompt)
{
    int w;
#ifndef SHORT_STRINGS
    if ((c & 0x80) != 0)		/* c >= 0x80 */
	return NLSCLASS_ILLEGAL;
#endif
    if (!drawPrompt) {			/* draw command-line */
#if INVALID_BYTE != 0
	if ((c & INVALID_BYTE) == INVALID_BYTE)		/* c >= INVALID_BYTE */
	    return NLSCLASS_ILLEGAL;
	if ((c & INVALID_BYTE) == QUOTE && (c & 0x80) == 0)	/* c >= QUOTE */
	    return 1;
	if (c >= 0x10000000)		/* U+10000000 = FC 90 80 80 80 80 */
	    return NLSCLASS_ILLEGAL5;
	if (c >= 0x1000000)		/*  U+1000000 = F9 80 80 80 80 */
	    return NLSCLASS_ILLEGAL4;
	if (c >= 0x100000)		/*   U+100000 = F4 80 80 80 */
	    return NLSCLASS_ILLEGAL3;
#endif
	if (c >= 0x10000)		/*    U+10000 = F0 90 80 80 */
	    return NLSCLASS_ILLEGAL2;
    }
    if (Iscntrl(c) && (c & CHAR) < 0x100) {
	if (c == '\n')
	    return NLSCLASS_NL;
	if (c == '\t')
	    return NLSCLASS_TAB;
	return NLSCLASS_CTRL;
    }
    w = NLSWidth(c);
    if (drawPrompt) {			/* draw prompt */
	if (w > 0)
	    return w;
	if (w == 0)
	    return 1;
    }
    if ((w > 0 && !(Iscntrl(c) && (c & CHAR) < 0x100)) || (Isprint(c) && !nocomb))
	return w;
    return NLSCLASS_ILLEGAL;
}