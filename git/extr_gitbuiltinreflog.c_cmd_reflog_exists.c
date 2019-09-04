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
 int /*<<< orphan*/  REFNAME_ALLOW_ONELEVEL ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_refname_format (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  reflog_exists (char const*) ; 
 char* reflog_exists_usage ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_reflog_exists(int argc, const char **argv, const char *prefix)
{
	int i, start = 0;

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		else if (arg[0] == '-')
			usage(_(reflog_exists_usage));
		else
			break;
	}

	start = i;

	if (argc - start != 1)
		usage(_(reflog_exists_usage));

	if (check_refname_format(argv[start], REFNAME_ALLOW_ONELEVEL))
		die(_("invalid ref format: %s"), argv[start]);
	return !reflog_exists(argv[start]);
}