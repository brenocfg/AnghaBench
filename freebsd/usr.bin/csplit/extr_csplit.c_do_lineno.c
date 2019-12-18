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
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  currfile ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 char* get_line () ; 
 long lineno ; 
 int maxfiles ; 
 int /*<<< orphan*/ * newfile () ; 
 int nfiles ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reps ; 
 int /*<<< orphan*/  sflag ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static void
do_lineno(const char *expr)
{
	long lastline, tgtline;
	char *ep, *p;
	FILE *ofp;

	errno = 0;
	tgtline = strtol(expr, &ep, 10);
	if (tgtline <= 0 || errno != 0 || *ep != '\0')
		errx(1, "%s: bad line number", expr);
	lastline = tgtline;
	if (lastline <= lineno)
		errx(1, "%s: can't go backwards", expr);

	while (nfiles < maxfiles - 1) {
		ofp = newfile();
		while (lineno + 1 != lastline) {
			if ((p = get_line()) == NULL)
				errx(1, "%ld: out of range", lastline);
			if (fputs(p, ofp) == EOF)
				break;
		}
		if (!sflag)
			printf("%jd\n", (intmax_t)ftello(ofp));
		if (fclose(ofp) != 0)
			err(1, "%s", currfile);
		if (reps-- == 0)
			break;
		lastline += tgtline;
	} 
}