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
struct fifolog_reader {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  R ; 
 int /*<<< orphan*/  REG_NOSUB ; 
 int /*<<< orphan*/  Render ; 
 int /*<<< orphan*/  Usage () ; 
 int /*<<< orphan*/  ctime (int*) ; 
 int /*<<< orphan*/  err (int,char*,char* const) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct fifolog_reader* fifolog_reader_open (char* const) ; 
 int /*<<< orphan*/  fifolog_reader_process (struct fifolog_reader*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fifolog_reader_seek (struct fifolog_reader*,int) ; 
 int /*<<< orphan*/ * fo ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int get_date (void*) ; 
 int getopt (int,char* const*,char*) ; 
 int opt_B ; 
 int opt_E ; 
 int /*<<< orphan*/ * opt_R ; 
 char* opt_T ; 
 char* opt_o ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regerror (int,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strtoul (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int*) ; 

int
main(int argc, char * const *argv)
{
	int ch, i;
	off_t o;
	struct fifolog_reader *fl;

	time(&opt_E);
	opt_o = "-";
	while ((ch = getopt(argc, argv, "b:B:e:E:o:R:tT:")) != -1) {
		switch (ch) {
		case 'b':
			opt_B = strtoul(optarg, NULL, 0);
			break;
		case 'B':
			opt_B = get_date(optarg);
			if (opt_B == -1)
				errx(1, "Didn't understand \"%s\"", optarg);
			break;
		case 'e':
			opt_E = strtoul(optarg, NULL, 0);
			break;
		case 'E':
			opt_E = get_date(optarg);
			if (opt_E == -1)
				errx(1, "Didn't understand \"%s\"", optarg);
			break;
		case 'o':
			opt_o = optarg;
			break;
		case 'R':
			opt_R = optarg;
			break;
		case 't':
			opt_T = "%Y%m%d%H%M%S";
			break;
		case 'T':
			opt_T = optarg;
			break;
		default:
			Usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (opt_R != NULL) {
		i = regcomp(&R, opt_R, REG_NOSUB);
		if (i != 0) {
			char buf[BUFSIZ];
			(void)regerror(i, &R, buf, sizeof buf);
			fprintf(stderr, "-R argument: %s\n", buf);
			exit (1);
		}
	}

	if (argv[0] == NULL)
		Usage();

	fprintf(stderr, "From\t%jd %s", (intmax_t)opt_B, ctime(&opt_B));
	fprintf(stderr, "To\t%jd %s", (intmax_t)opt_E, ctime(&opt_E));
	if (opt_B >= opt_E)
		errx(1, "Begin time not before End time");

	fl = fifolog_reader_open(argv[0]);

	if (!strcmp(opt_o, "-"))
		fo = stdout;
	else {
		fo = fopen(opt_o, "w");
		if (fo == NULL)
			err(1, "Cannot open: %s", argv[1]);
	}

	o = fifolog_reader_seek(fl, opt_B);
	fifolog_reader_process(fl, o, Render, NULL, opt_E);
	return (0);
}