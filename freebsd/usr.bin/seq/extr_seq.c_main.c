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
struct lconv {char* decimal_point; } ;

/* Variables and functions */
 char SPACE ; 
 char ZERO ; 
 int /*<<< orphan*/  asprintf (char**,char*,double) ; 
 char* decimal_point ; 
 double e_atof (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* generate_format (double,double,double,int,char) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* getprogname () ; 
 struct lconv* localeconv () ; 
 int /*<<< orphan*/  long_opts ; 
 int /*<<< orphan*/  numeric (char*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* unescape (char*) ; 
 int /*<<< orphan*/  valid_format (char*) ; 

int
main(int argc, char *argv[])
{
	const char *sep, *term;
	struct lconv *locale;
	char pad, *fmt, *cur_print, *last_print;
	double first, last, incr, last_shown_value, cur, step;
	int c, errflg, equalize;

	pad = ZERO;
	fmt = NULL;
	first = 1.0;
	last = incr = last_shown_value = 0.0;
	c = errflg = equalize = 0;
	sep = "\n";
	term = NULL;

	/* Determine the locale's decimal point. */
	locale = localeconv();
	if (locale && locale->decimal_point && locale->decimal_point[0] != '\0')
		decimal_point = locale->decimal_point;

	/*
         * Process options, but handle negative numbers separately
         * least they trip up getopt(3).
         */
	while ((optind < argc) && !numeric(argv[optind]) &&
	    (c = getopt_long(argc, argv, "+f:hs:t:w", long_opts, NULL)) != -1) {

		switch (c) {
		case 'f':	/* format (plan9) */
			fmt = optarg;
			equalize = 0;
			break;
		case 's':	/* separator (GNU) */
			sep = unescape(optarg);
			break;
		case 't':	/* terminator (new) */
			term = unescape(optarg);
			break;
		case 'w':	/* equal width (plan9) */
			if (!fmt)
				if (equalize++)
					pad = SPACE;
			break;
		case 'h':	/* help (GNU) */
		default:
			errflg++;
			break;
		}
	}

	argc -= optind;
	argv += optind;
	if (argc < 1 || argc > 3)
		errflg++;

	if (errflg) {
		fprintf(stderr,
		    "usage: %s [-w] [-f format] [-s string] [-t string] [first [incr]] last\n",
		    getprogname());
		exit(1);
	}

	last = e_atof(argv[argc - 1]);

	if (argc > 1)
		first = e_atof(argv[0]);
	
	if (argc > 2) {
		incr = e_atof(argv[1]);
		/* Plan 9/GNU don't do zero */
		if (incr == 0.0)
			errx(1, "zero %screment", (first < last)? "in" : "de");
	}

	/* default is one for Plan 9/GNU work alike */
	if (incr == 0.0)
		incr = (first < last) ? 1.0 : -1.0;

	if (incr <= 0.0 && first < last)
		errx(1, "needs positive increment");

	if (incr >= 0.0 && first > last)
		errx(1, "needs negative decrement");

	if (fmt != NULL) {
		if (!valid_format(fmt))
			errx(1, "invalid format string: `%s'", fmt);
		fmt = unescape(fmt);
		if (!valid_format(fmt))
			errx(1, "invalid format string");
		/*
	         * XXX to be bug for bug compatible with Plan 9 add a
		 * newline if none found at the end of the format string.
		 */
	} else
		fmt = generate_format(first, incr, last, equalize, pad);

	for (step = 1, cur = first; incr > 0 ? cur <= last : cur >= last;
	    cur = first + incr * step++) {
		printf(fmt, cur);
		fputs(sep, stdout);
		last_shown_value = cur;
	}

	/*
	 * Did we miss the last value of the range in the loop above?
	 *
	 * We might have, so check if the printable version of the last
	 * computed value ('cur') and desired 'last' value are equal.  If they
	 * are equal after formatting truncation, but 'cur' and
	 * 'last_shown_value' are not equal, it means the exit condition of the
	 * loop held true due to a rounding error and we still need to print
	 * 'last'.
	 */
	asprintf(&cur_print, fmt, cur);
	asprintf(&last_print, fmt, last);
	if (strcmp(cur_print, last_print) == 0 && cur != last_shown_value) {
		fputs(last_print, stdout);
		fputs(sep, stdout);
	}
	free(cur_print);
	free(last_print);

	if (term != NULL)
		fputs(term, stdout);

	return (0);
}