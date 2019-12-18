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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 

int
inskip(FILE *inf, int pgcnt, int lncnt)
{
	int c;
	int cnt;

	while(--pgcnt > 0) {
		cnt = lncnt;
		while ((c = getc(inf)) != EOF) {
			if ((c == '\n') && (--cnt == 0))
				break;
		}
		if (c == EOF) {
			if (inf != stdin)
				(void)fclose(inf);
			return(1);
		}
	}
	return(0);
}