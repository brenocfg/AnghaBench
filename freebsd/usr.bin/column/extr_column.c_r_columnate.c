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
 int /*<<< orphan*/  TAB ; 
 int entries ; 
 int /*<<< orphan*/ * list ; 
 int maxlength ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 
 int termwidth ; 
 scalar_t__ width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r_columnate(void)
{
	int base, chcnt, cnt, col, endcol, numcols, numrows, row;

	numcols = termwidth / maxlength;
	numrows = entries / numcols;
	if (entries % numcols)
		++numrows;

	for (row = 0; row < numrows; ++row) {
		endcol = maxlength;
		for (base = row, chcnt = col = 0; col < numcols; ++col) {
			wprintf(L"%ls", list[base]);
			chcnt += width(list[base]);
			if ((base += numrows) >= entries)
				break;
			while ((cnt = roundup(chcnt + 1, TAB)) <= endcol) {
				(void)putwchar('\t');
				chcnt = cnt;
			}
			endcol += maxlength;
		}
		putwchar('\n');
	}
}