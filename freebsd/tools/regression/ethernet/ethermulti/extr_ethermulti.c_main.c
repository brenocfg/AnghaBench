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
 int /*<<< orphan*/  PRIV_ASIS ; 
 int dorandom ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int geteuid () ; 
 int getopt (int,char**,char*) ; 
 int getuid () ; 
 int /*<<< orphan*/ * ifname ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  testsuite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 

int
main(int argc, char *argv[])
{
	int ch;

	while ((ch = getopt(argc, argv, "i:rv")) != -1) {
		switch (ch) {
		case 'i':
			ifname = optarg;
			break;
		case 'r':
			dorandom = 1;	/* introduce non-determinism */
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage();
		}
	}
	if (ifname == NULL)
		usage();

	printf("1..1\n");
	if (geteuid() != 0) {
		errx(1, "Not running as root, can't run tests as non-root");
		/*NOTREACHED*/
	} else {
		fprintf(stderr,
		    "Running tests with ruid %d euid %d sock uid 0\n",
		    getuid(), geteuid());
		testsuite(PRIV_ASIS);
	}
	printf("ok 1 - ethermulti\n");
	exit(0);
}