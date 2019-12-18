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
struct rlimit {int /*<<< orphan*/  rlim_max; int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  force ; 
 scalar_t__ fsirand (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  ignorelabel ; 
 int optind ; 
 int /*<<< orphan*/  printonly ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  srandomdev () ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char *argv[])
{
	int n, ex = 0;
	struct rlimit rl;

	while ((n = getopt(argc, argv, "bfp")) != -1) {
		switch (n) {
		case 'b':
			ignorelabel++;
			break;
		case 'p':
			printonly++;
			break;
		case 'f':
			force++;
			break;
		default:
			usage();
		}
	}
	if (argc - optind < 1)
		usage();

	srandomdev();

	/* Increase our data size to the max */
	if (getrlimit(RLIMIT_DATA, &rl) == 0) {
		rl.rlim_cur = rl.rlim_max;
		if (setrlimit(RLIMIT_DATA, &rl) < 0)
			warn("can't get resource limit to max data size");
	} else
		warn("can't get resource limit for data size");

	for (n = optind; n < argc; n++) {
		if (argc - optind != 1)
			(void)puts(argv[n]);
		ex += fsirand(argv[n]);
		if (n < argc - 1)
			putchar('\n');
	}

	exit(ex);
}