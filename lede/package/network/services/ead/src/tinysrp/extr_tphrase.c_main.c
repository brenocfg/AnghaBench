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
 int /*<<< orphan*/  Configindex ; 
 int EOF ; 
 int /*<<< orphan*/  Passfile ; 
 char* Progname ; 
 int /*<<< orphan*/  USAGE () ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doit (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 

int main(int argc, char **argv)
{
	int c;

	Progname = *argv;

	/* Parse option arguments. */

	while ((c = getopt(argc, argv, "n:p:")) != EOF) {
		switch (c) {

		case 'n':
			Configindex = atoi(optarg);
			break;

		case 'p':
			Passfile = optarg;
			break;

		default:
			USAGE();
			exit(1);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		USAGE();
		exit(1);
	}
	doit(argv[0]);

	return 0;
}