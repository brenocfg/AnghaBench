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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 int /*<<< orphan*/  GIT_UNUSED (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int remove_note_in_tree_enotfound_cb(
	git_tree **out,
	git_repository *repo,
	git_tree *parent,
	git_oid *note_oid,
	const char *annotated_object_sha,
	int fanout,
	int current_error)
{
	GIT_UNUSED(out);
	GIT_UNUSED(repo);
	GIT_UNUSED(parent);
	GIT_UNUSED(note_oid);
	GIT_UNUSED(fanout);

	git_error_set(GIT_ERROR_REPOSITORY, "object '%s' has no note", annotated_object_sha);
	return current_error;
}