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
struct replay_opts {int verbose; int quiet; int signoff; int reschedule_failed_exec; int current_fixup_count; int have_squash_onto; int /*<<< orphan*/  squash_onto; struct strbuf current_fixups; scalar_t__ allow_ff; int /*<<< orphan*/  allow_rerere_auto; int /*<<< orphan*/  gpg_sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  RERERE_AUTOUPDATE ; 
 int /*<<< orphan*/  RERERE_NOAUTOUPDATE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_hex (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct replay_opts*) ; 
 int /*<<< orphan*/  git_path_opts_file () ; 
 scalar_t__ is_rebase_i (struct replay_opts*) ; 
 int /*<<< orphan*/  populate_opts_cb ; 
 scalar_t__ read_oneliner (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_strategy_opts (struct replay_opts*,struct strbuf*) ; 
 int /*<<< orphan*/  rebase_path_allow_rerere_autoupdate () ; 
 int /*<<< orphan*/  rebase_path_current_fixups () ; 
 int /*<<< orphan*/  rebase_path_gpg_sign_opt () ; 
 int /*<<< orphan*/  rebase_path_quiet () ; 
 int /*<<< orphan*/  rebase_path_reschedule_failed_exec () ; 
 int /*<<< orphan*/  rebase_path_signoff () ; 
 int /*<<< orphan*/  rebase_path_squash_onto () ; 
 int /*<<< orphan*/  rebase_path_verbose () ; 
 int /*<<< orphan*/  starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static int read_populate_opts(struct replay_opts *opts)
{
	if (is_rebase_i(opts)) {
		struct strbuf buf = STRBUF_INIT;

		if (read_oneliner(&buf, rebase_path_gpg_sign_opt(), 1)) {
			if (!starts_with(buf.buf, "-S"))
				strbuf_reset(&buf);
			else {
				free(opts->gpg_sign);
				opts->gpg_sign = xstrdup(buf.buf + 2);
			}
			strbuf_reset(&buf);
		}

		if (read_oneliner(&buf, rebase_path_allow_rerere_autoupdate(), 1)) {
			if (!strcmp(buf.buf, "--rerere-autoupdate"))
				opts->allow_rerere_auto = RERERE_AUTOUPDATE;
			else if (!strcmp(buf.buf, "--no-rerere-autoupdate"))
				opts->allow_rerere_auto = RERERE_NOAUTOUPDATE;
			strbuf_reset(&buf);
		}

		if (file_exists(rebase_path_verbose()))
			opts->verbose = 1;

		if (file_exists(rebase_path_quiet()))
			opts->quiet = 1;

		if (file_exists(rebase_path_signoff())) {
			opts->allow_ff = 0;
			opts->signoff = 1;
		}

		if (file_exists(rebase_path_reschedule_failed_exec()))
			opts->reschedule_failed_exec = 1;

		read_strategy_opts(opts, &buf);
		strbuf_release(&buf);

		if (read_oneliner(&opts->current_fixups,
				  rebase_path_current_fixups(), 1)) {
			const char *p = opts->current_fixups.buf;
			opts->current_fixup_count = 1;
			while ((p = strchr(p, '\n'))) {
				opts->current_fixup_count++;
				p++;
			}
		}

		if (read_oneliner(&buf, rebase_path_squash_onto(), 0)) {
			if (get_oid_hex(buf.buf, &opts->squash_onto) < 0)
				return error(_("unusable squash-onto"));
			opts->have_squash_onto = 1;
		}

		return 0;
	}

	if (!file_exists(git_path_opts_file()))
		return 0;
	/*
	 * The function git_parse_source(), called from git_config_from_file(),
	 * may die() in case of a syntactically incorrect file. We do not care
	 * about this case, though, because we wrote that file ourselves, so we
	 * are pretty certain that it is syntactically correct.
	 */
	if (git_config_from_file(populate_opts_cb, git_path_opts_file(), opts) < 0)
		return error(_("malformed options sheet: '%s'"),
			git_path_opts_file());
	return 0;
}