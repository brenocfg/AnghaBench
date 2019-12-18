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
 unsigned int NLSStringWidth (int /*<<< orphan*/ *) ; 
 int SHOUT ; 
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/  STRlistflags ; 
 int /*<<< orphan*/ * Strchr (int /*<<< orphan*/ *,char) ; 
 size_t Strlen (int /*<<< orphan*/ *) ; 
 unsigned int TermH ; 
 scalar_t__ Tty_raw_mode ; 
 scalar_t__ didfds ; 
 int /*<<< orphan*/  filetype (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  isatty (int) ; 
 int lbuffed ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  print_with_color (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
print_by_column(Char *dir, Char *items[], int count, int no_file_suffix)
{
    int i, r, c, columns, rows;
    size_t w;
    unsigned int wx, maxwidth = 0;
    Char *val;
    int across;

    lbuffed = 0;		/* turn off line buffering */

    
    across = ((val = varval(STRlistflags)) != STRNULL) && 
	     (Strchr(val, 'x') != NULL);

    for (i = 0; i < count; i++)	{ /* find widest string */
	maxwidth = max(maxwidth, (unsigned int) NLSStringWidth(items[i]));
    }

    maxwidth += no_file_suffix ? 1 : 2;	/* for the file tag and space */
    columns = TermH / maxwidth;		/* PWP: terminal size change */
    if (!columns || !isatty(didfds ? 1 : SHOUT))
	columns = 1;
    rows = (count + (columns - 1)) / columns;

    i = -1;
    for (r = 0; r < rows; r++) {
	for (c = 0; c < columns; c++) {
	    i = across ? (i + 1) : (c * rows + r);

	    if (i < count) {
		wx = 0;
		w = Strlen(items[i]);

#ifdef COLOR_LS_F
		if (no_file_suffix) {
		    /* Print the command name */
		    Char f = items[i][w - 1];
		    items[i][w - 1] = 0;
		    print_with_color(items[i], w - 1, f);
		    items[i][w - 1] = f;
		}
		else {
		    /* Print filename followed by '/' or '*' or ' ' */
		    print_with_color(items[i], w, filetype(dir, items[i]));
		    wx++;
		}
#else /* ifndef COLOR_LS_F */
		if (no_file_suffix) {
		    /* Print the command name */
		    xprintf("%S", items[i]);
		}
		else {
		    /* Print filename followed by '/' or '*' or ' ' */
		    xprintf("%-S%c", items[i], filetype(dir, items[i]));
		    wx++;
		}
#endif /* COLOR_LS_F */

		if (c < (columns - 1)) {	/* Not last column? */
		    w = NLSStringWidth(items[i]) + wx;
		    for (; w < maxwidth; w++)
			xputchar(' ');
		}
	    }
	    else if (across)
		break;
	}
	if (Tty_raw_mode)
	    xputchar('\r');
	xputchar('\n');
    }

    lbuffed = 1;		/* turn back on line buffering */
    flush();
}