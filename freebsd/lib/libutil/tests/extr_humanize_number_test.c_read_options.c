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
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char* const*,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ ,char*,size_t*) ; 
 int /*<<< orphan*/  usage (char* const) ; 

__attribute__((used)) static void
read_options(int argc, char * const argv[], size_t *bufLength,
    int *includeNegativeScale, int *includeExabytes, int *verbose) {
	int ch;
	size_t temp;

	while ((ch = getopt(argc, argv, "nEh?vl:")) != -1) {
		switch (ch) {
			default:
				usage(argv[0]);
				exit(1);
				break;	/* UNREACHABLE */
			case 'h' :
			case '?' :
				usage(argv[0]);
				exit(0);
				break;	/* UNREACHABLE */
			case 'l' :
				sscanf(optarg, "%zu", &temp);
				*bufLength = temp + 1;
				break;
			case 'n' :
				*includeNegativeScale = 1;
				break;
			case 'E' :
				*includeExabytes = 1;
				break;
			case 'v' :
				*verbose = 1;
				break;
		}
	}
}