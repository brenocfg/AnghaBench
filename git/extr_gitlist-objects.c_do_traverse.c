#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct tree {TYPE_1__ object; } ;
struct traversal_context {TYPE_2__* revs; int /*<<< orphan*/  show_data; int /*<<< orphan*/  (* show_commit ) (struct commit*,int /*<<< orphan*/ ) ;} ;
struct strbuf {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_5__ {scalar_t__ tree_blobs_in_commit_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_USER_GIVEN ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  add_pending_tree (TYPE_2__*,struct tree*) ; 
 struct tree* get_commit_tree (struct commit*) ; 
 struct commit* get_revision (TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_trees_and_blobs (struct traversal_context*,struct strbuf*) ; 

__attribute__((used)) static void do_traverse(struct traversal_context *ctx)
{
	struct commit *commit;
	struct strbuf csp; /* callee's scratch pad */
	strbuf_init(&csp, PATH_MAX);

	while ((commit = get_revision(ctx->revs)) != NULL) {
		/*
		 * an uninteresting boundary commit may not have its tree
		 * parsed yet, but we are not going to show them anyway
		 */
		if (get_commit_tree(commit)) {
			struct tree *tree = get_commit_tree(commit);
			tree->object.flags |= NOT_USER_GIVEN;
			add_pending_tree(ctx->revs, tree);
		}
		ctx->show_commit(commit, ctx->show_data);

		if (ctx->revs->tree_blobs_in_commit_order)
			/*
			 * NEEDSWORK: Adding the tree and then flushing it here
			 * needs a reallocation for each commit. Can we pass the
			 * tree directory without allocation churn?
			 */
			traverse_trees_and_blobs(ctx, &csp);
	}
	traverse_trees_and_blobs(ctx, &csp);
	strbuf_release(&csp);
}