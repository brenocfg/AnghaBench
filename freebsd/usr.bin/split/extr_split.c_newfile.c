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
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_IOERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int LONG_MAX ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int file_open ; 
 int fileno (int /*<<< orphan*/ ) ; 
 char* fname ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int ofd ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 
 long sufflen ; 

__attribute__((used)) static void
newfile(void)
{
	long i, maxfiles, tfnum;
	static long fnum;
	static char *fpnt;
	char beg, end;
	int pattlen;

	if (ofd == -1) {
		if (fname[0] == '\0') {
			fname[0] = 'x';
			fpnt = fname + 1;
		} else {
			fpnt = fname + strlen(fname);
		}
		ofd = fileno(stdout);
	}

	if (dflag) {
		beg = '0';
		end = '9';
	}
	else {
		beg = 'a';
		end = 'z';
	}
	pattlen = end - beg + 1;

	/* maxfiles = pattlen^sufflen, but don't use libm. */
	for (maxfiles = 1, i = 0; i < sufflen; i++)
		if (LONG_MAX / pattlen < maxfiles)
			errx(EX_USAGE, "suffix is too long (max %ld)", i);
		else
			maxfiles *= pattlen;

	if (fnum == maxfiles)
		errx(EX_DATAERR, "too many files");

	/* Generate suffix of sufflen letters */
	tfnum = fnum;
	i = sufflen - 1;
	do {
		fpnt[i] = tfnum % pattlen + beg;
		tfnum /= pattlen;
	} while (i-- > 0);
	fpnt[sufflen] = '\0';

	++fnum;
	if (!freopen(fname, "w", stdout))
		err(EX_IOERR, "%s", fname);
	file_open = 1;
}