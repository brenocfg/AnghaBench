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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ lzmainfo (char*,int /*<<< orphan*/ *) ; 
 int optind ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* progname ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuklib_exit (int,int,int) ; 
 int /*<<< orphan*/  tuklib_gettext_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuklib_progname_init (char**) ; 

extern int
main(int argc, char **argv)
{
	tuklib_progname_init(argv);
	tuklib_gettext_init(PACKAGE, LOCALEDIR);

	parse_args(argc, argv);

#ifdef TUKLIB_DOSLIKE
	setmode(fileno(stdin), O_BINARY);
#endif

	int ret = EXIT_SUCCESS;

	// We print empty lines around the output only when reading from
	// files specified on the command line. This is due to how
	// LZMA Utils did it.
	if (optind == argc) {
		if (lzmainfo("(stdin)", stdin))
			ret = EXIT_FAILURE;
	} else {
		printf("\n");

		do {
			if (strcmp(argv[optind], "-") == 0) {
				if (lzmainfo("(stdin)", stdin))
					ret = EXIT_FAILURE;
			} else {
				FILE *f = fopen(argv[optind], "r");
				if (f == NULL) {
					ret = EXIT_FAILURE;
					fprintf(stderr, "%s: %s: %s\n",
							progname,
							argv[optind],
							strerror(errno));
					continue;
				}

				if (lzmainfo(argv[optind], f))
					ret = EXIT_FAILURE;

				printf("\n");
				fclose(f);
			}
		} while (++optind < argc);
	}

	tuklib_exit(ret, EXIT_FAILURE, true);
}