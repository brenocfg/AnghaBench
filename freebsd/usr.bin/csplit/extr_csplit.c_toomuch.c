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
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  currfile ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ftello (int /*<<< orphan*/ *) ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 long lineno ; 
 int /*<<< orphan*/ * overfile ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ truncofs ; 

__attribute__((used)) static void
toomuch(FILE *ofp, long n)
{
	char buf[BUFSIZ];
	size_t i, nread;

	if (overfile != NULL) {
		/*
		 * Truncate the previous file we overflowed into back to
		 * the correct length, close it.
		 */
		if (fflush(overfile) != 0)
			err(1, "overflow");
		if (ftruncate(fileno(overfile), truncofs) != 0)
			err(1, "overflow");
		if (fclose(overfile) != 0)
			err(1, "overflow");
		overfile = NULL;
	}

	if (n == 0)
		/* Just tidying up */
		return;

	lineno -= n;

	/*
	 * Wind the overflow file backwards to `n' lines before the
	 * current one.
	 */
	do {
		if (ftello(ofp) < (off_t)sizeof(buf))
			rewind(ofp);
		else
			fseeko(ofp, -(off_t)sizeof(buf), SEEK_CUR);
		if (ferror(ofp))
			errx(1, "%s: can't seek", currfile);
		if ((nread = fread(buf, 1, sizeof(buf), ofp)) == 0)
			errx(1, "can't read overflowed output");
		if (fseeko(ofp, -(off_t)nread, SEEK_CUR) != 0)
			err(1, "%s", currfile);
		for (i = 1; i <= nread; i++)
			if (buf[nread - i] == '\n' && n-- == 0)
				break;
		if (ftello(ofp) == 0)
			break;
	} while (n > 0);
	if (fseeko(ofp, nread - i + 1, SEEK_CUR) != 0)
		err(1, "%s", currfile);

	/*
	 * get_line() will read from here. Next call will truncate to
	 * truncofs in this file.
	 */
	overfile = ofp;
	truncofs = ftello(overfile);
}