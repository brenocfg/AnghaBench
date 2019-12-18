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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ ubig ;

/* Variables and functions */
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  hflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  primes (scalar_t__,scalar_t__) ; 
 scalar_t__ read_num_buf () ; 
 scalar_t__ strtoumax (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	ubig start;		/* where to start generating */
	ubig stop;		/* don't generate at or above this value */
	int ch;
	char *p;

	caph_cache_catpages();
	if (caph_enter() < 0)
		err(1, "cap_enter");

	while ((ch = getopt(argc, argv, "h")) != -1)
		switch (ch) {
		case 'h':
			hflag++;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	start = 0;
	stop = (uint64_t)(-1);

	/*
	 * Convert low and high args.  Strtoumax(3) sets errno to
	 * ERANGE if the number is too large, but, if there's
	 * a leading minus sign it returns the negation of the
	 * result of the conversion, which we'd rather disallow.
	 */
	switch (argc) {
	case 2:
		/* Start and stop supplied on the command line. */
		if (argv[0][0] == '-' || argv[1][0] == '-')
			errx(1, "negative numbers aren't permitted.");

		errno = 0;
		start = strtoumax(argv[0], &p, 0);
		if (errno)
			err(1, "%s", argv[0]);
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[0]);

		errno = 0;
		stop = strtoumax(argv[1], &p, 0);
		if (errno)
			err(1, "%s", argv[1]);
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[1]);
		break;
	case 1:
		/* Start on the command line. */
		if (argv[0][0] == '-')
			errx(1, "negative numbers aren't permitted.");

		errno = 0;
		start = strtoumax(argv[0], &p, 0);
		if (errno)
			err(1, "%s", argv[0]);
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[0]);
		break;
	case 0:
		start = read_num_buf();
		break;
	default:
		usage();
	}

	if (start > stop)
		errx(1, "start value must be less than stop value.");
	primes(start, stop);
	return (0);
}