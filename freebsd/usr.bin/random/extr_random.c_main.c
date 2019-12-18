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
 int EOF ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 double RANDOM_MAX_PLUS1 ; 
 int RANDOM_TYPE_LINES ; 
 int RANDOM_TYPE_UNSET ; 
 int RANDOM_TYPE_WORDS ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int getopt (int,char**,char*) ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  putchar (int) ; 
 double random () ; 
 int randomize_fd (int,int,int,double) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  srandomdev () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 double strtod (char*,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	double denom;
	int ch, fd, random_exit, randomize_lines, random_type, ret,
		selected, unique_output, unbuffer_output;
	char *ep;
	const char *filename;

	denom = 0;
	filename = "/dev/fd/0";
	random_type = RANDOM_TYPE_UNSET;
	random_exit = randomize_lines = unbuffer_output = 0;
	unique_output = 1;

	(void)setlocale(LC_CTYPE, "");

	while ((ch = getopt(argc, argv, "ef:hlruUw")) != -1)
		switch (ch) {
		case 'e':
			random_exit = 1;
			break;
		case 'f':
			randomize_lines = 1;
			if (strcmp(optarg, "-") != 0)
				filename = optarg;
			break;
		case 'l':
			randomize_lines = 1;
			random_type = RANDOM_TYPE_LINES;
			break;
		case 'r':
			unbuffer_output = 1;
			break;
		case 'u':
			randomize_lines = 1;
			unique_output = 1;
			break;
		case 'U':
			randomize_lines = 1;
			unique_output = 0;
			break;
		case 'w':
			randomize_lines = 1;
			random_type = RANDOM_TYPE_WORDS;
			break;
		default:
		case '?':
			usage();
			/* NOTREACHED */
		}

	argc -= optind;
	argv += optind;

	switch (argc) {
	case 0:
		denom = (randomize_lines ? 1 : 2);
		break;
	case 1:
		errno = 0;
		denom = strtod(*argv, &ep);
		if (errno == ERANGE)
			err(1, "%s", *argv);
		if (denom <= 0 || *ep != '\0')
			errx(1, "denominator is not valid.");
		if (random_exit && denom > 256)
			errx(1, "denominator must be <= 256 for random exit.");
		break;
	default:
		usage();
		/* NOTREACHED */
	}

	srandomdev();

	/*
	 * Act as a filter, randomly choosing lines of the standard input
	 * to write to the standard output.
	 */
	if (unbuffer_output)
		setbuf(stdout, NULL);

	/*
	 * Act as a filter, randomizing lines read in from a given file
	 * descriptor and write the output to standard output.
	 */
	if (randomize_lines) {
		if ((fd = open(filename, O_RDONLY, 0)) < 0)
			err(1, "%s", filename);
		ret = randomize_fd(fd, random_type, unique_output, denom);
		if (!random_exit)
			return(ret);
	}

	/* Compute a random exit status between 0 and denom - 1. */
	if (random_exit)
		return (int)(denom * random() / RANDOM_MAX_PLUS1);

	/*
	 * Select whether to print the first line.  (Prime the pump.)
	 * We find a random number between 0 and denom - 1 and, if it's
	 * 0 (which has a 1 / denom chance of being true), we select the
	 * line.
	 */
	selected = (int)(denom * random() / RANDOM_MAX_PLUS1) == 0;
	while ((ch = getchar()) != EOF) {
		if (selected)
			(void)putchar(ch);
		if (ch == '\n') {
			/* End of that line.  See if we got an error. */
			if (ferror(stdout))
				err(2, "stdout");

			/* Now see if the next line is to be printed. */
			selected = (int)(denom * random() /
				RANDOM_MAX_PLUS1) == 0;
		}
	}
	if (ferror(stdin))
		err(2, "stdin");
	exit (0);
}