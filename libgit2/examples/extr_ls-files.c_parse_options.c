#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int file_count; char** files; int error_unmatch; } ;
typedef  TYPE_1__ ls_options ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*,char*) ; 

__attribute__((used)) static int parse_options(ls_options *opts, int argc, char *argv[])
{
	int parsing_files = 0;
	int i;

	memset(opts, 0, sizeof(ls_options));

	if (argc < 2)
		return 0;

	for (i = 1; i < argc; ++i) {
		char *a = argv[i];

		/* if it doesn't start with a '-' or is after the '--' then it is a file */
		if (a[0] != '-' || parsing_files) {
			parsing_files = 1;

			/* watch for overflows (just in case) */
			if (opts->file_count == 1024) {
				fprintf(stderr, "ls-files can only support 1024 files at this time.\n");
				return -1;
			}

			opts->files[opts->file_count++] = a;
		} else if (!strcmp(a, "--")) {
			parsing_files = 1;
		} else if (!strcmp(a, "--error-unmatch")) {
			opts->error_unmatch = 1;
		} else {
			usage("Unsupported argument", a);
			return -1;
		}
	}

	return 0;
}