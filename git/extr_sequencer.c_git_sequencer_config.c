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
struct replay_opts {int explicit_cleanup; int /*<<< orphan*/ * gpg_sign; int /*<<< orphan*/  default_msg_cleanup; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_MSG_CLEANUP_ALL ; 
 int /*<<< orphan*/  COMMIT_MSG_CLEANUP_NONE ; 
 int /*<<< orphan*/  COMMIT_MSG_CLEANUP_SCISSORS ; 
 int /*<<< orphan*/  COMMIT_MSG_CLEANUP_SPACE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_config_bool (char const*,char const*) ; 
 int git_config_string (char const**,char const*,char const*) ; 
 int git_diff_basic_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_gpg_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * xstrdup (char*) ; 

__attribute__((used)) static int git_sequencer_config(const char *k, const char *v, void *cb)
{
	struct replay_opts *opts = cb;
	int status;

	if (!strcmp(k, "commit.cleanup")) {
		const char *s;

		status = git_config_string(&s, k, v);
		if (status)
			return status;

		if (!strcmp(s, "verbatim")) {
			opts->default_msg_cleanup = COMMIT_MSG_CLEANUP_NONE;
			opts->explicit_cleanup = 1;
		} else if (!strcmp(s, "whitespace")) {
			opts->default_msg_cleanup = COMMIT_MSG_CLEANUP_SPACE;
			opts->explicit_cleanup = 1;
		} else if (!strcmp(s, "strip")) {
			opts->default_msg_cleanup = COMMIT_MSG_CLEANUP_ALL;
			opts->explicit_cleanup = 1;
		} else if (!strcmp(s, "scissors")) {
			opts->default_msg_cleanup = COMMIT_MSG_CLEANUP_SCISSORS;
			opts->explicit_cleanup = 1;
		} else {
			warning(_("invalid commit message cleanup mode '%s'"),
				  s);
		}

		free((char *)s);
		return status;
	}

	if (!strcmp(k, "commit.gpgsign")) {
		opts->gpg_sign = git_config_bool(k, v) ? xstrdup("") : NULL;
		return 0;
	}

	status = git_gpg_config(k, v, NULL);
	if (status)
		return status;

	return git_diff_basic_config(k, v, NULL);
}