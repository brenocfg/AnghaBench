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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository_format {scalar_t__ version; int is_bare; scalar_t__ work_tree; int /*<<< orphan*/  unknown_extensions; scalar_t__ worktree_config; int /*<<< orphan*/  partial_clone; int /*<<< orphan*/  precious_objects; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int get_common_dir (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  git_config_from_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct repository_format*) ; 
 int /*<<< orphan*/  git_work_tree_cfg ; 
 int inside_work_tree ; 
 int is_bare_repository_cfg ; 
 int /*<<< orphan*/  read_repository_format (struct repository_format*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_worktree_config ; 
 int /*<<< orphan*/  repository_format_precious_objects ; 
 scalar_t__ repository_format_worktree_config ; 
 int /*<<< orphan*/  set_repository_format_partial_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_repository_format (struct repository_format*,struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (scalar_t__) ; 

__attribute__((used)) static int check_repository_format_gently(const char *gitdir, struct repository_format *candidate, int *nongit_ok)
{
	struct strbuf sb = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;
	int has_common;

	has_common = get_common_dir(&sb, gitdir);
	strbuf_addstr(&sb, "/config");
	read_repository_format(candidate, sb.buf);
	strbuf_release(&sb);

	/*
	 * For historical use of check_repository_format() in git-init,
	 * we treat a missing config as a silent "ok", even when nongit_ok
	 * is unset.
	 */
	if (candidate->version < 0)
		return 0;

	if (verify_repository_format(candidate, &err) < 0) {
		if (nongit_ok) {
			warning("%s", err.buf);
			strbuf_release(&err);
			*nongit_ok = -1;
			return -1;
		}
		die("%s", err.buf);
	}

	repository_format_precious_objects = candidate->precious_objects;
	set_repository_format_partial_clone(candidate->partial_clone);
	repository_format_worktree_config = candidate->worktree_config;
	string_list_clear(&candidate->unknown_extensions, 0);

	if (repository_format_worktree_config) {
		/*
		 * pick up core.bare and core.worktree from per-worktree
		 * config if present
		 */
		strbuf_addf(&sb, "%s/config.worktree", gitdir);
		git_config_from_file(read_worktree_config, sb.buf, candidate);
		strbuf_release(&sb);
		has_common = 0;
	}

	if (!has_common) {
		if (candidate->is_bare != -1) {
			is_bare_repository_cfg = candidate->is_bare;
			if (is_bare_repository_cfg == 1)
				inside_work_tree = -1;
		}
		if (candidate->work_tree) {
			free(git_work_tree_cfg);
			git_work_tree_cfg = xstrdup(candidate->work_tree);
			inside_work_tree = -1;
		}
	}

	return 0;
}