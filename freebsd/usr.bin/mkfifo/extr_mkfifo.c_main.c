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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  BASEMODE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int f_mode ; 
 int /*<<< orphan*/  getmode (void const*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ mkfifo (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 void* setmode (char const*) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

int
main(int argc, char *argv[])
{
	const char *modestr = NULL;
	const void *modep;
	mode_t fifomode;
	int ch, exitval;

	while ((ch = getopt(argc, argv, "m:")) != -1)
		switch(ch) {
		case 'm':
			f_mode = 1;
			modestr = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argv[0] == NULL)
		usage();

	if (f_mode) {
		umask(0);
		errno = 0;
		if ((modep = setmode(modestr)) == NULL) {
			if (errno)
				err(1, "setmode");
			errx(1, "invalid file mode: %s", modestr);
		}
		fifomode = getmode(modep, BASEMODE);
	} else {
		fifomode = BASEMODE;
	}

	for (exitval = 0; *argv != NULL; ++argv)
		if (mkfifo(*argv, fifomode) < 0) {
			warn("%s", *argv);
			exitval = 1;
		}
	exit(exitval);
}