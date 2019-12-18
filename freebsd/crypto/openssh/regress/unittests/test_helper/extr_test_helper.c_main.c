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
 int /*<<< orphan*/  _IONBF ; 
 char* __progname ; 
 int /*<<< orphan*/  data_dir ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int quiet_mode ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (char*) ; 
 char* strrchr (char*,char) ; 
 int test_number ; 
 int /*<<< orphan*/  tests () ; 
 int verbose_mode ; 

int
main(int argc, char **argv)
{
	int ch;

	/* Handle systems without __progname */
	if (__progname == NULL) {
		__progname = strrchr(argv[0], '/');
		if (__progname == NULL || __progname[1] == '\0')
			__progname = argv[0];	
		else
			__progname++;
		if ((__progname = strdup(__progname)) == NULL) {
			fprintf(stderr, "strdup failed\n");
			exit(1);
		}
	}

	while ((ch = getopt(argc, argv, "vqd:")) != -1) {
		switch (ch) {
		case 'd':
			data_dir = optarg;
			break;
		case 'q':
			verbose_mode = 0;
			quiet_mode = 1;
			break;
		case 'v':
			verbose_mode = 1;
			quiet_mode = 0;
			break;
		default:
			fprintf(stderr, "Unrecognised command line option\n");
			fprintf(stderr, "Usage: %s [-v]\n", __progname);
			exit(1);
		}
	}
	setvbuf(stdout, NULL, _IONBF, 0);
	if (!quiet_mode)
		printf("%s: ", __progname);
	if (verbose_mode)
		printf("\n");

	tests();

	if (!quiet_mode)
		printf(" %u tests ok\n", test_number);
	return 0;
}