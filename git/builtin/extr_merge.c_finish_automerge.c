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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 scalar_t__ FF_NO ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 scalar_t__ commit_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,struct commit_list*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ fast_forward ; 
 int /*<<< orphan*/  finish (struct commit*,struct commit_list*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 TYPE_1__ merge_msg ; 
 int /*<<< orphan*/  prepare_to_commit (struct commit_list*) ; 
 int /*<<< orphan*/  remove_merge_branch_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sign_commit ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_tree_trivial (struct object_id*) ; 

__attribute__((used)) static int finish_automerge(struct commit *head,
			    int head_subsumed,
			    struct commit_list *common,
			    struct commit_list *remoteheads,
			    struct object_id *result_tree,
			    const char *wt_strategy)
{
	struct commit_list *parents = NULL;
	struct strbuf buf = STRBUF_INIT;
	struct object_id result_commit;

	write_tree_trivial(result_tree);
	free_commit_list(common);
	parents = remoteheads;
	if (!head_subsumed || fast_forward == FF_NO)
		commit_list_insert(head, &parents);
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree, parents,
			&result_commit, NULL, sign_commit))
		die(_("failed to write commit object"));
	strbuf_addf(&buf, "Merge made by the '%s' strategy.", wt_strategy);
	finish(head, remoteheads, &result_commit, buf.buf);
	strbuf_release(&buf);
	remove_merge_branch_state(the_repository);
	return 0;
}