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
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAPH_READ ; 
 int /*<<< orphan*/  DIFF_EXIT ; 
 int EOF ; 
 int /*<<< orphan*/  ERR_EXIT ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stream (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diffmsg (char const*,char const*,int,int) ; 
 int /*<<< orphan*/  eofmsg (char const*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  printf (char*,long long,int,int) ; 
 scalar_t__ xflag ; 

void
c_special(int fd1, const char *file1, off_t skip1,
    int fd2, const char *file2, off_t skip2)
{
	int ch1, ch2;
	off_t byte, line;
	FILE *fp1, *fp2;
	int dfound;

	if (caph_limit_stream(fd1, CAPH_READ) < 0)
		err(ERR_EXIT, "caph_limit_stream(%s)", file1);
	if (caph_limit_stream(fd2, CAPH_READ) < 0)
		err(ERR_EXIT, "caph_limit_stream(%s)", file2);
	if (caph_enter() < 0)
		err(ERR_EXIT, "unable to enter capability mode");

	if ((fp1 = fdopen(fd1, "r")) == NULL)
		err(ERR_EXIT, "%s", file1);
	if ((fp2 = fdopen(fd2, "r")) == NULL)
		err(ERR_EXIT, "%s", file2);

	dfound = 0;
	while (skip1--)
		if (getc(fp1) == EOF)
			goto eof;
	while (skip2--)
		if (getc(fp2) == EOF)
			goto eof;

	for (byte = line = 1;; ++byte) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
		if (ch1 == EOF || ch2 == EOF)
			break;
		if (ch1 != ch2) {
			if (xflag) {
				dfound = 1;
				(void)printf("%08llx %02x %02x\n",
				    (long long)byte - 1, ch1, ch2);
			} else if (lflag) {
				dfound = 1;
				(void)printf("%6lld %3o %3o\n",
				    (long long)byte, ch1, ch2);
			} else {
				diffmsg(file1, file2, byte, line);
				/* NOTREACHED */
			}
		}
		if (ch1 == '\n')
			++line;
	}

eof:	if (ferror(fp1))
		err(ERR_EXIT, "%s", file1);
	if (ferror(fp2))
		err(ERR_EXIT, "%s", file2);
	if (feof(fp1)) {
		if (!feof(fp2))
			eofmsg(file1);
	} else
		if (feof(fp2))
			eofmsg(file2);
	fclose(fp2);
	fclose(fp1);
	if (dfound)
		exit(DIFF_EXIT);
}