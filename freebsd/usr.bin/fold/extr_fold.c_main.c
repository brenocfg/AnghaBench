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
 int DEFLINEWIDTH ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int bflag ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fold (int) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int sflag ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char **argv)
{
	int ch, previous_ch;
	int rval, width;

	(void) setlocale(LC_CTYPE, "");

	width = -1;
	previous_ch = 0;
	while ((ch = getopt(argc, argv, "0123456789bsw:")) != -1) {
		switch (ch) {
		case 'b':
			bflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'w':
			if ((width = atoi(optarg)) <= 0) {
				errx(1, "illegal width value");
			}
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/* Accept a width as eg. -30. Note that a width
			 * specified using the -w option is always used prior
			 * to this undocumented option. */
			switch (previous_ch) {
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				/* The width is a number with multiple digits:
				 * add the last one. */
				width = width * 10 + (ch - '0');
				break;
			default:
				/* Set the width, unless it was previously
				 * set. For instance, the following options
				 * would all give a width of 5 and not 10:
				 *   -10 -w5
				 *   -5b10
				 *   -5 -10b */
				if (width == -1)
					width = ch - '0';
				break;
			}
			break;
		default:
			usage();
		}
		previous_ch = ch;
	}
	argv += optind;
	argc -= optind;

	if (width == -1)
		width = DEFLINEWIDTH;
	rval = 0;
	if (!*argv)
		fold(width);
	else for (; *argv; ++argv)
		if (!freopen(*argv, "r", stdin)) {
			warn("%s", *argv);
			rval = 1;
		} else
			fold(width);
	exit(rval);
}