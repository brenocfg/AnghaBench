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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgetwln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

int
main(int argc, char *argv[])
{
	const char *filename;
	wchar_t *p, *t;
	FILE *fp;
	size_t len;
	int ch, rval;

	setlocale(LC_ALL, "");

	while ((ch = getopt(argc, argv, "")) != -1)
		switch(ch) {
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	fp = stdin;
	filename = "stdin";
	rval = 0;
	do {
		if (*argv) {
			if ((fp = fopen(*argv, "r")) == NULL) {
				warn("%s", *argv);
				rval = 1;
				++argv;
				continue;
			}
			filename = *argv++;
		}
		while ((p = fgetwln(fp, &len)) != NULL) {
			if (p[len - 1] == '\n')
				--len;
			for (t = p + len - 1; t >= p; --t)
				putwchar(*t);
			putwchar('\n');
		}
		if (ferror(fp)) {
			warn("%s", filename);
			clearerr(fp);
			rval = 1;
		}
		(void)fclose(fp);
	} while(*argv);
	exit(rval);
}