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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* file_name_to_table_name (char*) ; 
 char* fixregex (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_mapping_table_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_mapping_table_suffix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int process_mapfile(FILE *outfp, char *fpath)
{
	int n = 16384;
	FILE *mapfp;
	char *save = NULL;
	char *line, *p;
	int line_num;
	char *tblname;

	pr_info("%s: Processing mapfile %s\n", prog, fpath);

	line = malloc(n);
	if (!line)
		return -1;

	mapfp = fopen(fpath, "r");
	if (!mapfp) {
		pr_info("%s: Error %s opening %s\n", prog, strerror(errno),
				fpath);
		return -1;
	}

	print_mapping_table_prefix(outfp);

	/* Skip first line (header) */
	p = fgets(line, n, mapfp);
	if (!p)
		goto out;

	line_num = 1;
	while (1) {
		char *cpuid, *version, *type, *fname;

		line_num++;
		p = fgets(line, n, mapfp);
		if (!p)
			break;

		if (line[0] == '#' || line[0] == '\n')
			continue;

		if (line[strlen(line)-1] != '\n') {
			/* TODO Deal with lines longer than 16K */
			pr_info("%s: Mapfile %s: line %d too long, aborting\n",
					prog, fpath, line_num);
			return -1;
		}
		line[strlen(line)-1] = '\0';

		cpuid = fixregex(strtok_r(p, ",", &save));
		version = strtok_r(NULL, ",", &save);
		fname = strtok_r(NULL, ",", &save);
		type = strtok_r(NULL, ",", &save);

		tblname = file_name_to_table_name(fname);
		fprintf(outfp, "{\n");
		fprintf(outfp, "\t.cpuid = \"%s\",\n", cpuid);
		fprintf(outfp, "\t.version = \"%s\",\n", version);
		fprintf(outfp, "\t.type = \"%s\",\n", type);

		/*
		 * CHECK: We can't use the type (eg "core") field in the
		 * table name. For us to do that, we need to somehow tweak
		 * the other caller of file_name_to_table(), process_json()
		 * to determine the type. process_json() file has no way
		 * of knowing these are "core" events unless file name has
		 * core in it. If filename has core in it, we can safely
		 * ignore the type field here also.
		 */
		fprintf(outfp, "\t.table = %s\n", tblname);
		fprintf(outfp, "},\n");
	}

out:
	print_mapping_table_suffix(outfp);
	return 0;
}