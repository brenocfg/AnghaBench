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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; } ;
struct stash_info {int /*<<< orphan*/  i_tree; int /*<<< orphan*/  w_commit; } ;
struct pathspec {scalar_t__ nr; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int INCLUDE_ALL_FILES ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  add_pathspecs (int /*<<< orphan*/ *,struct pathspec const*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/  ce_path_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pathspec const*,char*) ; 
 int /*<<< orphan*/  check_changes (struct pathspec const*,int,struct strbuf*) ; 
 int /*<<< orphan*/  discard_cache () ; 
 scalar_t__ do_clear_stash () ; 
 scalar_t__ do_create_stash (struct pathspec const*,struct strbuf*,int,int,struct stash_info*,struct strbuf*,int) ; 
 scalar_t__ do_store_stash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ pipe_command (struct child_process*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  read_cache_preload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_stash ; 
 int /*<<< orphan*/  reflog_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ refresh_and_write_cache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ report_path_error (char*,struct pathspec const*) ; 
 scalar_t__ run_command (struct child_process*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_index ; 
 char* xcalloc (scalar_t__,int) ; 

__attribute__((used)) static int do_push_stash(const struct pathspec *ps, const char *stash_msg, int quiet,
			 int keep_index, int patch_mode, int include_untracked)
{
	int ret = 0;
	struct stash_info info;
	struct strbuf patch = STRBUF_INIT;
	struct strbuf stash_msg_buf = STRBUF_INIT;
	struct strbuf untracked_files = STRBUF_INIT;

	if (patch_mode && keep_index == -1)
		keep_index = 1;

	if (patch_mode && include_untracked) {
		fprintf_ln(stderr, _("Can't use --patch and --include-untracked"
				     " or --all at the same time"));
		ret = -1;
		goto done;
	}

	read_cache_preload(NULL);
	if (!include_untracked && ps->nr) {
		int i;
		char *ps_matched = xcalloc(ps->nr, 1);

		for (i = 0; i < active_nr; i++)
			ce_path_match(&the_index, active_cache[i], ps,
				      ps_matched);

		if (report_path_error(ps_matched, ps)) {
			fprintf_ln(stderr, _("Did you forget to 'git add'?"));
			ret = -1;
			free(ps_matched);
			goto done;
		}
		free(ps_matched);
	}

	if (refresh_and_write_cache(REFRESH_QUIET, 0, 0)) {
		ret = -1;
		goto done;
	}

	if (!check_changes(ps, include_untracked, &untracked_files)) {
		if (!quiet)
			printf_ln(_("No local changes to save"));
		goto done;
	}

	if (!reflog_exists(ref_stash) && do_clear_stash()) {
		ret = -1;
		if (!quiet)
			fprintf_ln(stderr, _("Cannot initialize stash"));
		goto done;
	}

	if (stash_msg)
		strbuf_addstr(&stash_msg_buf, stash_msg);
	if (do_create_stash(ps, &stash_msg_buf, include_untracked, patch_mode,
			    &info, &patch, quiet)) {
		ret = -1;
		goto done;
	}

	if (do_store_stash(&info.w_commit, stash_msg_buf.buf, 1)) {
		ret = -1;
		if (!quiet)
			fprintf_ln(stderr, _("Cannot save the current status"));
		goto done;
	}

	if (!quiet)
		printf_ln(_("Saved working directory and index state %s"),
			  stash_msg_buf.buf);

	if (!patch_mode) {
		if (include_untracked && !ps->nr) {
			struct child_process cp = CHILD_PROCESS_INIT;

			cp.git_cmd = 1;
			argv_array_pushl(&cp.args, "clean", "--force",
					 "--quiet", "-d", NULL);
			if (include_untracked == INCLUDE_ALL_FILES)
				argv_array_push(&cp.args, "-x");
			if (run_command(&cp)) {
				ret = -1;
				goto done;
			}
		}
		discard_cache();
		if (ps->nr) {
			struct child_process cp_add = CHILD_PROCESS_INIT;
			struct child_process cp_diff = CHILD_PROCESS_INIT;
			struct child_process cp_apply = CHILD_PROCESS_INIT;
			struct strbuf out = STRBUF_INIT;

			cp_add.git_cmd = 1;
			argv_array_push(&cp_add.args, "add");
			if (!include_untracked)
				argv_array_push(&cp_add.args, "-u");
			if (include_untracked == INCLUDE_ALL_FILES)
				argv_array_push(&cp_add.args, "--force");
			argv_array_push(&cp_add.args, "--");
			add_pathspecs(&cp_add.args, ps);
			if (run_command(&cp_add)) {
				ret = -1;
				goto done;
			}

			cp_diff.git_cmd = 1;
			argv_array_pushl(&cp_diff.args, "diff-index", "-p",
					 "--cached", "--binary", "HEAD", "--",
					 NULL);
			add_pathspecs(&cp_diff.args, ps);
			if (pipe_command(&cp_diff, NULL, 0, &out, 0, NULL, 0)) {
				ret = -1;
				goto done;
			}

			cp_apply.git_cmd = 1;
			argv_array_pushl(&cp_apply.args, "apply", "--index",
					 "-R", NULL);
			if (pipe_command(&cp_apply, out.buf, out.len, NULL, 0,
					 NULL, 0)) {
				ret = -1;
				goto done;
			}
		} else {
			struct child_process cp = CHILD_PROCESS_INIT;
			cp.git_cmd = 1;
			argv_array_pushl(&cp.args, "reset", "--hard", "-q",
					 "--no-recurse-submodules", NULL);
			if (run_command(&cp)) {
				ret = -1;
				goto done;
			}
		}

		if (keep_index == 1 && !is_null_oid(&info.i_tree)) {
			struct child_process cp = CHILD_PROCESS_INIT;

			cp.git_cmd = 1;
			argv_array_pushl(&cp.args, "checkout", "--no-overlay",
					 oid_to_hex(&info.i_tree), "--", NULL);
			if (!ps->nr)
				argv_array_push(&cp.args, ":/");
			else
				add_pathspecs(&cp.args, ps);
			if (run_command(&cp)) {
				ret = -1;
				goto done;
			}
		}
		goto done;
	} else {
		struct child_process cp = CHILD_PROCESS_INIT;

		cp.git_cmd = 1;
		argv_array_pushl(&cp.args, "apply", "-R", NULL);

		if (pipe_command(&cp, patch.buf, patch.len, NULL, 0, NULL, 0)) {
			if (!quiet)
				fprintf_ln(stderr, _("Cannot remove "
						     "worktree changes"));
			ret = -1;
			goto done;
		}

		if (keep_index < 1) {
			struct child_process cp = CHILD_PROCESS_INIT;

			cp.git_cmd = 1;
			argv_array_pushl(&cp.args, "reset", "-q", "--", NULL);
			add_pathspecs(&cp.args, ps);
			if (run_command(&cp)) {
				ret = -1;
				goto done;
			}
		}
		goto done;
	}

done:
	strbuf_release(&stash_msg_buf);
	return ret;
}