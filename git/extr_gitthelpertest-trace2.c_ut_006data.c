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
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_data_string (char const*,int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static int ut_006data(int argc, const char **argv)
{
	const char *usage_error =
		"expect <cat0> <k0> <v0> [<cat1> <k1> <v1> [...]]";

	if (argc % 3 != 0)
		die("%s", usage_error);

	while (argc) {
		if (!argv[0] || !*argv[0] || !argv[1] || !*argv[1] ||
		    !argv[2] || !*argv[2])
			die("%s", usage_error);

		trace2_data_string(argv[0], the_repository, argv[1], argv[2]);
		argv += 3;
		argc -= 3;
	}

	return 0;
}