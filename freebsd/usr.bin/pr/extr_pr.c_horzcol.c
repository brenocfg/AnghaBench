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
 int /*<<< orphan*/  addnum (char*,scalar_t__,int) ; 
 int clcnt ; 
 int colwd ; 
 int eoptind ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int inln (int /*<<< orphan*/ *,char*,int,int*,int,int*) ; 
 scalar_t__ inskip (int /*<<< orphan*/ *,int,int) ; 
 int lines ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  mfail () ; 
 int /*<<< orphan*/  nmchar ; 
 scalar_t__ nmwd ; 
 int /*<<< orphan*/  nohead ; 
 int /*<<< orphan*/ * nxtfile (int,char**,char const**,char*,int /*<<< orphan*/ ) ; 
 int offst ; 
 scalar_t__ otln (char*,int,int*,int*,int /*<<< orphan*/ ) ; 
 int pgnm ; 
 scalar_t__ pgwd ; 
 scalar_t__ prhead (char*,char const*,int) ; 
 scalar_t__ prtail (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schar ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ttypause (int) ; 

int
horzcol(int argc, char *argv[])
{
	char *ptbf;
	int pln;
	int cnt = -1;
	char *lstdat;
	int col = colwd + 1;
	int j;
	int i;
	int lncnt;
	int pagecnt;
	char *buf;
	char *hbuf;
	char *ohbuf;
	const char *fname;
	FILE *inf;
	int ips = 0;
	int cps = 0;
	int ops = 0;
	int mor = 0;

	if ((buf = malloc((unsigned)(pgwd+offst+1)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}

	/*
	 * page header
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		free(buf);
		mfail();
		return(1);
	}
	ohbuf = hbuf + offst;
	if (offst) {
		(void)memset(buf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}

	/*
	 * loop by file
	 */
	while ((inf = nxtfile(argc, argv, &fname, ohbuf, 0)) != NULL) {
		if (pgnm) {
			if (inskip(inf, pgnm, lines))
				continue;
			pagecnt = pgnm;
		} else
			pagecnt = 1;
		lncnt = 0;

		/*
		 * loop by page
		 */
		for(;;) {
			ttypause(pagecnt);

			/*
			 * loop by line
			 */
			for (i = 0; i < lines; ++i) {
				ptbf = buf + offst;
				lstdat = ptbf;
				j = 0;
				/*
				 * loop by col
				 */
				for(;;) {
					if (nmwd) {
						/*
						 * add number to column
						 */
						addnum(ptbf, nmwd, ++lncnt);
						ptbf += nmwd;
						*ptbf++ = nmchar;
					}
					/*
					 * input line
					 */
					if ((cnt = inln(inf,ptbf,colwd,&cps,1,
							&mor)) < 0)
						break;
					ptbf += cnt;
					lstdat = ptbf;

					/*
					 * if last line skip padding
					 */
					if (++j >= clcnt)
						break;

					/*
					 * pad to end of column
					 */
					if (sflag)
						*ptbf++ = schar;
					else if ((pln = col - cnt) > 0) {
						(void)memset(ptbf,(int)' ',pln);
						ptbf += pln;
					}
				}

				/*
				 * determine line length
				 */
				if ((j = lstdat - buf) <= offst)
					break;
				if (!i && !nohead &&
					prhead(hbuf, fname, pagecnt))
					goto err;
				/*
				 * output line
				 */
				if (otln(buf, j, &ips, &ops, 0))
					goto err;
			}

			/*
			 * pad to end of page
			 */
			if (i && prtail(lines-i, 0))
				goto err;

			/*
			 * if EOF go to next file
			 */
			if (cnt < 0)
				break;
			++pagecnt;
		}
		if (inf != stdin)
			(void)fclose(inf);
	}
	if (eoptind < argc)
		goto err;
	free(hbuf);
	free(buf);
	return(0);
err:
	free(hbuf);
	free(buf);
	return(1);
}