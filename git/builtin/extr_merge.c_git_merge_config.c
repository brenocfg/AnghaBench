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

/* Variables and functions */
 int /*<<< orphan*/  FF_ALLOW ; 
 int /*<<< orphan*/  FF_NO ; 
 int /*<<< orphan*/  FF_ONLY ; 
 char* branch ; 
 int /*<<< orphan*/  branch_mergeoptions ; 
 int /*<<< orphan*/  cleanup_arg ; 
 void* default_to_upstream ; 
 int /*<<< orphan*/  fast_forward ; 
 int fmt_merge_msg_config (char const*,char const*,void*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 void* git_config_bool (char const*,char const*) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_diff_ui_config (char const*,char const*,void*) ; 
 int git_gpg_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_parse_maybe_bool (char const*) ; 
 void* option_renormalize ; 
 int /*<<< orphan*/  pull_octopus ; 
 int /*<<< orphan*/  pull_twohead ; 
 void* show_diffstat ; 
 char* sign_commit ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 void* verify_signatures ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int git_merge_config(const char *k, const char *v, void *cb)
{
	int status;

	if (branch && starts_with(k, "branch.") &&
		starts_with(k + 7, branch) &&
		!strcmp(k + 7 + strlen(branch), ".mergeoptions")) {
		free(branch_mergeoptions);
		branch_mergeoptions = xstrdup(v);
		return 0;
	}

	if (!strcmp(k, "merge.diffstat") || !strcmp(k, "merge.stat"))
		show_diffstat = git_config_bool(k, v);
	else if (!strcmp(k, "merge.verifysignatures"))
		verify_signatures = git_config_bool(k, v);
	else if (!strcmp(k, "pull.twohead"))
		return git_config_string(&pull_twohead, k, v);
	else if (!strcmp(k, "pull.octopus"))
		return git_config_string(&pull_octopus, k, v);
	else if (!strcmp(k, "commit.cleanup"))
		return git_config_string(&cleanup_arg, k, v);
	else if (!strcmp(k, "merge.renormalize"))
		option_renormalize = git_config_bool(k, v);
	else if (!strcmp(k, "merge.ff")) {
		int boolval = git_parse_maybe_bool(v);
		if (0 <= boolval) {
			fast_forward = boolval ? FF_ALLOW : FF_NO;
		} else if (v && !strcmp(v, "only")) {
			fast_forward = FF_ONLY;
		} /* do not barf on values from future versions of git */
		return 0;
	} else if (!strcmp(k, "merge.defaulttoupstream")) {
		default_to_upstream = git_config_bool(k, v);
		return 0;
	} else if (!strcmp(k, "commit.gpgsign")) {
		sign_commit = git_config_bool(k, v) ? "" : NULL;
		return 0;
	}

	status = fmt_merge_msg_config(k, v, cb);
	if (status)
		return status;
	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;
	return git_diff_ui_config(k, v, cb);
}