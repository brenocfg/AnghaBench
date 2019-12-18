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
typedef  scalar_t__ iconv_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 int do_conv (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  do_list ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iconv (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int /*<<< orphan*/  iconvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  long_options ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
	iconv_t cd;
	FILE *fp;
	const char *opt_f, *opt_t;
	int ch, i, res;
	bool opt_c = false, opt_s = false;

	opt_f = opt_t = "";

	setlocale(LC_ALL, "");
	setprogname(argv[0]);

	while ((ch = getopt_long(argc, argv, "csLlf:t:",
	    long_options, NULL)) != -1) {
		switch (ch) {
		case 'c':
			opt_c = true;
			break;
		case 's':
			opt_s = true;
			break;
		case 'l':
			/* list */
			if (opt_s || opt_c || strcmp(opt_f, "") != 0 ||
			    strcmp(opt_t, "") != 0) {
				warnx("-l is not allowed with other flags.");
				usage();
			}
			iconvlist(do_list, NULL);
			return (EXIT_SUCCESS);
		case 'f':
			/* from */
			if (optarg != NULL)
				opt_f = optarg;
			break;
		case 't':
			/* to */
			if (optarg != NULL)
				opt_t = optarg;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	if ((strcmp(opt_f, "") == 0) && (strcmp(opt_t, "") == 0))
		usage();

	if (caph_limit_stdio() < 0)
		err(EXIT_FAILURE, "capsicum");

	/*
	 * Cache NLS data, for strerror, for err(3), before entering capability
	 * mode.
	 */
	caph_cache_catpages();

	/*
	 * Cache iconv conversion handle before entering sandbox.
	 */
	cd = iconv_open(opt_t, opt_f);
	if (cd == (iconv_t)-1)
		err(EXIT_FAILURE, "iconv_open(%s, %s)", opt_t, opt_f);

	if (argc == 0) {
		if (caph_enter() < 0)
			err(EXIT_FAILURE, "unable to enter capability mode");
		res = do_conv(stdin, cd, opt_s, opt_c);
	} else {
		res = 0;
		for (i = 0; i < argc; i++) {
			fp = (strcmp(argv[i], "-") != 0) ?
			    fopen(argv[i], "r") : stdin;
			if (fp == NULL)
				err(EXIT_FAILURE, "Cannot open `%s'",
				    argv[i]);
			/* Enter Capsicum sandbox for final input file. */
			if (i + 1 == argc && caph_enter() < 0)
				err(EXIT_FAILURE,
				    "unable to enter capability mode");
			res |= do_conv(fp, cd, opt_s, opt_c);
			(void)fclose(fp);

			/* Reset iconv descriptor state. */
			(void)iconv(cd, NULL, NULL, NULL, NULL);
		}
	}
	iconv_close(cd);
	return (res == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}