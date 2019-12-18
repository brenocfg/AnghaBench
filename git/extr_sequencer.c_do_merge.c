#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char const* buf; int len; } ;
struct repository {TYPE_5__* index; } ;
struct replay_opts {int xopts_nr; char* strategy; char* gpg_sign; int /*<<< orphan*/  allow_rerere_auto; int /*<<< orphan*/ * xopts; scalar_t__ allow_ff; int /*<<< orphan*/  squash_onto; scalar_t__ have_squash_onto; } ;
struct merge_options {char* branch1; char* branch2; int buffer_output; struct strbuf obuf; } ;
struct lock_file {int dummy; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct TYPE_12__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_4__ object; TYPE_3__* parents; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;
struct TYPE_15__ {struct commit_list* next; } ;
struct TYPE_14__ {int hexsz; } ;
struct TYPE_13__ {scalar_t__ cache_changed; } ;
struct TYPE_11__ {struct commit_list* next; TYPE_2__* item; } ;
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
struct TYPE_10__ {TYPE_1__ object; } ;

/* Variables and functions */
 int AMEND_MSG ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  COMMIT_LOCK ; 
 int EDIT_MSG ; 
 int /*<<< orphan*/  LOCK_REPORT_ON_ERROR ; 
 struct strbuf STRBUF_INIT ; 
 int TODO_EDIT_MERGE_MSG ; 
 int VERIFY_MSG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_8__* commit_list_insert (struct commit*,struct commit_list**) ; 
 scalar_t__ discard_index (TYPE_5__*) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  error_errno (int /*<<< orphan*/ ,char*) ; 
 int fast_forward_to (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct replay_opts*) ; 
 int /*<<< orphan*/  find_commit_subject (char const*,char const**) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 int /*<<< orphan*/  git_author_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 char* git_path_merge_head (struct repository*) ; 
 char* git_path_merge_mode (struct repository*) ; 
 char* git_path_merge_msg (struct repository*) ; 
 char* gpg_sign_opt_quoted (struct replay_opts*) ; 
 int /*<<< orphan*/  init_merge_options (struct merge_options*,struct repository*) ; 
 scalar_t__ isspace (char const) ; 
 struct commit* lookup_commit_reference_by_name (char*) ; 
 struct commit* lookup_label (char const*,int,struct strbuf*) ; 
 int merge_recursive (struct merge_options*,struct commit*,struct commit*,struct commit_list*,struct commit**) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_env_script (int /*<<< orphan*/ *) ; 
 scalar_t__ repo_hold_locked_index (struct repository*,struct lock_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  repo_rerere (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  run_git_commit (struct repository*,char*,struct replay_opts*,int) ; 
 char* staged_changes_advice ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strspn (char const*,char*) ; 
 TYPE_6__* the_hash_algo ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 
 int /*<<< orphan*/  write_author_script (char const*) ; 
 scalar_t__ write_locked_index (TYPE_5__*,struct lock_file*,int /*<<< orphan*/ ) ; 
 int write_message (char const*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_merge(struct repository *r,
		    struct commit *commit,
		    const char *arg, int arg_len,
		    int flags, struct replay_opts *opts)
{
	int run_commit_flags = (flags & TODO_EDIT_MERGE_MSG) ?
		EDIT_MSG | VERIFY_MSG : 0;
	struct strbuf ref_name = STRBUF_INIT;
	struct commit *head_commit, *merge_commit, *i;
	struct commit_list *bases, *j, *reversed = NULL;
	struct commit_list *to_merge = NULL, **tail = &to_merge;
	const char *strategy = !opts->xopts_nr &&
		(!opts->strategy || !strcmp(opts->strategy, "recursive")) ?
		NULL : opts->strategy;
	struct merge_options o;
	int merge_arg_len, oneline_offset, can_fast_forward, ret, k;
	static struct lock_file lock;
	const char *p;

	if (repo_hold_locked_index(r, &lock, LOCK_REPORT_ON_ERROR) < 0) {
		ret = -1;
		goto leave_merge;
	}

	head_commit = lookup_commit_reference_by_name("HEAD");
	if (!head_commit) {
		ret = error(_("cannot merge without a current revision"));
		goto leave_merge;
	}

	/*
	 * For octopus merges, the arg starts with the list of revisions to be
	 * merged. The list is optionally followed by '#' and the oneline.
	 */
	merge_arg_len = oneline_offset = arg_len;
	for (p = arg; p - arg < arg_len; p += strspn(p, " \t\n")) {
		if (!*p)
			break;
		if (*p == '#' && (!p[1] || isspace(p[1]))) {
			p += 1 + strspn(p + 1, " \t\n");
			oneline_offset = p - arg;
			break;
		}
		k = strcspn(p, " \t\n");
		if (!k)
			continue;
		merge_commit = lookup_label(p, k, &ref_name);
		if (!merge_commit) {
			ret = error(_("unable to parse '%.*s'"), k, p);
			goto leave_merge;
		}
		tail = &commit_list_insert(merge_commit, tail)->next;
		p += k;
		merge_arg_len = p - arg;
	}

	if (!to_merge) {
		ret = error(_("nothing to merge: '%.*s'"), arg_len, arg);
		goto leave_merge;
	}

	if (opts->have_squash_onto &&
	    oideq(&head_commit->object.oid, &opts->squash_onto)) {
		/*
		 * When the user tells us to "merge" something into a
		 * "[new root]", let's simply fast-forward to the merge head.
		 */
		rollback_lock_file(&lock);
		if (to_merge->next)
			ret = error(_("octopus merge cannot be executed on "
				      "top of a [new root]"));
		else
			ret = fast_forward_to(r, &to_merge->item->object.oid,
					      &head_commit->object.oid, 0,
					      opts);
		goto leave_merge;
	}

	if (commit) {
		const char *message = get_commit_buffer(commit, NULL);
		const char *body;
		int len;

		if (!message) {
			ret = error(_("could not get commit message of '%s'"),
				    oid_to_hex(&commit->object.oid));
			goto leave_merge;
		}
		write_author_script(message);
		find_commit_subject(message, &body);
		len = strlen(body);
		ret = write_message(body, len, git_path_merge_msg(r), 0);
		unuse_commit_buffer(commit, message);
		if (ret) {
			error_errno(_("could not write '%s'"),
				    git_path_merge_msg(r));
			goto leave_merge;
		}
	} else {
		struct strbuf buf = STRBUF_INIT;
		int len;

		strbuf_addf(&buf, "author %s", git_author_info(0));
		write_author_script(buf.buf);
		strbuf_reset(&buf);

		if (oneline_offset < arg_len) {
			p = arg + oneline_offset;
			len = arg_len - oneline_offset;
		} else {
			strbuf_addf(&buf, "Merge %s '%.*s'",
				    to_merge->next ? "branches" : "branch",
				    merge_arg_len, arg);
			p = buf.buf;
			len = buf.len;
		}

		ret = write_message(p, len, git_path_merge_msg(r), 0);
		strbuf_release(&buf);
		if (ret) {
			error_errno(_("could not write '%s'"),
				    git_path_merge_msg(r));
			goto leave_merge;
		}
	}

	/*
	 * If HEAD is not identical to the first parent of the original merge
	 * commit, we cannot fast-forward.
	 */
	can_fast_forward = opts->allow_ff && commit && commit->parents &&
		oideq(&commit->parents->item->object.oid,
		      &head_commit->object.oid);

	/*
	 * If any merge head is different from the original one, we cannot
	 * fast-forward.
	 */
	if (can_fast_forward) {
		struct commit_list *p = commit->parents->next;

		for (j = to_merge; j && p; j = j->next, p = p->next)
			if (!oideq(&j->item->object.oid,
				   &p->item->object.oid)) {
				can_fast_forward = 0;
				break;
			}
		/*
		 * If the number of merge heads differs from the original merge
		 * commit, we cannot fast-forward.
		 */
		if (j || p)
			can_fast_forward = 0;
	}

	if (can_fast_forward) {
		rollback_lock_file(&lock);
		ret = fast_forward_to(r, &commit->object.oid,
				      &head_commit->object.oid, 0, opts);
		if (flags & TODO_EDIT_MERGE_MSG) {
			run_commit_flags |= AMEND_MSG;
			goto fast_forward_edit;
		}
		goto leave_merge;
	}

	if (strategy || to_merge->next) {
		/* Octopus merge */
		struct child_process cmd = CHILD_PROCESS_INIT;

		if (read_env_script(&cmd.env_array)) {
			const char *gpg_opt = gpg_sign_opt_quoted(opts);

			ret = error(_(staged_changes_advice), gpg_opt, gpg_opt);
			goto leave_merge;
		}

		cmd.git_cmd = 1;
		argv_array_push(&cmd.args, "merge");
		argv_array_push(&cmd.args, "-s");
		if (!strategy)
			argv_array_push(&cmd.args, "octopus");
		else {
			argv_array_push(&cmd.args, strategy);
			for (k = 0; k < opts->xopts_nr; k++)
				argv_array_pushf(&cmd.args,
						 "-X%s", opts->xopts[k]);
		}
		argv_array_push(&cmd.args, "--no-edit");
		argv_array_push(&cmd.args, "--no-ff");
		argv_array_push(&cmd.args, "--no-log");
		argv_array_push(&cmd.args, "--no-stat");
		argv_array_push(&cmd.args, "-F");
		argv_array_push(&cmd.args, git_path_merge_msg(r));
		if (opts->gpg_sign)
			argv_array_push(&cmd.args, opts->gpg_sign);

		/* Add the tips to be merged */
		for (j = to_merge; j; j = j->next)
			argv_array_push(&cmd.args,
					oid_to_hex(&j->item->object.oid));

		strbuf_release(&ref_name);
		unlink(git_path_cherry_pick_head(r));
		rollback_lock_file(&lock);

		rollback_lock_file(&lock);
		ret = run_command(&cmd);

		/* force re-reading of the cache */
		if (!ret && (discard_index(r->index) < 0 ||
			     repo_read_index(r) < 0))
			ret = error(_("could not read index"));
		goto leave_merge;
	}

	merge_commit = to_merge->item;
	bases = get_merge_bases(head_commit, merge_commit);
	if (bases && oideq(&merge_commit->object.oid,
			   &bases->item->object.oid)) {
		ret = 0;
		/* skip merging an ancestor of HEAD */
		goto leave_merge;
	}

	write_message(oid_to_hex(&merge_commit->object.oid), the_hash_algo->hexsz,
		      git_path_merge_head(r), 0);
	write_message("no-ff", 5, git_path_merge_mode(r), 0);

	for (j = bases; j; j = j->next)
		commit_list_insert(j->item, &reversed);
	free_commit_list(bases);

	repo_read_index(r);
	init_merge_options(&o, r);
	o.branch1 = "HEAD";
	o.branch2 = ref_name.buf;
	o.buffer_output = 2;

	ret = merge_recursive(&o, head_commit, merge_commit, reversed, &i);
	if (ret <= 0)
		fputs(o.obuf.buf, stdout);
	strbuf_release(&o.obuf);
	if (ret < 0) {
		error(_("could not even attempt to merge '%.*s'"),
		      merge_arg_len, arg);
		goto leave_merge;
	}
	/*
	 * The return value of merge_recursive() is 1 on clean, and 0 on
	 * unclean merge.
	 *
	 * Let's reverse that, so that do_merge() returns 0 upon success and
	 * 1 upon failed merge (keeping the return value -1 for the cases where
	 * we will want to reschedule the `merge` command).
	 */
	ret = !ret;

	if (r->index->cache_changed &&
	    write_locked_index(r->index, &lock, COMMIT_LOCK)) {
		ret = error(_("merge: Unable to write new index file"));
		goto leave_merge;
	}

	rollback_lock_file(&lock);
	if (ret)
		repo_rerere(r, opts->allow_rerere_auto);
	else
		/*
		 * In case of problems, we now want to return a positive
		 * value (a negative one would indicate that the `merge`
		 * command needs to be rescheduled).
		 */
	fast_forward_edit:
		ret = !!run_git_commit(r, git_path_merge_msg(r), opts,
				       run_commit_flags);

leave_merge:
	strbuf_release(&ref_name);
	rollback_lock_file(&lock);
	free_commit_list(to_merge);
	return ret;
}