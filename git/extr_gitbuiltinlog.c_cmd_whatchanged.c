#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct setup_revision_opt {char* def; int /*<<< orphan*/  revarg_opt; } ;
struct TYPE_2__ {scalar_t__ output_format; } ;
struct rev_info {int diff; TYPE_1__ diffopt; scalar_t__ simplify_history; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ DIFF_FORMAT_RAW ; 
 int /*<<< orphan*/  REVARG_COMMITTISH ; 
 int /*<<< orphan*/  cmd_log_init (int,char const**,char const*,struct rev_info*,struct setup_revision_opt*) ; 
 int cmd_log_walk (struct rev_info*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_log_config ; 
 int /*<<< orphan*/  init_log_defaults () ; 
 int /*<<< orphan*/  memset (struct setup_revision_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int cmd_whatchanged(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_log_defaults();
	git_config(git_log_config, NULL);

	repo_init_revisions(the_repository, &rev, prefix);
	rev.diff = 1;
	rev.simplify_history = 0;
	memset(&opt, 0, sizeof(opt));
	opt.def = "HEAD";
	opt.revarg_opt = REVARG_COMMITTISH;
	cmd_log_init(argc, argv, prefix, &rev, &opt);
	if (!rev.diffopt.output_format)
		rev.diffopt.output_format = DIFF_FORMAT_RAW;
	return cmd_log_walk(&rev);
}