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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/ ** list ; 
 int maxlength ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int roundup (int,int /*<<< orphan*/ ) ; 
 int termwidth ; 
 scalar_t__ width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
c_columnate(void)
{
	int chcnt, col, cnt, endcol, numcols;
	wchar_t **lp;

	numcols = termwidth / maxlength;
	endcol = maxlength;
	for (chcnt = col = 0, lp = list;; ++lp) {
		wprintf(L"%ls", *lp);
		chcnt += width(*lp);
		if (!--entries)
			break;
		if (++col == numcols) {
			chcnt = col = 0;
			endcol = maxlength;
			putwchar('\n');
		} else {
			while ((cnt = roundup(chcnt + 1, TAB)) <= endcol) {
				(void)putwchar('\t');
				chcnt = cnt;
			}
			endcol += maxlength;
		}
	}
	if (chcnt)
		putwchar('\n');
}