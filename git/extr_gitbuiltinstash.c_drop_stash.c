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
struct stash_info {int dummy; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_END () ; 
 struct option OPT__QUIET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_stash_ref (struct stash_info*) ; 
 int do_drop_stash (struct stash_info*,int) ; 
 int /*<<< orphan*/  free_stash_info (struct stash_info*) ; 
 scalar_t__ get_stash_info (struct stash_info*,int,char const**) ; 
 int /*<<< orphan*/  git_stash_drop_usage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drop_stash(int argc, const char **argv, const char *prefix)
{
	int ret;
	int quiet = 0;
	struct stash_info info;
	struct option options[] = {
		OPT__QUIET(&quiet, N_("be quiet, only report errors")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_stash_drop_usage, 0);

	if (get_stash_info(&info, argc, argv))
		return -1;

	assert_stash_ref(&info);

	ret = do_drop_stash(&info, quiet);
	free_stash_info(&info);
	return ret;
}