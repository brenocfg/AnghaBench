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
 char ASCII ; 
 char CHAR_DBWIDTH ; 
 int TermH ; 
 size_t TermV ; 
 char** Vdisplay ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  reprintf (char*,size_t,size_t,...) ; 
 int vcursor_h ; 
 size_t vcursor_v ; 

__attribute__((used)) static void
Vdraw(Char c, int width)	/* draw char c onto V lines */
{
#ifdef DEBUG_REFRESH
# ifdef SHORT_STRINGS
    reprintf("Vdrawing %6.6o '%c' %d\r\n", (unsigned)c, (int)(c & ASCII), width);
# else
    reprintf("Vdrawing %3.3o '%c' %d\r\n", (unsigned)c, (int)c, width);
# endif /* SHORT_STRNGS */
#endif  /* DEBUG_REFRESH */

    /* Hopefully this is what all the terminals do with multi-column characters
       that "span line breaks". */
    while (vcursor_h + width > TermH)
	Vdraw(' ', 1);
    Vdisplay[vcursor_v][vcursor_h] = c;
    if (width)
	vcursor_h++;		/* advance to next place */
    while (--width > 0)
	Vdisplay[vcursor_v][vcursor_h++] = CHAR_DBWIDTH;
    if (vcursor_h >= TermH) {
	Vdisplay[vcursor_v][TermH] = '\0';	/* assure end of line */
	vcursor_h = 0;		/* reset it. */
	vcursor_v++;
#ifdef DEBUG_REFRESH
	if (vcursor_v >= TermV) {	/* should NEVER happen. */
	    reprintf("\r\nVdraw: vcursor_v overflow! Vcursor_v == %d > %d\r\n",
		    vcursor_v, TermV);
	    abort();
	}
#endif /* DEBUG_REFRESH */
    }
}