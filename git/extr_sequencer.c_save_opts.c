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
struct strbuf {char* buf; } ;
struct replay_opts {char* strategy; char* gpg_sign; int xopts_nr; scalar_t__ allow_rerere_auto; int /*<<< orphan*/  default_msg_cleanup; scalar_t__ explicit_cleanup; int /*<<< orphan*/ * xopts; scalar_t__ mainline; scalar_t__ allow_ff; scalar_t__ record_origin; scalar_t__ signoff; scalar_t__ keep_redundant_commits; scalar_t__ allow_empty_message; scalar_t__ allow_empty; scalar_t__ edit; scalar_t__ no_commit; } ;

/* Variables and functions */
 scalar_t__ RERERE_AUTOUPDATE ; 
 struct strbuf STRBUF_INIT ; 
 char* describe_cleanup_mode (int /*<<< orphan*/ ) ; 
 int git_config_set_in_file_gently (char const*,char*,char*) ; 
 int git_config_set_multivar_in_file_gently (char const*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* git_path_opts_file () ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int save_opts(struct replay_opts *opts)
{
	const char *opts_file = git_path_opts_file();
	int res = 0;

	if (opts->no_commit)
		res |= git_config_set_in_file_gently(opts_file,
					"options.no-commit", "true");
	if (opts->edit)
		res |= git_config_set_in_file_gently(opts_file,
					"options.edit", "true");
	if (opts->allow_empty)
		res |= git_config_set_in_file_gently(opts_file,
					"options.allow-empty", "true");
	if (opts->allow_empty_message)
		res |= git_config_set_in_file_gently(opts_file,
				"options.allow-empty-message", "true");
	if (opts->keep_redundant_commits)
		res |= git_config_set_in_file_gently(opts_file,
				"options.keep-redundant-commits", "true");
	if (opts->signoff)
		res |= git_config_set_in_file_gently(opts_file,
					"options.signoff", "true");
	if (opts->record_origin)
		res |= git_config_set_in_file_gently(opts_file,
					"options.record-origin", "true");
	if (opts->allow_ff)
		res |= git_config_set_in_file_gently(opts_file,
					"options.allow-ff", "true");
	if (opts->mainline) {
		struct strbuf buf = STRBUF_INIT;
		strbuf_addf(&buf, "%d", opts->mainline);
		res |= git_config_set_in_file_gently(opts_file,
					"options.mainline", buf.buf);
		strbuf_release(&buf);
	}
	if (opts->strategy)
		res |= git_config_set_in_file_gently(opts_file,
					"options.strategy", opts->strategy);
	if (opts->gpg_sign)
		res |= git_config_set_in_file_gently(opts_file,
					"options.gpg-sign", opts->gpg_sign);
	if (opts->xopts) {
		int i;
		for (i = 0; i < opts->xopts_nr; i++)
			res |= git_config_set_multivar_in_file_gently(opts_file,
					"options.strategy-option",
					opts->xopts[i], "^$", 0);
	}
	if (opts->allow_rerere_auto)
		res |= git_config_set_in_file_gently(opts_file,
				"options.allow-rerere-auto",
				opts->allow_rerere_auto == RERERE_AUTOUPDATE ?
				"true" : "false");

	if (opts->explicit_cleanup)
		res |= git_config_set_in_file_gently(opts_file,
				"options.default-msg-cleanup",
				describe_cleanup_mode(opts->default_msg_cleanup));
	return res;
}