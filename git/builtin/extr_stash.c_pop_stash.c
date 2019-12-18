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
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT__QUIET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert_stash_ref (struct stash_info*) ; 
 int do_apply_stash (char const*,struct stash_info*,int,int) ; 
 int do_drop_stash (struct stash_info*,int) ; 
 int /*<<< orphan*/  free_stash_info (struct stash_info*) ; 
 scalar_t__ get_stash_info (struct stash_info*,int,char const**) ; 
 int /*<<< orphan*/  git_stash_pop_usage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pop_stash(int argc, const char **argv, const char *prefix)
{
	int ret;
	int index = 0;
	int quiet = 0;
	struct stash_info info;
	struct option options[] = {
		OPT__QUIET(&quiet, N_("be quiet, only report errors")),
		OPT_BOOL(0, "index", &index,
			 N_("attempt to recreate the index")),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_stash_pop_usage, 0);

	if (get_stash_info(&info, argc, argv))
		return -1;

	assert_stash_ref(&info);
	if ((ret = do_apply_stash(prefix, &info, index, quiet)))
		printf_ln(_("The stash entry is kept in case "
			    "you need it again."));
	else
		ret = do_drop_stash(&info, quiet);

	free_stash_info(&info);
	return ret;
}