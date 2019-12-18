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
 int EOF ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ Iflag ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  enqueue (char*,char,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 size_t file1ln ; 
 size_t file2ln ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  printa (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  printd (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  processq () ; 
 size_t strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 char* xfgets (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parsecmd(FILE *diffpipe, FILE *file1, FILE *file2)
{
	size_t file1start, file1end, file2start, file2end, n;
	/* ed command line and pointer to characters in line */
	char *line, *p, *q;
	const char *errstr;
	char c, cmd;

	/* Read ed command. */
	if (!(line = xfgets(diffpipe)))
		return (EOF);

	p = line;
	/* Go to character after line number. */
	while (isdigit(*p))
		++p;
	c = *p;
	*p++ = 0;
	file1start = strtonum(line, 0, INT_MAX, &errstr);
	if (errstr)
		errx(2, "file1 start is %s: %s", errstr, line);

	/* A range is specified for file1. */
	if (c == ',') {
		q = p;
		/* Go to character after file2end. */
		while (isdigit(*p))
			++p;
		c = *p;
		*p++ = 0;
		file1end = strtonum(q, 0, INT_MAX, &errstr);
		if (errstr)
			errx(2, "file1 end is %s: %s", errstr, line);
		if (file1start > file1end)
			errx(2, "invalid line range in file1: %s", line);
	} else
		file1end = file1start;

	cmd = c;
	/* Check that cmd is valid. */
	if (!(cmd == 'a' || cmd == 'c' || cmd == 'd'))
		errx(2, "ed command not recognized: %c: %s", cmd, line);

	q = p;
	/* Go to character after line number. */
	while (isdigit(*p))
		++p;
	c = *p;
	*p++ = 0;
	file2start = strtonum(q, 0, INT_MAX, &errstr);
	if (errstr)
		errx(2, "file2 start is %s: %s", errstr, line);

	/*
	 * There should either be a comma signifying a second line
	 * number or the line should just end here.
	 */
	if (c != ',' && c != '\0')
		errx(2, "invalid line range in file2: %c: %s", c, line);

	if (c == ',') {

		file2end = strtonum(p, 0, INT_MAX, &errstr);
		if (errstr)
			errx(2, "file2 end is %s: %s", errstr, line);
		if (file2start >= file2end)
			errx(2, "invalid line range in file2: %s", line);
	} else
		file2end = file2start;

	/* Appends happen _after_ stated line. */
	if (cmd == 'a') {
		if (file1start != file1end)
			errx(2, "append cannot have a file1 range: %s",
			    line);
		if (file1start == SIZE_MAX)
			errx(2, "file1 line range too high: %s", line);
		file1start = ++file1end;
	}
	/*
	 * I'm not sure what the deal is with the line numbers for
	 * deletes, though.
	 */
	else if (cmd == 'd') {
		if (file2start != file2end)
			errx(2, "delete cannot have a file2 range: %s",
			    line);
		if (file2start == SIZE_MAX)
			errx(2, "file2 line range too high: %s", line);
		file2start = ++file2end;
	}

	/*
	 * Continue reading file1 and file2 until we reach line numbers
	 * specified by diff.  Should only happen with -I flag.
	 */
	for (; file1ln < file1start && file2ln < file2start;
	    ++file1ln, ++file2ln) {
		char *s1, *s2;

		if (!(s1 = xfgets(file1)))
			errx(2, "file1 shorter than expected");
		if (!(s2 = xfgets(file2)))
			errx(2, "file2 shorter than expected");

		/* If the -l flag was specified, print only left column. */
		if (lflag) {
			free(s2);
			/*
			 * XXX - If -l and -I are both specified, all
			 * unchanged or ignored lines are shown with a
			 * `(' divider.  This matches GNU sdiff, but I
			 * believe it is a bug.  Just check out:
			 * gsdiff -l -I '^$' samefile samefile.
			 */
			if (Iflag)
				enqueue(s1, '(', NULL);
			else
				enqueue(s1, ' ', NULL);
		} else
			enqueue(s1, ' ', s2);
	}
	/* Ignore deleted lines. */
	for (; file1ln < file1start; ++file1ln) {
		char *s;

		if (!(s = xfgets(file1)))
			errx(2, "file1 shorter than expected");

		enqueue(s, '(', NULL);
	}
	/* Ignore added lines. */
	for (; file2ln < file2start; ++file2ln) {
		char *s;

		if (!(s = xfgets(file2)))
			errx(2, "file2 shorter than expected");

		/* If -l flag was given, don't print right column. */
		if (lflag)
			free(s);
		else
			enqueue(NULL, ')', s);
	}

	/* Process unmodified or skipped lines. */
	processq();

	switch (cmd) {
	case 'a':
		printa(file2, file2end);
		n = file2end - file2start + 1;
		break;
	case 'c':
		printc(file1, file1end, file2, file2end);
		n = file1end - file1start + 1 + 1 + file2end - file2start + 1;
		break;
	case 'd':
		printd(file1, file1end);
		n = file1end - file1start + 1;
		break;
	default:
		errx(2, "invalid diff command: %c: %s", cmd, line);
	}
	free(line);

	/* Skip to next ed line. */
	while (n--) {
		if (!(line = xfgets(diffpipe)))
			errx(2, "diff ended early");
		free(line);
	}

	return (0);
}