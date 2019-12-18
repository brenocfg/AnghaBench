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
struct replay_opts {char* strategy; scalar_t__ xopts_nr; scalar_t__ allow_rerere_auto; char* gpg_sign; scalar_t__ reschedule_failed_exec; scalar_t__ signoff; scalar_t__ verbose; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ RERERE_AUTOUPDATE ; 
 scalar_t__ RERERE_NOAUTOUPDATE ; 
 char* getenv (char*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebase_path_allow_rerere_autoupdate () ; 
 int /*<<< orphan*/  rebase_path_gpg_sign_opt () ; 
 int /*<<< orphan*/  rebase_path_head_name () ; 
 int /*<<< orphan*/  rebase_path_onto () ; 
 int /*<<< orphan*/  rebase_path_orig_head () ; 
 int /*<<< orphan*/  rebase_path_quiet () ; 
 int /*<<< orphan*/  rebase_path_reschedule_failed_exec () ; 
 int /*<<< orphan*/  rebase_path_signoff () ; 
 int /*<<< orphan*/  rebase_path_strategy () ; 
 int /*<<< orphan*/  rebase_path_verbose () ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  write_strategy_opts (struct replay_opts*) ; 

int write_basic_state(struct replay_opts *opts, const char *head_name,
		      struct commit *onto, const char *orig_head)
{
	const char *quiet = getenv("GIT_QUIET");

	if (head_name)
		write_file(rebase_path_head_name(), "%s\n", head_name);
	if (onto)
		write_file(rebase_path_onto(), "%s\n",
			   oid_to_hex(&onto->object.oid));
	if (orig_head)
		write_file(rebase_path_orig_head(), "%s\n", orig_head);

	if (quiet)
		write_file(rebase_path_quiet(), "%s\n", quiet);
	if (opts->verbose)
		write_file(rebase_path_verbose(), "%s", "");
	if (opts->strategy)
		write_file(rebase_path_strategy(), "%s\n", opts->strategy);
	if (opts->xopts_nr > 0)
		write_strategy_opts(opts);

	if (opts->allow_rerere_auto == RERERE_AUTOUPDATE)
		write_file(rebase_path_allow_rerere_autoupdate(), "--rerere-autoupdate\n");
	else if (opts->allow_rerere_auto == RERERE_NOAUTOUPDATE)
		write_file(rebase_path_allow_rerere_autoupdate(), "--no-rerere-autoupdate\n");

	if (opts->gpg_sign)
		write_file(rebase_path_gpg_sign_opt(), "-S%s\n", opts->gpg_sign);
	if (opts->signoff)
		write_file(rebase_path_signoff(), "--signoff\n");
	if (opts->reschedule_failed_exec)
		write_file(rebase_path_reschedule_failed_exec(), "%s", "");

	return 0;
}