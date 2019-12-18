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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ inchar ; 
 int ingap ; 
 int ungetc (int,int /*<<< orphan*/ *) ; 

int
inln(FILE *inf, char *buf, int lim, int *cps, int trnc, int *mor)
{
	int col;
	int gap = ingap;
	int ch = EOF;
	char *ptbuf;
	int chk = (int)inchar;

	ptbuf = buf;

	if (gap) {
		/*
		 * expanding input option
		 */
		while ((--lim >= 0) && ((ch = getc(inf)) != EOF)) {
			/*
			 * is this the input "tab" char
			 */
			if (ch == chk) {
				/*
				 * expand to number of spaces
				 */
				col = (ptbuf - buf) + *cps;
				col = gap - (col % gap);

				/*
				 * if more than this line, push back
				 */
				if ((col > lim) && (ungetc(ch, inf) == EOF))
					return(1);

				/*
				 * expand to spaces
				 */
				while ((--col >= 0) && (--lim >= 0))
					*ptbuf++ = ' ';
				continue;
			}
			if (ch == '\n')
				break;
			*ptbuf++ = ch;
		}
	} else {
		/*
		 * no expansion
		 */
		while ((--lim >= 0) && ((ch = getc(inf)) != EOF)) {
			if (ch == '\n')
				break;
			*ptbuf++ = ch;
		}
	}
	col = ptbuf - buf;
	if (ch == EOF) {
		*mor = 0;
		*cps = 0;
		if (!col)
			return(-1);
		return(col);
	}
	if (ch == '\n') {
		/*
		 * entire line processed
		 */
		*mor = 0;
		*cps = 0;
		return(col);
	}

	/*
	 * line was larger than limit
	 */
	if (trnc) {
		/*
		 * throw away rest of line
		 */
		while ((ch = getc(inf)) != EOF) {
			if (ch == '\n')
				break;
		}
		*cps = 0;
		*mor = 0;
	} else {
		/*
		 * save column offset if not truncated
		 */
		*cps += col;
		*mor = 1;
	}

	return(col);
}