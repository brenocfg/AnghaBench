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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exist (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* input_file ; 
 int /*<<< orphan*/ * name_filter ; 
 void* optarg ; 
 int print_all_key_names ; 
 int show_all ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strtoul (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int swap_bytes ; 
 int /*<<< orphan*/  tffs_size ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_options(int argc, char *argv[])
{
	while (1)
	{
		int c;

		c = getopt(argc, argv, "abhi:ln:s:");
		if (c == -1)
			break;

		switch (c) {
			case 'a':
				show_all = true;
				name_filter = NULL;
				print_all_key_names = false;
				break;
			case 'b':
				swap_bytes = 1;
				break;
			case 'h':
				usage(EXIT_SUCCESS);
				break;
			case 'i':
				input_file = optarg;
				break;
			case 'l':
				print_all_key_names = true;
				show_all = false;
				name_filter = NULL;
				break;
			case 'n':
				name_filter = optarg;
				show_all = false;
				print_all_key_names = false;
				break;
			case 's':
				tffs_size = strtoul(optarg, NULL, 0);
				break;
			default:
				usage(EXIT_FAILURE);
				break;
		}
	}

	if (!input_file) {
		fprintf(stderr, "ERROR: No input file (-i <file>) given!\n");
		exit(EXIT_FAILURE);
	}

	if (!file_exist(input_file)) {
		fprintf(stderr, "ERROR: %s does not exist\n", input_file);
		exit(EXIT_FAILURE);
	}

	if (!show_all && !name_filter && !print_all_key_names) {
		fprintf(stderr,
			"ERROR: either -l, -a or -n <key name> is required!\n");
		exit(EXIT_FAILURE);
	}
}