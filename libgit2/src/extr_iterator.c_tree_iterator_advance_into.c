#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_iterator_frame ;
struct TYPE_4__ {int /*<<< orphan*/  tree_entry; } ;
typedef  TYPE_1__ tree_iterator_entry ;
typedef  int /*<<< orphan*/  tree_iterator ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_tree_entry__is_tree (int /*<<< orphan*/ ) ; 
 int iterator__do_autoexpand (int /*<<< orphan*/ *) ; 
 int tree_iterator_advance (int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* tree_iterator_current_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tree_iterator_current_frame (int /*<<< orphan*/ *) ; 
 int tree_iterator_frame_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int tree_iterator_advance_into(
	const git_index_entry **out, git_iterator *i)
{
	tree_iterator *iter = (tree_iterator *)i;
    tree_iterator_frame *frame;
	tree_iterator_entry *prev_entry;
	int error;

	if (out)
		*out = NULL;

	if ((frame = tree_iterator_current_frame(iter)) == NULL)
		return GIT_ITEROVER;

	/* get the last seen entry */
	prev_entry = tree_iterator_current_entry(frame);

	/* it's legal to call advance_into when auto-expand is on.  in this case,
	 * we will have pushed a new (empty) frame on to the stack for this
	 * new directory.  since it's empty, its current_entry should be null.
	 */
	assert(iterator__do_autoexpand(i) ^ (prev_entry != NULL));

	if (prev_entry) {
		if (!git_tree_entry__is_tree(prev_entry->tree_entry))
			return 0;

		if ((error = tree_iterator_frame_push(iter, prev_entry)) < 0)
			return error;
	}

	/* we've advanced into the directory in question, let advance
	 * find the first entry
	 */
	return tree_iterator_advance(out, i);
}