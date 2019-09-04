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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct replay_opts {int /*<<< orphan*/  record_origin; int /*<<< orphan*/  signoff; int /*<<< orphan*/  gpg_sign; } ;
struct object_id {int dummy; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;

/* Variables and functions */
 unsigned int ALLOW_EMPTY ; 
 unsigned int AMEND_MSG ; 
 int /*<<< orphan*/  BUG (char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 unsigned int CLEANUP_MSG ; 
 unsigned int CREATE_ROOT_COMMIT ; 
 unsigned int EDIT_MSG ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_MSG_ON_ERR ; 
 unsigned int VERIFY_MSG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int commit_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *,struct object_id*,char const*,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 struct object_id* get_cache_tree_oid (int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_get_value (char*,char const**) ; 
 char* gpg_sign_opt_quoted (struct replay_opts*) ; 
 scalar_t__ is_rebase_i (struct replay_opts*) ; 
 char* read_author_ident (struct strbuf*) ; 
 scalar_t__ read_env_script (int /*<<< orphan*/ *) ; 
 int run_command (struct child_process*) ; 
 int run_command_silent_on_success (struct child_process*) ; 
 char* staged_changes_advice ; 
 int strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int update_ref (int /*<<< orphan*/ *,char*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_git_commit(struct repository *r,
			  const char *defmsg,
			  struct replay_opts *opts,
			  unsigned int flags)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	const char *value;

	if ((flags & CREATE_ROOT_COMMIT) && !(flags & AMEND_MSG)) {
		struct strbuf msg = STRBUF_INIT, script = STRBUF_INIT;
		const char *author = NULL;
		struct object_id root_commit, *cache_tree_oid;
		int res = 0;

		if (is_rebase_i(opts)) {
			author = read_author_ident(&script);
			if (!author) {
				strbuf_release(&script);
				return -1;
			}
		}

		if (!defmsg)
			BUG("root commit without message");

		if (!(cache_tree_oid = get_cache_tree_oid(r->index)))
			res = -1;

		if (!res)
			res = strbuf_read_file(&msg, defmsg, 0);

		if (res <= 0)
			res = error_errno(_("could not read '%s'"), defmsg);
		else
			res = commit_tree(msg.buf, msg.len, cache_tree_oid,
					  NULL, &root_commit, author,
					  opts->gpg_sign);

		strbuf_release(&msg);
		strbuf_release(&script);
		if (!res) {
			update_ref(NULL, "CHERRY_PICK_HEAD", &root_commit, NULL,
				   REF_NO_DEREF, UPDATE_REFS_MSG_ON_ERR);
			res = update_ref(NULL, "HEAD", &root_commit, NULL, 0,
					 UPDATE_REFS_MSG_ON_ERR);
		}
		return res < 0 ? error(_("writing root commit")) : 0;
	}

	cmd.git_cmd = 1;

	if (is_rebase_i(opts) && read_env_script(&cmd.env_array)) {
		const char *gpg_opt = gpg_sign_opt_quoted(opts);

		return error(_(staged_changes_advice),
			     gpg_opt, gpg_opt);
	}

	argv_array_push(&cmd.args, "commit");

	if (!(flags & VERIFY_MSG))
		argv_array_push(&cmd.args, "-n");
	if ((flags & AMEND_MSG))
		argv_array_push(&cmd.args, "--amend");
	if (opts->gpg_sign)
		argv_array_pushf(&cmd.args, "-S%s", opts->gpg_sign);
	if (defmsg)
		argv_array_pushl(&cmd.args, "-F", defmsg, NULL);
	else if (!(flags & EDIT_MSG))
		argv_array_pushl(&cmd.args, "-C", "HEAD", NULL);
	if ((flags & CLEANUP_MSG))
		argv_array_push(&cmd.args, "--cleanup=strip");
	if ((flags & EDIT_MSG))
		argv_array_push(&cmd.args, "-e");
	else if (!(flags & CLEANUP_MSG) &&
		 !opts->signoff && !opts->record_origin &&
		 git_config_get_value("commit.cleanup", &value))
		argv_array_push(&cmd.args, "--cleanup=verbatim");

	if ((flags & ALLOW_EMPTY))
		argv_array_push(&cmd.args, "--allow-empty");

	if (!(flags & EDIT_MSG))
		argv_array_push(&cmd.args, "--allow-empty-message");

	if (is_rebase_i(opts) && !(flags & EDIT_MSG))
		return run_command_silent_on_success(&cmd);
	else
		return run_command(&cmd);
}