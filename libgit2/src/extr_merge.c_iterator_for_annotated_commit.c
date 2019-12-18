#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  tree; int /*<<< orphan*/  commit; int /*<<< orphan*/  index; } ;
typedef  TYPE_2__ git_annotated_commit ;

/* Variables and functions */
 scalar_t__ GIT_ANNOTATED_COMMIT_VIRTUAL ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int git_commit_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_owner (int /*<<< orphan*/ ) ; 
 int git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int git_iterator_for_nothing (int /*<<< orphan*/ **,TYPE_1__*) ; 
 int git_iterator_for_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int iterator_for_annotated_commit(
	git_iterator **out,
	git_annotated_commit *commit)
{
	git_iterator_options opts = GIT_ITERATOR_OPTIONS_INIT;
	int error;

	opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

	if (commit == NULL) {
		error = git_iterator_for_nothing(out, &opts);
	} else if (commit->type == GIT_ANNOTATED_COMMIT_VIRTUAL) {
		error = git_iterator_for_index(out, git_index_owner(commit->index), commit->index, &opts);
	} else {
		if (!commit->tree &&
			(error = git_commit_tree(&commit->tree, commit->commit)) < 0)
			goto done;

		error = git_iterator_for_tree(out, commit->tree, &opts);
	}

done:
	return error;
}