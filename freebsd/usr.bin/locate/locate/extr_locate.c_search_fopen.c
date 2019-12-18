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
 int /*<<< orphan*/  SEEK_SET ; 
 long cputime () ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ f_icase ; 
 scalar_t__ f_statistic ; 
 scalar_t__ f_stdin ; 
 int /*<<< orphan*/  fastfind (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fastfind_icase (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statistic (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

void
search_fopen(char *db, char **s)
{
	FILE *fp;
#ifdef DEBUG
        long t0;
#endif
	       
	/* can only read stdin once */
	if (f_stdin) { 
		fp = stdin;
		if (*(s+1) != NULL) {
			warnx("read database from stdin, use only `%s' as pattern", *s);
			*(s+1) = NULL;
		}
	} 
	else if ((fp = fopen(db, "r")) == NULL)
		err(1,  "`%s'", db);

	/* count only chars or lines */
	if (f_statistic) {
		statistic(fp, db);
		(void)fclose(fp);
		return;
	}

	/* foreach search string ... */
	while(*s != NULL) {
#ifdef DEBUG
		t0 = cputime();
#endif
		if (!f_stdin &&
		    fseek(fp, (long)0, SEEK_SET) == -1)
			err(1, "fseek to begin of ``%s''\n", db);

		if (f_icase)
			fastfind_icase(fp, *s, db);
		else
			fastfind(fp, *s, db);
#ifdef DEBUG
		warnx("fastfind %ld ms", cputime () - t0);
#endif
		s++;
	} 
	(void)fclose(fp);
}