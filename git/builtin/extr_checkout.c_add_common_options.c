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
struct option {char* member_2; char* member_4; char* member_5; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct checkout_opts {int /*<<< orphan*/  conflict_style; int /*<<< orphan*/  merge; int /*<<< orphan*/  show_progress; int /*<<< orphan*/  quiet; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option OPT_BOOL (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__QUIET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  free (struct option*) ; 
 int /*<<< orphan*/  option_parse_recurse_submodules_worktree_updater ; 
 struct option* parse_options_concat (struct option*,struct option*) ; 

__attribute__((used)) static struct option *add_common_options(struct checkout_opts *opts,
					 struct option *prevopts)
{
	struct option options[] = {
		OPT__QUIET(&opts->quiet, N_("suppress progress reporting")),
		{ OPTION_CALLBACK, 0, "recurse-submodules", NULL,
			    "checkout", "control recursive updating of submodules",
			    PARSE_OPT_OPTARG, option_parse_recurse_submodules_worktree_updater },
		OPT_BOOL(0, "progress", &opts->show_progress, N_("force progress reporting")),
		OPT_BOOL('m', "merge", &opts->merge, N_("perform a 3-way merge with the new branch")),
		OPT_STRING(0, "conflict", &opts->conflict_style, N_("style"),
			   N_("conflict style (merge or diff3)")),
		OPT_END()
	};
	struct option *newopts = parse_options_concat(prevopts, options);
	free(prevopts);
	return newopts;
}