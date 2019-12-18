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
typedef  int /*<<< orphan*/  regex_t ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int REG_BASIC ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  currfile ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 char* get_line () ; 
 int /*<<< orphan*/ * newfile () ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sflag ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char const) ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/ * tmpfile () ; 
 int /*<<< orphan*/  toomuch (int /*<<< orphan*/ *,long) ; 
 scalar_t__ truncofs ; 

__attribute__((used)) static void
do_rexp(const char *expr)
{
	regex_t cre;
	intmax_t nwritten;
	long ofs;
	int first;
	char *ecopy, *ep, *p, *pofs, *re;
	FILE *ofp;

	if ((ecopy = strdup(expr)) == NULL)
		err(1, "strdup");

	re = ecopy + 1;
	if ((pofs = strrchr(ecopy, *expr)) == NULL || pofs[-1] == '\\')
		errx(1, "%s: missing trailing %c", expr, *expr);
	*pofs++ = '\0';

	if (*pofs != '\0') {
		errno = 0;
		ofs = strtol(pofs, &ep, 10);
		if (*ep != '\0' || errno != 0)
			errx(1, "%s: bad offset", pofs);
	} else
		ofs = 0;

	if (regcomp(&cre, re, REG_BASIC|REG_NOSUB) != 0)
		errx(1, "%s: bad regular expression", re);

	if (*expr == '/')
		/* /regexp/: Save results to a file. */
		ofp = newfile();
	else {
		/* %regexp%: Make a temporary file for overflow. */
		if ((ofp = tmpfile()) == NULL)
			err(1, "tmpfile");
	}

	/* Read and output lines until we get a match. */
	first = 1;
	while ((p = get_line()) != NULL) {
		if (fputs(p, ofp) == EOF)
			break;
		if (!first && regexec(&cre, p, 0, NULL, 0) == 0)
			break;
		first = 0;
	}

	if (p == NULL) {
		toomuch(NULL, 0);
		errx(1, "%s: no match", re);
	}

	if (ofs <= 0) {
		/*
		 * Negative (or zero) offset: throw back any lines we should
		 * not have read yet.
		  */
		if (p != NULL) {
			toomuch(ofp, -ofs + 1);
			nwritten = (intmax_t)truncofs;
		} else
			nwritten = (intmax_t)ftello(ofp);
	} else {
		/*
		 * Positive offset: copy the requested number of lines
		 * after the match.
		 */
		while (--ofs > 0 && (p = get_line()) != NULL)
			fputs(p, ofp);
		toomuch(NULL, 0);
		nwritten = (intmax_t)ftello(ofp);
		if (fclose(ofp) != 0)
			err(1, "%s", currfile);
	}

	if (!sflag && *expr == '/')
		printf("%jd\n", nwritten);

	regfree(&cre);
	free(ecopy);
}