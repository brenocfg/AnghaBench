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
 int /*<<< orphan*/  crid ; 
 int /*<<< orphan*/  crlookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  testit () ; 
 int /*<<< orphan*/  usage (char*) ; 
 int verbose ; 

int
main(int argc, char *argv[])
{
	int c, i;

	while ((c = getopt(argc, argv, "d:v")) != -1) {
		switch (c) {
		case 'd':
			crid = crlookup(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage(argv[0]);
		}
	}
	argc -= optind, argv += optind;

	for (i = 0; i < 1000; i++) {
		fprintf(stderr, "test %d\n", i);
		testit();
	}
	return (0);
}