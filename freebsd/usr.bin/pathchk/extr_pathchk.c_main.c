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
 int Pflag ; 
 int check (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int pflag ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int ch, rval;
	const char *arg;

	while ((ch = getopt(argc, argv, "pP")) > 0) {
		switch (ch) {
		case 'p':
			pflag = 1;
			break;
		case 'P':
			Pflag = 1;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	rval = 0;
	while ((arg = *argv++) != NULL)
		rval |= check(arg);

	exit(rval);
}