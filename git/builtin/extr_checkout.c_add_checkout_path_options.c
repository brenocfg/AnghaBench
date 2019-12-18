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
struct option {int dummy; } ;
struct checkout_opts {int /*<<< orphan*/  ignore_skipworktree; int /*<<< orphan*/  patch_mode; int /*<<< orphan*/  writeout_stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_SET_INT_F (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  free (struct option*) ; 
 struct option* parse_options_concat (struct option*,struct option*) ; 

__attribute__((used)) static struct option *add_checkout_path_options(struct checkout_opts *opts,
						struct option *prevopts)
{
	struct option options[] = {
		OPT_SET_INT_F('2', "ours", &opts->writeout_stage,
			      N_("checkout our version for unmerged files"),
			      2, PARSE_OPT_NONEG),
		OPT_SET_INT_F('3', "theirs", &opts->writeout_stage,
			      N_("checkout their version for unmerged files"),
			      3, PARSE_OPT_NONEG),
		OPT_BOOL('p', "patch", &opts->patch_mode, N_("select hunks interactively")),
		OPT_BOOL(0, "ignore-skip-worktree-bits", &opts->ignore_skipworktree,
			 N_("do not limit pathspecs to sparse entries only")),
		OPT_END()
	};
	struct option *newopts = parse_options_concat(prevopts, options);
	free(prevopts);
	return newopts;
}