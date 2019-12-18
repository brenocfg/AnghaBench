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
struct setup_revision_opt {char* def; } ;
struct rev_info {int verbose_header; int abbrev_commit; int use_terminator; int always_show_header; int /*<<< orphan*/  commit_format; int /*<<< orphan*/  reflog_info; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  CMIT_FMT_ONELINE ; 
 int /*<<< orphan*/  cmd_log_init_defaults (struct rev_info*) ; 
 int /*<<< orphan*/  cmd_log_init_finish (int,char const**,char const*,struct rev_info*,struct setup_revision_opt*) ; 
 int cmd_log_walk (struct rev_info*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_log_config ; 
 int /*<<< orphan*/  init_log_defaults () ; 
 int /*<<< orphan*/  init_reflog_walk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct setup_revision_opt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 

int cmd_log_reflog(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;
	struct setup_revision_opt opt;

	init_log_defaults();
	git_config(git_log_config, NULL);

	repo_init_revisions(the_repository, &rev, prefix);
	init_reflog_walk(&rev.reflog_info);
	rev.verbose_header = 1;
	memset(&opt, 0, sizeof(opt));
	opt.def = "HEAD";
	cmd_log_init_defaults(&rev);
	rev.abbrev_commit = 1;
	rev.commit_format = CMIT_FMT_ONELINE;
	rev.use_terminator = 1;
	rev.always_show_header = 1;
	cmd_log_init_finish(argc, argv, prefix, &rev, &opt);

	return cmd_log_walk(&rev);
}