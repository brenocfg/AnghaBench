#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {char* bp; int len; } ;
struct TYPE_16__ {size_t cols; struct TYPE_16__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_1__ GS ;
typedef  char CHAR_T ;
typedef  TYPE_3__ ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_INTR ; 
 scalar_t__ COL_OFF (size_t,int) ; 
 int /*<<< orphan*/  FREE_SPACE (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_INTERRUPTED ; 
 int /*<<< orphan*/  INT2CHAR (TYPE_1__*,char*,int,char*,size_t) ; 
 scalar_t__ KEY_COL (TYPE_1__*,char) ; 
 scalar_t__ MEMCMP (char*,char*,size_t) ; 
 int /*<<< orphan*/  SC_TINPUT_INFO ; 
 int /*<<< orphan*/  ex_fflush (TYPE_1__*) ; 
 size_t ex_printf (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  ex_puts (TYPE_1__*,char*) ; 
 char* msg_print (TYPE_1__*,char*,int*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
txt_fc_col(SCR *sp, int argc, ARGS **argv)
{
	ARGS **av;
	CHAR_T *p;
	GS *gp;
	size_t base, cnt, col, colwidth, numrows, numcols, prefix, row;
	int ac, nf, reset;
	char *np, *pp;
	size_t nlen;

	gp = sp->gp;

	/* Trim any directory prefix common to all of the files. */
	INT2CHAR(sp, argv[0]->bp, argv[0]->len + 1, np, nlen);
	if ((pp = strrchr(np, '/')) == NULL)
		prefix = 0;
	else {
		prefix = (pp - np) + 1;
		for (ac = argc - 1, av = argv + 1; ac > 0; --ac, ++av)
			if (av[0]->len < prefix ||
			    MEMCMP(av[0]->bp, argv[0]->bp, 
				   prefix)) {
				prefix = 0;
				break;
			}
	}

	/*
	 * Figure out the column width for the longest name.  Output is done on
	 * 6 character "tab" boundaries for no particular reason.  (Since we
	 * don't output tab characters, we ignore the terminal's tab settings.)
	 * Ignore the user's tab setting because we have no idea how reasonable
	 * it is.
	 */
	for (ac = argc, av = argv, colwidth = 0; ac > 0; --ac, ++av) {
		for (col = 0, p = av[0]->bp + prefix; *p != '\0'; ++p)
			col += KEY_COL(sp, *p);
		if (col > colwidth)
			colwidth = col;
	}
	colwidth += COL_OFF(colwidth, 6);

	/*
	 * Writing to the bottom line of the screen is always turned off when
	 * SC_TINPUT_INFO is set.  Turn it back on, we know what we're doing.
	 */
	if (F_ISSET(sp, SC_TINPUT_INFO)) {
		reset = 1;
		F_CLR(sp, SC_TINPUT_INFO);
	} else
		reset = 0;

#define	CHK_INTR							\
	if (F_ISSET(gp, G_INTERRUPTED))					\
		goto intr;

	/* If the largest file name is too large, just print them. */
	if (colwidth >= sp->cols) {
		for (ac = argc, av = argv; ac > 0; --ac, ++av) {
			INT2CHAR(sp, av[0]->bp+prefix, av[0]->len+1-prefix,
				 np, nlen);
			pp = msg_print(sp, np, &nf);
			(void)ex_printf(sp, "%s\n", pp);
			if (nf)
				FREE_SPACE(sp, pp, 0);
			if (F_ISSET(gp, G_INTERRUPTED))
				break;
		}
		CHK_INTR;
	} else {
		/* Figure out the number of columns. */
		numcols = (sp->cols - 1) / colwidth;
		if (argc > numcols) {
			numrows = argc / numcols;
			if (argc % numcols)
				++numrows;
		} else
			numrows = 1;

		/* Display the files in sorted order. */
		for (row = 0; row < numrows; ++row) {
			for (base = row, col = 0; col < numcols; ++col) {
				INT2CHAR(sp, argv[base]->bp+prefix, 
					argv[base]->len+1-prefix, np, nlen);
				pp = msg_print(sp, np, &nf);
				cnt = ex_printf(sp, "%s", pp);
				if (nf)
					FREE_SPACE(sp, pp, 0);
				CHK_INTR;
				if ((base += numrows) >= argc)
					break;
				(void)ex_printf(sp,
				    "%*s", (int)(colwidth - cnt), "");
				CHK_INTR;
			}
			(void)ex_puts(sp, "\n");
			CHK_INTR;
		}
		(void)ex_puts(sp, "\n");
		CHK_INTR;
	}
	(void)ex_fflush(sp);

	if (0) {
intr:		F_CLR(gp, G_INTERRUPTED);
	}
	if (reset)
		F_SET(sp, SC_TINPUT_INFO);

	return (0);
}