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
typedef  int /*<<< orphan*/  lzma_stream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  LZMA_STREAM_INIT ; 
 int /*<<< orphan*/  O_BINARY ; 
 int /*<<< orphan*/  display_errors ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  lzma_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_errorf (char*,char*,int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  parse_options (int,char**) ; 
 int /*<<< orphan*/  setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuklib_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuklib_progname_init (char**) ; 
 int /*<<< orphan*/  uncompress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
main(int argc, char **argv)
{
	// Initialize progname which we will be used in error messages.
	tuklib_progname_init(argv);

	// Parse the command line options.
	parse_options(argc, argv);

	// The same lzma_stream is used for all files that we decode. This way
	// we don't need to reallocate memory for every file if they use same
	// compression settings.
	lzma_stream strm = LZMA_STREAM_INIT;

	// Some systems require setting stdin and stdout to binary mode.
#ifdef TUKLIB_DOSLIKE
	setmode(fileno(stdin), O_BINARY);
	setmode(fileno(stdout), O_BINARY);
#endif

	if (optind == argc) {
		// No filenames given, decode from stdin.
		uncompress(&strm, stdin, "(stdin)");
	} else {
		// Loop through the filenames given on the command line.
		do {
			// "-" indicates stdin.
			if (strcmp(argv[optind], "-") == 0) {
				uncompress(&strm, stdin, "(stdin)");
			} else {
				FILE *file = fopen(argv[optind], "rb");
				if (file == NULL) {
					my_errorf("%s: %s", argv[optind],
							strerror(errno));
					exit(EXIT_FAILURE);
				}

				uncompress(&strm, file, argv[optind]);
				fclose(file);
			}
		} while (++optind < argc);
	}

#ifndef NDEBUG
	// Free the memory only when debugging. Freeing wastes some time,
	// but allows detecting possible memory leaks with Valgrind.
	lzma_end(&strm);
#endif

	tuklib_exit(EXIT_SUCCESS, EXIT_FAILURE, display_errors);
}