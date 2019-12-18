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
 scalar_t__ fopen (char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_random_seed () ; 
 scalar_t__ input_file ; 
 scalar_t__ iter_end ; 
 scalar_t__ iter_start ; 
 char* optarg ; 
 char* prog ; 
 unsigned int seed ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 scalar_t__ stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  verbose ; 
 int x86_64 ; 

__attribute__((used)) static void parse_args(int argc, char **argv)
{
	int c;
	char *tmp = NULL;
	int set_seed = 0;

	prog = argv[0];
	while ((c = getopt(argc, argv, "ynvs:m:i:")) != -1) {
		switch (c) {
		case 'y':
			x86_64 = 1;
			break;
		case 'n':
			x86_64 = 0;
			break;
		case 'v':
			verbose++;
			break;
		case 'i':
			if (strcmp("-", optarg) == 0)
				input_file = stdin;
			else
				input_file = fopen(optarg, "r");
			if (!input_file)
				usage("Failed to open input file");
			break;
		case 's':
			seed = (unsigned int)strtoul(optarg, &tmp, 0);
			if (*tmp == ',') {
				optarg = tmp + 1;
				iter_start = strtoul(optarg, &tmp, 0);
			}
			if (*tmp != '\0' || tmp == optarg)
				usage("Failed to parse seed");
			set_seed = 1;
			break;
		case 'm':
			iter_end = strtoul(optarg, &tmp, 0);
			if (*tmp != '\0' || tmp == optarg)
				usage("Failed to parse max_iter");
			break;
		default:
			usage(NULL);
		}
	}

	/* Check errors */
	if (iter_end < iter_start)
		usage("Max iteration number must be bigger than iter-num");

	if (set_seed && input_file)
		usage("Don't use input file (-i) with random seed (-s)");

	/* Initialize random seed */
	if (!input_file) {
		if (!set_seed)	/* No seed is given */
			init_random_seed();
		srand(seed);
	}
}