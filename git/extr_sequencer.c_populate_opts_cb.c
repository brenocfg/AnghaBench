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
struct replay_opts {int explicit_cleanup; int /*<<< orphan*/  default_msg_cleanup; int /*<<< orphan*/  allow_rerere_auto; scalar_t__ xopts_nr; int /*<<< orphan*/ * xopts; int /*<<< orphan*/  xopts_alloc; int /*<<< orphan*/  gpg_sign; int /*<<< orphan*/  strategy; int /*<<< orphan*/  mainline; void* allow_ff; void* record_origin; void* signoff; void* keep_redundant_commits; void* allow_empty_message; void* allow_empty; void* edit; void* no_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RERERE_AUTOUPDATE ; 
 int /*<<< orphan*/  RERERE_NOAUTOUPDATE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  get_cleanup_mode (char const*,int) ; 
 void* git_config_bool_or_int (char const*,char const*,int*) ; 
 int /*<<< orphan*/  git_config_int (char const*,char const*) ; 
 int /*<<< orphan*/  git_config_string_dup (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int populate_opts_cb(const char *key, const char *value, void *data)
{
	struct replay_opts *opts = data;
	int error_flag = 1;

	if (!value)
		error_flag = 0;
	else if (!strcmp(key, "options.no-commit"))
		opts->no_commit = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.edit"))
		opts->edit = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.allow-empty"))
		opts->allow_empty =
			git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.allow-empty-message"))
		opts->allow_empty_message =
			git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.keep-redundant-commits"))
		opts->keep_redundant_commits =
			git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.signoff"))
		opts->signoff = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.record-origin"))
		opts->record_origin = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.allow-ff"))
		opts->allow_ff = git_config_bool_or_int(key, value, &error_flag);
	else if (!strcmp(key, "options.mainline"))
		opts->mainline = git_config_int(key, value);
	else if (!strcmp(key, "options.strategy"))
		git_config_string_dup(&opts->strategy, key, value);
	else if (!strcmp(key, "options.gpg-sign"))
		git_config_string_dup(&opts->gpg_sign, key, value);
	else if (!strcmp(key, "options.strategy-option")) {
		ALLOC_GROW(opts->xopts, opts->xopts_nr + 1, opts->xopts_alloc);
		opts->xopts[opts->xopts_nr++] = xstrdup(value);
	} else if (!strcmp(key, "options.allow-rerere-auto"))
		opts->allow_rerere_auto =
			git_config_bool_or_int(key, value, &error_flag) ?
				RERERE_AUTOUPDATE : RERERE_NOAUTOUPDATE;
	else if (!strcmp(key, "options.default-msg-cleanup")) {
		opts->explicit_cleanup = 1;
		opts->default_msg_cleanup = get_cleanup_mode(value, 1);
	} else
		return error(_("invalid key: %s"), key);

	if (!error_flag)
		return error(_("invalid value for %s: %s"), key, value);

	return 0;
}