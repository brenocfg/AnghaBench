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
struct strbuf {char* buf; int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct argv_array {char const** argv; } ;
struct child_process {int git_cmd; char const** env; int no_stdin; int stdout_to_stderr; char const* dir; char* trace2_hook_name; struct argv_array args; int /*<<< orphan*/ * argv; } ;
struct add_opts {scalar_t__ checkout; int /*<<< orphan*/  keep_locked; scalar_t__ quiet; int /*<<< orphan*/  force; int /*<<< orphan*/  detach; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  BUG (char*,char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DIR_ENVIRONMENT ; 
 int /*<<< orphan*/  GIT_WORK_TREE_ENVIRONMENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_path (char const*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,char const*,...) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die_if_checked_out (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 char* find_hook (char*) ; 
 char const* get_git_common_dir () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  git_path_buf (struct strbuf*,char*,char const*) ; 
 int is_junk ; 
 int /*<<< orphan*/  junk_git_dir ; 
 int /*<<< orphan*/  junk_pid ; 
 int /*<<< orphan*/  junk_work_tree ; 
 struct commit* lookup_commit_reference_by_name (char const*) ; 
 scalar_t__ mkdir (char*,int) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_path (char const*) ; 
 scalar_t__ ref_exists (char*) ; 
 int /*<<< orphan*/  remove_junk ; 
 int /*<<< orphan*/  remove_junk_on_signal ; 
 int run_command (struct child_process*) ; 
 scalar_t__ safe_create_leading_directories_const (char*) ; 
 int /*<<< orphan*/  sanitize_refname_component (char*,struct strbuf*) ; 
 int /*<<< orphan*/  sigchain_push_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_check_branch_ref (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unlink_or_warn (char const*) ; 
 int /*<<< orphan*/  validate_worktree_add (char const*,struct add_opts const*) ; 
 char* worktree_basename (char const*,int*) ; 
 int /*<<< orphan*/  write_file (char const*,char*,...) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int add_worktree(const char *path, const char *refname,
			const struct add_opts *opts)
{
	struct strbuf sb_git = STRBUF_INIT, sb_repo = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *name;
	struct child_process cp = CHILD_PROCESS_INIT;
	struct argv_array child_env = ARGV_ARRAY_INIT;
	unsigned int counter = 0;
	int len, ret;
	struct strbuf symref = STRBUF_INIT;
	struct commit *commit = NULL;
	int is_branch = 0;
	struct strbuf sb_name = STRBUF_INIT;

	validate_worktree_add(path, opts);

	/* is 'refname' a branch or commit? */
	if (!opts->detach && !strbuf_check_branch_ref(&symref, refname) &&
	    ref_exists(symref.buf)) {
		is_branch = 1;
		if (!opts->force)
			die_if_checked_out(symref.buf, 0);
	}
	commit = lookup_commit_reference_by_name(refname);
	if (!commit)
		die(_("invalid reference: %s"), refname);

	name = worktree_basename(path, &len);
	strbuf_add(&sb, name, path + len - name);
	sanitize_refname_component(sb.buf, &sb_name);
	if (!sb_name.len)
		BUG("How come '%s' becomes empty after sanitization?", sb.buf);
	strbuf_reset(&sb);
	name = sb_name.buf;
	git_path_buf(&sb_repo, "worktrees/%s", name);
	len = sb_repo.len;
	if (safe_create_leading_directories_const(sb_repo.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_repo.buf);

	while (mkdir(sb_repo.buf, 0777)) {
		counter++;
		if ((errno != EEXIST) || !counter /* overflow */)
			die_errno(_("could not create directory of '%s'"),
				  sb_repo.buf);
		strbuf_setlen(&sb_repo, len);
		strbuf_addf(&sb_repo, "%d", counter);
	}
	name = strrchr(sb_repo.buf, '/') + 1;

	junk_pid = getpid();
	atexit(remove_junk);
	sigchain_push_common(remove_junk_on_signal);

	junk_git_dir = xstrdup(sb_repo.buf);
	is_junk = 1;

	/*
	 * lock the incomplete repo so prune won't delete it, unlock
	 * after the preparation is over.
	 */
	strbuf_addf(&sb, "%s/locked", sb_repo.buf);
	if (!opts->keep_locked)
		write_file(sb.buf, "initializing");
	else
		write_file(sb.buf, "added with --lock");

	strbuf_addf(&sb_git, "%s/.git", path);
	if (safe_create_leading_directories_const(sb_git.buf))
		die_errno(_("could not create leading directories of '%s'"),
			  sb_git.buf);
	junk_work_tree = xstrdup(path);

	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/gitdir", sb_repo.buf);
	write_file(sb.buf, "%s", real_path(sb_git.buf));
	write_file(sb_git.buf, "gitdir: %s/worktrees/%s",
		   real_path(get_git_common_dir()), name);
	/*
	 * This is to keep resolve_ref() happy. We need a valid HEAD
	 * or is_git_directory() will reject the directory. Any value which
	 * looks like an object ID will do since it will be immediately
	 * replaced by the symbolic-ref or update-ref invocation in the new
	 * worktree.
	 */
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/HEAD", sb_repo.buf);
	write_file(sb.buf, "%s", oid_to_hex(&null_oid));
	strbuf_reset(&sb);
	strbuf_addf(&sb, "%s/commondir", sb_repo.buf);
	write_file(sb.buf, "../..");

	argv_array_pushf(&child_env, "%s=%s", GIT_DIR_ENVIRONMENT, sb_git.buf);
	argv_array_pushf(&child_env, "%s=%s", GIT_WORK_TREE_ENVIRONMENT, path);
	cp.git_cmd = 1;

	if (!is_branch)
		argv_array_pushl(&cp.args, "update-ref", "HEAD",
				 oid_to_hex(&commit->object.oid), NULL);
	else {
		argv_array_pushl(&cp.args, "symbolic-ref", "HEAD",
				 symref.buf, NULL);
		if (opts->quiet)
			argv_array_push(&cp.args, "--quiet");
	}

	cp.env = child_env.argv;
	ret = run_command(&cp);
	if (ret)
		goto done;

	if (opts->checkout) {
		cp.argv = NULL;
		argv_array_clear(&cp.args);
		argv_array_pushl(&cp.args, "reset", "--hard", NULL);
		if (opts->quiet)
			argv_array_push(&cp.args, "--quiet");
		cp.env = child_env.argv;
		ret = run_command(&cp);
		if (ret)
			goto done;
	}

	is_junk = 0;
	FREE_AND_NULL(junk_work_tree);
	FREE_AND_NULL(junk_git_dir);

done:
	if (ret || !opts->keep_locked) {
		strbuf_reset(&sb);
		strbuf_addf(&sb, "%s/locked", sb_repo.buf);
		unlink_or_warn(sb.buf);
	}

	/*
	 * Hook failure does not warrant worktree deletion, so run hook after
	 * is_junk is cleared, but do return appropriate code when hook fails.
	 */
	if (!ret && opts->checkout) {
		const char *hook = find_hook("post-checkout");
		if (hook) {
			const char *env[] = { "GIT_DIR", "GIT_WORK_TREE", NULL };
			cp.git_cmd = 0;
			cp.no_stdin = 1;
			cp.stdout_to_stderr = 1;
			cp.dir = path;
			cp.env = env;
			cp.argv = NULL;
			cp.trace2_hook_name = "post-checkout";
			argv_array_pushl(&cp.args, absolute_path(hook),
					 oid_to_hex(&null_oid),
					 oid_to_hex(&commit->object.oid),
					 "1", NULL);
			ret = run_command(&cp);
		}
	}

	argv_array_clear(&child_env);
	strbuf_release(&sb);
	strbuf_release(&symref);
	strbuf_release(&sb_repo);
	strbuf_release(&sb_git);
	strbuf_release(&sb_name);
	return ret;
}