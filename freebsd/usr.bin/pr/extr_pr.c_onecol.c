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
 scalar_t__ LBUF ; 
 int /*<<< orphan*/  addnum (char*,int,int) ; 
 int eoptind ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int inln (int /*<<< orphan*/ *,char*,scalar_t__,int*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ inskip (int /*<<< orphan*/ *,int,int) ; 
 int lines ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  mfail () ; 
 char nmchar ; 
 int nmwd ; 
 int /*<<< orphan*/  nohead ; 
 int /*<<< orphan*/ * nxtfile (int,char**,char const**,char*,int /*<<< orphan*/ ) ; 
 int offst ; 
 scalar_t__ otln (char*,int,int*,int*,int) ; 
 int pgnm ; 
 scalar_t__ prhead (char*,char const*,int) ; 
 scalar_t__ prtail (int,int) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  ttypause (int) ; 

int
onecol(int argc, char *argv[])
{
	int cnt = -1;
	int off;
	int lrgln;
	int linecnt;
	int num;
	int lncnt;
	int pagecnt;
	int ips;
	int ops;
	int cps;
	char *obuf;
	char *lbuf;
	char *nbuf;
	char *hbuf;
	char *ohbuf;
	FILE *inf;
	const char *fname;
	int mor;

	if (nmwd)
		num = nmwd + 1;
	else
		num = 0;
	off = num + offst;

	/*
	 * allocate line buffer
	 */
	if ((obuf = malloc((unsigned)(LBUF + off)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	/*
	 * allocate header buffer
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		free(obuf);
		mfail();
		return(1);
	}

	ohbuf = hbuf + offst;
	nbuf = obuf + offst;
	lbuf = nbuf + num;
	if (num)
		nbuf[--num] = nmchar;
	if (offst) {
		(void)memset(obuf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}

	/*
	 * loop by file
	 */
	while ((inf = nxtfile(argc, argv, &fname, ohbuf, 0)) != NULL) {
		if (pgnm) {
			/*
			 * skip to specified page
			 */
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
			linecnt = 0;
			lrgln = 0;
			ops = 0;
			ips = 0;
			cps = 0;

			ttypause(pagecnt);

			/*
			 * loop by line
			 */
			while (linecnt < lines) {
				/*
				 * input next line
				 */
				if ((cnt = inln(inf,lbuf,LBUF,&cps,0,&mor)) < 0)
					break;
				if (!linecnt && !nohead &&
					prhead(hbuf, fname, pagecnt))
					goto err;

				/*
				 * start of new line.
				 */
				if (!lrgln) {
					if (num)
						addnum(nbuf, num, ++lncnt);
					if (otln(obuf,cnt+off, &ips, &ops, mor))
						goto err;
				} else if (otln(lbuf, cnt, &ips, &ops, mor))
					goto err;

				/*
				 * if line bigger than buffer, get more
				 */
				if (mor) {
					lrgln = 1;
					continue;
				}

				/*
				 * whole line rcvd. reset tab proc. state
				 */
				++linecnt;
				lrgln = 0;
				ops = 0;
				ips = 0;
			}

			/*
			 * fill to end of page
			 */
			if (linecnt && prtail(lines-linecnt-lrgln, lrgln))
				goto err;

			/*
			 * On EOF go to next file
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
	free(obuf);
	return(0);
err:
	free(hbuf);
	free(obuf);
	return(1);
}