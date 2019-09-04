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
struct tree_walk_context {int /*<<< orphan*/  buf; int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  git_tree_entry ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int git_packbuilder_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_tree_entry_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cb_tree_walk(
	const char *root, const git_tree_entry *entry, void *payload)
{
	int error;
	struct tree_walk_context *ctx = payload;

	/* A commit inside a tree represents a submodule commit and should be skipped. */
	if (git_tree_entry_type(entry) == GIT_OBJECT_COMMIT)
		return 0;

	if (!(error = git_buf_sets(&ctx->buf, root)) &&
		!(error = git_buf_puts(&ctx->buf, git_tree_entry_name(entry))))
		error = git_packbuilder_insert(
			ctx->pb, git_tree_entry_id(entry), git_buf_cstr(&ctx->buf));

	return error;
}