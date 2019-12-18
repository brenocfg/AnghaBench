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
typedef  int wint_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int WEOF ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getstops (char*) ; 
 int getwchar () ; 
 scalar_t__ isdigit (unsigned char) ; 
 int nstops ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  putwchar (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int* tabstops ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int wcwidth (int) ; 

int
main(int argc, char *argv[])
{
	const char *curfile;
	wint_t wc;
	int c, column;
	int n;
	int rval;
	int width;

	setlocale(LC_CTYPE, "");

	/* handle obsolete syntax */
	while (argc > 1 && argv[1][0] == '-' &&
	    isdigit((unsigned char)argv[1][1])) {
		getstops(&argv[1][1]);
		argc--; argv++;
	}

	while ((c = getopt (argc, argv, "t:")) != -1) {
		switch (c) {
		case 't':
			getstops(optarg);
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	rval = 0;
	do {
		if (argc > 0) {
			if (freopen(argv[0], "r", stdin) == NULL) {
				warn("%s", argv[0]);
				rval = 1;
				argc--, argv++;
				continue;
			}
			curfile = argv[0];
			argc--, argv++;
		} else
			curfile = "stdin";
		column = 0;
		while ((wc = getwchar()) != WEOF) {
			switch (wc) {
			case '\t':
				if (nstops == 0) {
					do {
						putwchar(' ');
						column++;
					} while (column & 07);
					continue;
				}
				if (nstops == 1) {
					do {
						putwchar(' ');
						column++;
					} while (((column - 1) % tabstops[0]) != (tabstops[0] - 1));
					continue;
				}
				for (n = 0; n < nstops; n++)
					if (tabstops[n] > column)
						break;
				if (n == nstops) {
					putwchar(' ');
					column++;
					continue;
				}
				while (column < tabstops[n]) {
					putwchar(' ');
					column++;
				}
				continue;

			case '\b':
				if (column)
					column--;
				putwchar('\b');
				continue;

			default:
				putwchar(wc);
				if ((width = wcwidth(wc)) > 0)
					column += width;
				continue;

			case '\n':
				putwchar(wc);
				column = 0;
				continue;
			}
		}
		if (ferror(stdin)) {
			warn("%s", curfile);
			rval = 1;
		}
	} while (argc > 0);
	exit(rval);
}