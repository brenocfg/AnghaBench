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
struct printc {int show_all_datasets; int show_space; int script_fmt; int show_snaps; } ;
typedef  int /*<<< orphan*/  pc ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  be ; 
 scalar_t__ be_get_bootenv_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ be_prop_list_alloc (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  be_prop_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct printc*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  print_headers (int /*<<< orphan*/ *,struct printc*) ; 
 int /*<<< orphan*/  print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct printc*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  prop_list_sort (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char*) ; 
 int usage (int) ; 

int
bectl_cmd_list(int argc, char *argv[])
{
	struct printc pc;
	nvpair_t *cur;
	nvlist_t *dsprops, *props;
	int opt, printed;
	char *column;
	bool reverse;

	column = NULL;
	props = NULL;
	printed = 0;
	bzero(&pc, sizeof(pc));
	reverse = false;
	while ((opt = getopt(argc, argv, "aDHsc:C:")) != -1) {
		switch (opt) {
		case 'a':
			pc.show_all_datasets = true;
			break;
		case 'D':
			pc.show_space = true;
			break;
		case 'H':
			pc.script_fmt = true;
			break;
		case 's':
			pc.show_snaps = true;
			break;
		case 'c':
			if (column != NULL)
				free(column);
			column = strdup(optarg);
			reverse = false;
			break;
		case 'C':
			if (column != NULL)
				free(column);
			column = strdup(optarg);
			reverse = true;
			break;
		default:
			fprintf(stderr, "bectl list: unknown option '-%c'\n",
			    optopt);
			return (usage(false));
		}
	}

	argc -= optind;

	if (argc != 0) {
		fprintf(stderr, "bectl list: extra argument provided\n");
		return (usage(false));
	}

	if (be_prop_list_alloc(&props) != 0) {
		fprintf(stderr, "bectl list: failed to allocate prop nvlist\n");
		return (1);
	}
	if (be_get_bootenv_props(be, props) != 0) {
		/* XXX TODO: Real errors */
		fprintf(stderr, "bectl list: failed to fetch boot environments\n");
		return (1);
	}

	/* List boot environments in alphabetical order by default */
	if (column == NULL)
		column = strdup("name");

	prop_list_sort(props, column, reverse);

	/* Force -D off if either -a or -s are specified */
	if (pc.show_all_datasets || pc.show_snaps)
		pc.show_space = false;
	if (!pc.script_fmt)
		print_headers(props, &pc);

	/* Print boot environments */
	for (cur = nvlist_next_nvpair(props, NULL); cur != NULL;
	    cur = nvlist_next_nvpair(props, cur)) {
		nvpair_value_nvlist(cur, &dsprops);

		if (printed > 0 && (pc.show_all_datasets || pc.show_snaps))
			printf("\n");

		print_info(nvpair_name(cur), dsprops, &pc);
		printed++;
	}

	free(column);
	be_prop_list_free(props);

	return (0);
}