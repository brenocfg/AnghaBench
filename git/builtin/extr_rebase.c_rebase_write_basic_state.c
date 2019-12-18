#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rebase_options {char* head_name; int flags; scalar_t__ allow_rerere_autoupdate; scalar_t__ signoff; int /*<<< orphan*/  gpg_sign_opt; int /*<<< orphan*/  strategy_opts; int /*<<< orphan*/  strategy; int /*<<< orphan*/  orig_head; TYPE_2__* onto; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int REBASE_NO_QUIET ; 
 int REBASE_VERBOSE ; 
 scalar_t__ RERERE_AUTOUPDATE ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_dir_path (char*,struct rebase_options*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int rebase_write_basic_state(struct rebase_options *opts)
{
	write_file(state_dir_path("head-name", opts), "%s",
		   opts->head_name ? opts->head_name : "detached HEAD");
	write_file(state_dir_path("onto", opts), "%s",
		   opts->onto ? oid_to_hex(&opts->onto->object.oid) : "");
	write_file(state_dir_path("orig-head", opts), "%s",
		   oid_to_hex(&opts->orig_head));
	write_file(state_dir_path("quiet", opts), "%s",
		   opts->flags & REBASE_NO_QUIET ? "" : "t");
	if (opts->flags & REBASE_VERBOSE)
		write_file(state_dir_path("verbose", opts), "%s", "");
	if (opts->strategy)
		write_file(state_dir_path("strategy", opts), "%s",
			   opts->strategy);
	if (opts->strategy_opts)
		write_file(state_dir_path("strategy_opts", opts), "%s",
			   opts->strategy_opts);
	if (opts->allow_rerere_autoupdate > 0)
		write_file(state_dir_path("allow_rerere_autoupdate", opts),
			   "-%s-rerere-autoupdate",
			   opts->allow_rerere_autoupdate == RERERE_AUTOUPDATE ?
				"" : "-no");
	if (opts->gpg_sign_opt)
		write_file(state_dir_path("gpg_sign_opt", opts), "%s",
			   opts->gpg_sign_opt);
	if (opts->signoff)
		write_file(state_dir_path("strategy", opts), "--signoff");

	return 0;
}