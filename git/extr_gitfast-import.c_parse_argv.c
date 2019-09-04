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
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  fast_import_usage ; 
 unsigned int global_argc ; 
 char** global_argv ; 
 scalar_t__ import_marks_file ; 
 int /*<<< orphan*/  option_cat_blob_fd (char const*) ; 
 scalar_t__ parse_one_feature (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_one_option (char const*) ; 
 int /*<<< orphan*/  read_marks () ; 
 int seen_data_command ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_argv(void)
{
	unsigned int i;

	for (i = 1; i < global_argc; i++) {
		const char *a = global_argv[i];

		if (*a != '-' || !strcmp(a, "--"))
			break;

		if (!skip_prefix(a, "--", &a))
			die("unknown option %s", a);

		if (parse_one_option(a))
			continue;

		if (parse_one_feature(a, 0))
			continue;

		if (skip_prefix(a, "cat-blob-fd=", &a)) {
			option_cat_blob_fd(a);
			continue;
		}

		die("unknown option --%s", a);
	}
	if (i != global_argc)
		usage(fast_import_usage);

	seen_data_command = 1;
	if (import_marks_file)
		read_marks();
}