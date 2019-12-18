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
 int ASC (int) ; 
 int ATTRIBUTES ; 
 int CHAR ; 
 int CTL_ESC (int) ; 
 int MB_CUR_MAX ; 
 int QUOTE ; 
 int /*<<< orphan*/  STRcolorcat ; 
 int /*<<< orphan*/  SetAttributes (int) ; 
 int TRIM ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ didfds ; 
 int /*<<< orphan*/  flush () ; 
 scalar_t__ haderr ; 
 scalar_t__ is1atty ; 
 scalar_t__ is2atty ; 
 scalar_t__ iscntrl (int) ; 
 scalar_t__ isdiagatty ; 
 scalar_t__ isoutatty ; 
 int /*<<< orphan*/  isprint (int) ; 
 scalar_t__ lbuffed ; 
 int /*<<< orphan*/  output_raw ; 
 int /*<<< orphan*/  putpure (int) ; 
 int /*<<< orphan*/  putraw (int) ; 
 scalar_t__ xlate_cr ; 

void
xputchar(int c)
{
    int     atr;

    atr = c & ATTRIBUTES & TRIM;
    c &= CHAR | QUOTE;
    if (!output_raw && (c & QUOTE) == 0) {
	if (iscntrl(c) && (ASC(c) < 0x80 || MB_CUR_MAX == 1)) {
	    if (c != '\t' && c != '\n'
#ifdef COLORCAT
	        && !(adrof(STRcolorcat) && c == CTL_ESC('\033'))
#endif
		&& (xlate_cr || c != '\r'))
	    {
		xputchar('^' | atr);
		if (c == CTL_ESC('\177'))
		    c = '?';
		else
		    /* Note: for IS_ASCII, this compiles to: c = c | 0100 */
		    c = CTL_ESC(ASC(c)|0100);
	    }
	}
	else if (!isprint(c) && (ASC(c) < 0x80 || MB_CUR_MAX == 1)) {
	    xputchar('\\' | atr);
	    xputchar((((c >> 6) & 7) + '0') | atr);
	    xputchar((((c >> 3) & 7) + '0') | atr);
	    c = (c & 7) + '0';
	}
	(void) putraw(c | atr);
    }
    else {
	c &= TRIM;
	if (haderr ? (didfds ? is2atty : isdiagatty) :
	    (didfds ? is1atty : isoutatty))
	    SetAttributes(c | atr);
	(void) putpure(c);
    }
    if (lbuffed && (c & CHAR) == '\n')
	flush();
}