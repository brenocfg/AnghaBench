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
 int MTRANSPOSE ; 
 int NOTRIMENDCOL ; 
 int RECYCLE ; 
 int RIGHTADJUST ; 
 int SQUEEZE ; 
 int TRANSPOSE ; 
 double* colwidths ; 
 char** elem ; 
 char** endelem ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int flags ; 
 int /*<<< orphan*/  getptrs (char**) ; 
 double gutter ; 
 int icols ; 
 int irows ; 
 scalar_t__ malloc (int) ; 
 double maxlen ; 
 int nelem ; 
 int ocols ; 
 int orows ; 
 int owidth ; 
 double propgutter ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*,int,int) ; 

__attribute__((used)) static void
prepfile(void)
{
	char **ep;
	int  i;
	int  j;
	char **lp;
	int colw;
	int max;
	int n;

	if (!nelem)
		exit(0);
	gutter += maxlen * propgutter / 100.0;
	colw = maxlen + gutter;
	if (flags & MTRANSPOSE) {
		orows = icols;
		ocols = irows;
	}
	else if (orows == 0 && ocols == 0) {	/* decide rows and cols */
		ocols = owidth / colw;
		if (ocols == 0) {
			warnx("display width %d is less than column width %d",
					owidth, colw);
			ocols = 1;
		}
		if (ocols > nelem)
			ocols = nelem;
		orows = nelem / ocols + (nelem % ocols ? 1 : 0);
	}
	else if (orows == 0)			/* decide on rows */
		orows = nelem / ocols + (nelem % ocols ? 1 : 0);
	else if (ocols == 0)			/* decide on cols */
		ocols = nelem / orows + (nelem % orows ? 1 : 0);
	lp = elem + orows * ocols;
	while (lp > endelem) {
		getptrs(elem + nelem);
		lp = elem + orows * ocols;
	}
	if (flags & RECYCLE) {
		for (ep = elem + nelem; ep < lp; ep++)
			*ep = *(ep - nelem);
		nelem = lp - elem;
	}
	if (!(colwidths = (short *) malloc(ocols * sizeof(short))))
		errx(1, "malloc");
	if (flags & SQUEEZE) {
		ep = elem;
		if (flags & TRANSPOSE)
			for (i = 0; i < ocols; i++) {
				max = 0;
				for (j = 0; *ep != NULL && j < orows; j++)
					if ((n = strlen(*ep++)) > max)
						max = n;
				colwidths[i] = max + gutter;
			}
		else
			for (i = 0; i < ocols; i++) {
				max = 0;
				for (j = i; j < nelem; j += ocols)
					if ((n = strlen(ep[j])) > max)
						max = n;
				colwidths[i] = max + gutter;
			}
	}
	/*	for (i = 0; i < orows; i++) {
			for (j = i; j < nelem; j += orows)
				prints(ep[j], (j - i) / orows);
			putchar('\n');
		}
	else
		for (i = 0; i < orows; i++) {
			for (j = 0; j < ocols; j++)
				prints(*ep++, j);
			putchar('\n');
		}*/
	else
		for (i = 0; i < ocols; i++)
			colwidths[i] = colw;
	if (!(flags & NOTRIMENDCOL)) {
		if (flags & RIGHTADJUST)
			colwidths[0] -= gutter;
		else
			colwidths[ocols - 1] = 0;
	}
	n = orows * ocols;
	if (n > nelem && (flags & RECYCLE))
		nelem = n;
	/*for (i = 0; i < ocols; i++)
		warnx("%d is colwidths, nelem %d", colwidths[i], nelem);*/
}