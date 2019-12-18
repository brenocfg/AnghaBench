#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct todo_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct TYPE_3__ {char* buf; int len; } ;
struct replay_opts {scalar_t__ current_fixup_count; TYPE_1__ current_fixups; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 unsigned int ALLOW_EMPTY ; 
 unsigned int AMEND_MSG ; 
 int /*<<< orphan*/  BUG (char*,char const*) ; 
 unsigned int CLEANUP_MSG ; 
 unsigned int EDIT_MSG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 scalar_t__ file_exists (char const*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,struct object_id*) ; 
 char* git_path_cherry_pick_head (struct repository*) ; 
 char const* git_path_merge_head (struct repository*) ; 
 int /*<<< orphan*/  has_uncommitted_changes (struct repository*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_unstaged_changes (struct repository*,int) ; 
 scalar_t__ is_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oideq (struct object_id*,struct object_id*) ; 
 scalar_t__ parse_head (struct repository*,struct commit**) ; 
 int /*<<< orphan*/  peek_command (struct todo_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_oneliner (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 char const* rebase_path_amend () ; 
 char const* rebase_path_current_fixups () ; 
 char const* rebase_path_fixup_msg () ; 
 int /*<<< orphan*/ * rebase_path_message () ; 
 char const* rebase_path_squash_msg () ; 
 char const* rebase_path_stopped_sha () ; 
 scalar_t__ run_git_commit (struct repository*,int /*<<< orphan*/ *,struct replay_opts*,unsigned int) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_setlen (TYPE_1__*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 
 scalar_t__ write_message (char const*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int commit_staged_changes(struct repository *r,
				 struct replay_opts *opts,
				 struct todo_list *todo_list)
{
	unsigned int flags = ALLOW_EMPTY | EDIT_MSG;
	unsigned int final_fixup = 0, is_clean;

	if (has_unstaged_changes(r, 1))
		return error(_("cannot rebase: You have unstaged changes."));

	is_clean = !has_uncommitted_changes(r, 0);

	if (file_exists(rebase_path_amend())) {
		struct strbuf rev = STRBUF_INIT;
		struct object_id head, to_amend;

		if (get_oid("HEAD", &head))
			return error(_("cannot amend non-existing commit"));
		if (!read_oneliner(&rev, rebase_path_amend(), 0))
			return error(_("invalid file: '%s'"), rebase_path_amend());
		if (get_oid_hex(rev.buf, &to_amend))
			return error(_("invalid contents: '%s'"),
				rebase_path_amend());
		if (!is_clean && !oideq(&head, &to_amend))
			return error(_("\nYou have uncommitted changes in your "
				       "working tree. Please, commit them\n"
				       "first and then run 'git rebase "
				       "--continue' again."));
		/*
		 * When skipping a failed fixup/squash, we need to edit the
		 * commit message, the current fixup list and count, and if it
		 * was the last fixup/squash in the chain, we need to clean up
		 * the commit message and if there was a squash, let the user
		 * edit it.
		 */
		if (!is_clean || !opts->current_fixup_count)
			; /* this is not the final fixup */
		else if (!oideq(&head, &to_amend) ||
			 !file_exists(rebase_path_stopped_sha())) {
			/* was a final fixup or squash done manually? */
			if (!is_fixup(peek_command(todo_list, 0))) {
				unlink(rebase_path_fixup_msg());
				unlink(rebase_path_squash_msg());
				unlink(rebase_path_current_fixups());
				strbuf_reset(&opts->current_fixups);
				opts->current_fixup_count = 0;
			}
		} else {
			/* we are in a fixup/squash chain */
			const char *p = opts->current_fixups.buf;
			int len = opts->current_fixups.len;

			opts->current_fixup_count--;
			if (!len)
				BUG("Incorrect current_fixups:\n%s", p);
			while (len && p[len - 1] != '\n')
				len--;
			strbuf_setlen(&opts->current_fixups, len);
			if (write_message(p, len, rebase_path_current_fixups(),
					  0) < 0)
				return error(_("could not write file: '%s'"),
					     rebase_path_current_fixups());

			/*
			 * If a fixup/squash in a fixup/squash chain failed, the
			 * commit message is already correct, no need to commit
			 * it again.
			 *
			 * Only if it is the final command in the fixup/squash
			 * chain, and only if the chain is longer than a single
			 * fixup/squash command (which was just skipped), do we
			 * actually need to re-commit with a cleaned up commit
			 * message.
			 */
			if (opts->current_fixup_count > 0 &&
			    !is_fixup(peek_command(todo_list, 0))) {
				final_fixup = 1;
				/*
				 * If there was not a single "squash" in the
				 * chain, we only need to clean up the commit
				 * message, no need to bother the user with
				 * opening the commit message in the editor.
				 */
				if (!starts_with(p, "squash ") &&
				    !strstr(p, "\nsquash "))
					flags = (flags & ~EDIT_MSG) | CLEANUP_MSG;
			} else if (is_fixup(peek_command(todo_list, 0))) {
				/*
				 * We need to update the squash message to skip
				 * the latest commit message.
				 */
				struct commit *commit;
				const char *path = rebase_path_squash_msg();

				if (parse_head(r, &commit) ||
				    !(p = get_commit_buffer(commit, NULL)) ||
				    write_message(p, strlen(p), path, 0)) {
					unuse_commit_buffer(commit, p);
					return error(_("could not write file: "
						       "'%s'"), path);
				}
				unuse_commit_buffer(commit, p);
			}
		}

		strbuf_release(&rev);
		flags |= AMEND_MSG;
	}

	if (is_clean) {
		const char *cherry_pick_head = git_path_cherry_pick_head(r);

		if (file_exists(cherry_pick_head) && unlink(cherry_pick_head))
			return error(_("could not remove CHERRY_PICK_HEAD"));
		if (!final_fixup)
			return 0;
	}

	if (run_git_commit(r, final_fixup ? NULL : rebase_path_message(),
			   opts, flags))
		return error(_("could not commit staged changes."));
	unlink(rebase_path_amend());
	unlink(git_path_merge_head(r));
	if (final_fixup) {
		unlink(rebase_path_fixup_msg());
		unlink(rebase_path_squash_msg());
	}
	if (opts->current_fixup_count > 0) {
		/*
		 * Whether final fixup or not, we just cleaned up the commit
		 * message...
		 */
		unlink(rebase_path_current_fixups());
		strbuf_reset(&opts->current_fixups);
		opts->current_fixup_count = 0;
	}
	return 0;
}