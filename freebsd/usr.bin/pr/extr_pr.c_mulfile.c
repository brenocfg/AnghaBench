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
 scalar_t__ HDBUF ; 
 int /*<<< orphan*/  addnum (char*,int,int) ; 
 int clcnt ; 
 int colwd ; 
 int eoptind ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int inln (int /*<<< orphan*/ *,char*,int,int*,int,int*) ; 
 scalar_t__ inskip (int /*<<< orphan*/ *,int,int) ; 
 int lines ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  mfail () ; 
 int /*<<< orphan*/  nmchar ; 
 int nmwd ; 
 int /*<<< orphan*/  nohead ; 
 int /*<<< orphan*/ * nxtfile (int,char**,char const**,char*,int) ; 
 int offst ; 
 scalar_t__ otln (char*,int,int*,int*,int /*<<< orphan*/ ) ; 
 int pgnm ; 
 int pgwd ; 
 scalar_t__ prhead (char*,char const*,int) ; 
 scalar_t__ prtail (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schar ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ttypause (int) ; 

int
mulfile(int argc, char *argv[])
{
	char *ptbf;
	int j;
	int pln;
	int cnt;
	char *lstdat;
	int i;
	FILE **fbuf = NULL;
	int actf;
	int lncnt;
	int col;
	int pagecnt;
	int fproc;
	char *buf = NULL;
	char *hbuf = NULL;
	char *ohbuf;
	const char *fname;
	int ips = 0;
	int cps = 0;
	int ops = 0;
	int mor = 0;
	int retval = 1;

	/*
	 * array of FILE *, one for each operand
	 */
	if ((fbuf = (FILE **)malloc((unsigned)clcnt*sizeof(FILE *))) == NULL) {
		mfail();
		goto out;
	}

	/*
	 * page header
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		mfail();
		goto out;
	}
	ohbuf = hbuf + offst;

	/*
	 * do not know how many columns yet. The number of operands provide an
	 * upper bound on the number of columns. We use the number of files
	 * we can open successfully to set the number of columns. The operation
	 * of the merge operation (-m) in relation to unsuccessful file opens
	 * is unspecified by posix.
	 */
	j = 0;
	while (j < clcnt) {
		if ((fbuf[j] = nxtfile(argc, argv, &fname, ohbuf, 1)) == NULL)
			break;
		if (pgnm && (inskip(fbuf[j], pgnm, lines)))
			fbuf[j] = NULL;
		++j;
	}

	/*
	 * if no files, exit
	 */
	if (!j)
		goto out;

	/*
	 * calculate page boundaries based on open file count
	 */
	clcnt = j;
	if (nmwd) {
		colwd = (pgwd - clcnt - nmwd)/clcnt;
		pgwd = ((colwd + 1) * clcnt) - nmwd - 2;
	} else {
		colwd = (pgwd + 1 - clcnt)/clcnt;
		pgwd = ((colwd + 1) * clcnt) - 1;
	}
	if (colwd < 1) {
		(void)fprintf(err,
		  "pr: page width too small for %d columns\n", clcnt);
		goto out;
	}
	actf = clcnt;
	col = colwd + 1;

	/*
	 * line buffer
	 */
	if ((buf = malloc((unsigned)(pgwd+offst+1)*sizeof(char))) == NULL) {
		mfail();
		goto out;
	}
	if (offst) {
		(void)memset(buf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}
	if (pgnm)
		pagecnt = pgnm;
	else
		pagecnt = 1;
	lncnt = 0;

	/*
	 * continue to loop while any file still has data
	 */
	while (actf > 0) {
		ttypause(pagecnt);

		/*
		 * loop by line
		 */
		for (i = 0; i < lines; ++i) {
			ptbf = buf + offst;
			lstdat = ptbf;
			if (nmwd) {
				/*
				 * add line number to line
				 */
				addnum(ptbf, nmwd, ++lncnt);
				ptbf += nmwd;
				*ptbf++ = nmchar;
			}
			j = 0;
			fproc = 0;

			/*
			 * loop by column
			 */
			for (j = 0; j < clcnt; ++j) {
				if (fbuf[j] == NULL) {
					/*
					 * empty column; EOF
					 */
					cnt = 0;
				} else if ((cnt = inln(fbuf[j], ptbf, colwd,
							&cps, 1, &mor)) < 0) {
					/*
					 * EOF hit; no data
					 */
					if (fbuf[j] != stdin)
						(void)fclose(fbuf[j]);
					fbuf[j] = NULL;
					--actf;
					cnt = 0;
				} else {
					/*
					 * process file data
					 */
					ptbf += cnt;
					lstdat = ptbf;
					fproc++;
				}

				/*
				 * if last ACTIVE column, done with line
				 */
				if (fproc >= actf)
					break;

				/*
				 * pad to end of column
				 */
				if (sflag) {
					*ptbf++ = schar;
				} else if ((pln = col - cnt) > 0) {
					(void)memset(ptbf, (int)' ', pln);
					ptbf += pln;
				}
			}

			/*
			 * calculate data in line
			 */
			if ((j = lstdat - buf) <= offst)
				break;

			if (!i && !nohead && prhead(hbuf, fname, pagecnt))
				goto out;

			/*
			 * output line
			 */
			if (otln(buf, j, &ips, &ops, 0))
				goto out;

			/*
			 * if no more active files, done
			 */
			if (actf <= 0) {
				++i;
				break;
			}
		}

		/*
		 * pad to end of page
		 */
		if (i && prtail(lines-i, 0))
			goto out;
		++pagecnt;
	}
	if (eoptind < argc)
		goto out;
	retval = 0;
out:
	free(buf);
	free(hbuf);
	free(fbuf);
	return(retval);
}