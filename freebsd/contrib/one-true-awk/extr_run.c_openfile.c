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
struct files {char* fname; int mode; int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int APPEND ; 
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int FFLUSH ; 
 int FOPEN_MAX ; 
 int GT ; 
 int LE ; 
 int LT ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 struct files* files ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  memset (struct files*,int /*<<< orphan*/ ,int) ; 
 int nfiles ; 
 int /*<<< orphan*/ * popen (char const*,char*) ; 
 struct files* realloc (struct files*,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* tostring (char const*) ; 

FILE *openfile(int a, const char *us)
{
	const char *s = us;
	int i, m;
	FILE *fp = NULL;

	if (*s == '\0')
		FATAL("null file name in print or getline");
	for (i=0; i < nfiles; i++)
		if (files[i].fname && strcmp(s, files[i].fname) == 0) {
			if (a == files[i].mode || (a==APPEND && files[i].mode==GT))
				return files[i].fp;
			if (a == FFLUSH)
				return files[i].fp;
		}
	if (a == FFLUSH)	/* didn't find it, so don't create it! */
		return NULL;

	for (i=0; i < nfiles; i++)
		if (files[i].fp == NULL)
			break;
	if (i >= nfiles) {
		struct files *nf;
		int nnf = nfiles + FOPEN_MAX;
		nf = realloc(files, nnf * sizeof(*nf));
		if (nf == NULL)
			FATAL("cannot grow files for %s and %d files", s, nnf);
		memset(&nf[nfiles], 0, FOPEN_MAX * sizeof(*nf));
		nfiles = nnf;
		files = nf;
	}
	fflush(stdout);	/* force a semblance of order */
	m = a;
	if (a == GT) {
		fp = fopen(s, "w");
	} else if (a == APPEND) {
		fp = fopen(s, "a");
		m = GT;	/* so can mix > and >> */
	} else if (a == '|') {	/* output pipe */
		fp = popen(s, "w");
	} else if (a == LE) {	/* input pipe */
		fp = popen(s, "r");
	} else if (a == LT) {	/* getline <file */
		fp = strcmp(s, "-") == 0 ? stdin : fopen(s, "r");	/* "-" is stdin */
	} else	/* can't happen */
		FATAL("illegal redirection %d", a);
	if (fp != NULL) {
		files[i].fname = tostring(s);
		files[i].fp = fp;
		files[i].mode = m;
	}
	return fp;
}