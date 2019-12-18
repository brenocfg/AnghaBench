#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct diff_options {int stat_width; int stat_graph_width; int output_format; int /*<<< orphan*/  detect_rename; } ;
struct commit_list {int dummy; } ;
struct TYPE_5__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_DETECT_RENAME ; 
 int DIFF_FORMAT_DIFFSTAT ; 
 int DIFF_FORMAT_SUMMARY ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  close_object_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_flush (struct diff_options*) ; 
 int /*<<< orphan*/  diff_setup_done (struct diff_options*) ; 
 int /*<<< orphan*/  diff_tree_oid (struct object_id const*,struct object_id const*,char*,struct diff_options*) ; 
 int /*<<< orphan*/  diffcore_std (struct diff_options*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 TYPE_4__ merge_msg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  repo_diff_setup (TYPE_2__*,struct diff_options*) ; 
 int /*<<< orphan*/  run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_hook_le (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ show_diffstat ; 
 scalar_t__ squash ; 
 int /*<<< orphan*/  squash_message (struct commit*,struct commit_list*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_2__* the_repository ; 
 int /*<<< orphan*/  update_ref (int /*<<< orphan*/ ,char*,struct object_id const*,struct object_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void finish(struct commit *head_commit,
		   struct commit_list *remoteheads,
		   const struct object_id *new_head, const char *msg)
{
	struct strbuf reflog_message = STRBUF_INIT;
	const struct object_id *head = &head_commit->object.oid;

	if (!msg)
		strbuf_addstr(&reflog_message, getenv("GIT_REFLOG_ACTION"));
	else {
		if (verbosity >= 0)
			printf("%s\n", msg);
		strbuf_addf(&reflog_message, "%s: %s",
			getenv("GIT_REFLOG_ACTION"), msg);
	}
	if (squash) {
		squash_message(head_commit, remoteheads);
	} else {
		if (verbosity >= 0 && !merge_msg.len)
			printf(_("No merge message -- not updating HEAD\n"));
		else {
			const char *argv_gc_auto[] = { "gc", "--auto", NULL };
			update_ref(reflog_message.buf, "HEAD", new_head, head,
				   0, UPDATE_REFS_DIE_ON_ERR);
			/*
			 * We ignore errors in 'gc --auto', since the
			 * user should see them.
			 */
			close_object_store(the_repository->objects);
			run_command_v_opt(argv_gc_auto, RUN_GIT_CMD);
		}
	}
	if (new_head && show_diffstat) {
		struct diff_options opts;
		repo_diff_setup(the_repository, &opts);
		opts.stat_width = -1; /* use full terminal width */
		opts.stat_graph_width = -1; /* respect statGraphWidth config */
		opts.output_format |=
			DIFF_FORMAT_SUMMARY | DIFF_FORMAT_DIFFSTAT;
		opts.detect_rename = DIFF_DETECT_RENAME;
		diff_setup_done(&opts);
		diff_tree_oid(head, new_head, "", &opts);
		diffcore_std(&opts);
		diff_flush(&opts);
	}

	/* Run a post-merge hook */
	run_hook_le(NULL, "post-merge", squash ? "1" : "0", NULL);

	strbuf_release(&reflog_message);
}