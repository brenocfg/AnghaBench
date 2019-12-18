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
struct stat {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 scalar_t__ close_table ; 
 int /*<<< orphan*/  create_empty_mapping (char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  eventsfp ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_arch_std_events () ; 
 int get_maxfds () ; 
 char* mapfile ; 
 int nftw_ordered (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  preprocess_arch_std_files ; 
 int /*<<< orphan*/  print_events_table_suffix (int /*<<< orphan*/ ) ; 
 scalar_t__ process_mapfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  process_one_file ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

int main(int argc, char *argv[])
{
	int rc;
	int maxfds;
	char ldirname[PATH_MAX];

	const char *arch;
	const char *output_file;
	const char *start_dirname;
	struct stat stbuf;

	prog = basename(argv[0]);
	if (argc < 4) {
		pr_err("Usage: %s <arch> <starting_dir> <output_file>\n", prog);
		return 1;
	}

	arch = argv[1];
	start_dirname = argv[2];
	output_file = argv[3];

	if (argc > 4)
		verbose = atoi(argv[4]);

	eventsfp = fopen(output_file, "w");
	if (!eventsfp) {
		pr_err("%s Unable to create required file %s (%s)\n",
				prog, output_file, strerror(errno));
		return 2;
	}

	sprintf(ldirname, "%s/%s", start_dirname, arch);

	/* If architecture does not have any event lists, bail out */
	if (stat(ldirname, &stbuf) < 0) {
		pr_info("%s: Arch %s has no PMU event lists\n", prog, arch);
		goto empty_map;
	}

	/* Include pmu-events.h first */
	fprintf(eventsfp, "#include \"pmu-events/pmu-events.h\"\n");

	/*
	 * The mapfile allows multiple CPUids to point to the same JSON file,
	 * so, not sure if there is a need for symlinks within the pmu-events
	 * directory.
	 *
	 * For now, treat symlinks of JSON files as regular files and create
	 * separate tables for each symlink (presumably, each symlink refers
	 * to specific version of the CPU).
	 */

	maxfds = get_maxfds();
	mapfile = NULL;
	rc = nftw_ordered(ldirname, preprocess_arch_std_files, maxfds, 0);
	if (rc && verbose) {
		pr_info("%s: Error preprocessing arch standard files %s: %s\n",
			prog, ldirname, strerror(errno));
		goto empty_map;
	} else if (rc < 0) {
		/* Make build fail */
		free_arch_std_events();
		return 1;
	} else if (rc) {
		goto empty_map;
	}

	rc = nftw_ordered(ldirname, process_one_file, maxfds, 0);
	if (rc && verbose) {
		pr_info("%s: Error walking file tree %s\n", prog, ldirname);
		goto empty_map;
	} else if (rc < 0) {
		/* Make build fail */
		free_arch_std_events();
		return 1;
	} else if (rc) {
		goto empty_map;
	}

	if (close_table)
		print_events_table_suffix(eventsfp);

	if (!mapfile) {
		pr_info("%s: No CPU->JSON mapping?\n", prog);
		goto empty_map;
	}

	if (process_mapfile(eventsfp, mapfile)) {
		pr_info("%s: Error processing mapfile %s\n", prog, mapfile);
		/* Make build fail */
		return 1;
	}

	return 0;

empty_map:
	fclose(eventsfp);
	create_empty_mapping(output_file);
	free_arch_std_events();
	return 0;
}