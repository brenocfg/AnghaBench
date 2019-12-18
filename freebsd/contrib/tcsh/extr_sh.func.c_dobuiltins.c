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
typedef  int /*<<< orphan*/ * command ;
struct biltins {int /*<<< orphan*/  bname; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int TermH ; 
 scalar_t__ Tty_raw_mode ; 
 int /*<<< orphan*/  USE (int /*<<< orphan*/ **) ; 
 struct biltins const* bfunc ; 
 int /*<<< orphan*/  cleanup_push (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (scalar_t__*) ; 
 int /*<<< orphan*/  flush () ; 
 scalar_t__ lbuffed ; 
 int /*<<< orphan*/  lbuffed_cleanup ; 
 unsigned int max (unsigned int,unsigned int) ; 
 size_t nbfunc ; 
 int /*<<< orphan*/  nt_print_builtins (unsigned int) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xputchar (char) ; 

void
dobuiltins(Char **v, struct command *c)
{
    /* would use print_by_column() in tw.parse.c but that assumes
     * we have an array of Char * to pass.. (sg)
     */
    const struct biltins *b;
    int row, col, columns, rows;
    unsigned int w, maxwidth;

    USE(c);
    USE(v);
    lbuffed = 0;		/* turn off line buffering */
    cleanup_push(&lbuffed, lbuffed_cleanup);

    /* find widest string */
    for (maxwidth = 0, b = bfunc; b < &bfunc[nbfunc]; ++b)
	maxwidth = max(maxwidth, strlen(b->bname));
    ++maxwidth;					/* for space */

    columns = (TermH + 1) / maxwidth;	/* PWP: terminal size change */
    if (!columns)
	columns = 1;
    rows = (nbfunc + (columns - 1)) / columns;

    for (b = bfunc, row = 0; row < rows; row++) {
	for (col = 0; col < columns; col++) {
	    if (b < &bfunc[nbfunc]) {
		w = strlen(b->bname);
		xprintf("%s", b->bname);
		if (col < (columns - 1))	/* Not last column? */
		    for (; w < maxwidth; w++)
			xputchar(' ');
		++b;
	    }
	}
	if (row < (rows - 1)) {
	    if (Tty_raw_mode)
		xputchar('\r');
	    xputchar('\n');
	}
    }
#ifdef WINNT_NATIVE
    nt_print_builtins(maxwidth);
#else
    if (Tty_raw_mode)
	xputchar('\r');
    xputchar('\n');
#endif /* WINNT_NATIVE */

    cleanup_until(&lbuffed);		/* turn back on line buffering */
    flush();
}