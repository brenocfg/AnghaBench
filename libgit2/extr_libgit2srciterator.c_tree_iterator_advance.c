#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_24__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_16__ ;

/* Type definitions */
struct TYPE_29__ {size_t length; TYPE_2__** contents; } ;
struct TYPE_28__ {size_t next_idx; TYPE_24__ entries; } ;
typedef  TYPE_1__ tree_iterator_frame ;
struct TYPE_30__ {int /*<<< orphan*/  tree_entry; } ;
typedef  TYPE_2__ tree_iterator_entry ;
struct TYPE_26__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_27__ {int /*<<< orphan*/  flags; } ;
struct TYPE_31__ {int /*<<< orphan*/  entry; TYPE_16__ entry_path; TYPE_18__ base; } ;
typedef  TYPE_3__ tree_iterator ;
typedef  int /*<<< orphan*/  git_iterator ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_FIRST_ACCESS ; 
 int GIT_ITEROVER ; 
 int git_tree_entry__is_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_is_sorted (TYPE_24__*) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_24__*) ; 
 scalar_t__ iterator__do_autoexpand (TYPE_3__*) ; 
 scalar_t__ iterator__ignore_case (TYPE_18__*) ; 
 int /*<<< orphan*/  iterator__include_trees (TYPE_3__*) ; 
 scalar_t__ iterator_has_ended (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterator_has_started (TYPE_18__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iterator_pathlist_next_is (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int tree_iterator_compute_path (TYPE_16__*,TYPE_2__*) ; 
 TYPE_2__* tree_iterator_current_entry (TYPE_1__*) ; 
 TYPE_1__* tree_iterator_current_frame (TYPE_3__*) ; 
 scalar_t__ tree_iterator_entry_cmp_icase (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tree_iterator_frame_pop (TYPE_3__*) ; 
 int tree_iterator_frame_push (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  tree_iterator_set_current (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int tree_iterator_advance(const git_index_entry **out, git_iterator *i)
{
	tree_iterator *iter = (tree_iterator *)i;
	int error = 0;

	iter->base.flags |= GIT_ITERATOR_FIRST_ACCESS;

	/* examine tree entries until we find the next one to return */
	while (true) {
		tree_iterator_entry *prev_entry, *entry;
		tree_iterator_frame *frame;
		bool is_tree;

		if ((frame = tree_iterator_current_frame(iter)) == NULL) {
			error = GIT_ITEROVER;
			break;
		}

		/* no more entries in this frame.  pop the frame out */
		if (frame->next_idx == frame->entries.length) {
			tree_iterator_frame_pop(iter);
			continue;
		}

		/* we may have coalesced the contents of case-insensitively same-named
		 * directories, so do the sort now.
		 */
		if (frame->next_idx == 0 && !git_vector_is_sorted(&frame->entries))
			git_vector_sort(&frame->entries);

		/* we have more entries in the current frame, that's our next entry */
		prev_entry = tree_iterator_current_entry(frame);
		entry = frame->entries.contents[frame->next_idx];
		frame->next_idx++;

		/* we can have collisions when iterating case insensitively.  (eg,
		 * 'A/a' and 'a/A').  squash this one if it's already been seen.
		 */
		if (iterator__ignore_case(&iter->base) &&
			prev_entry &&
			tree_iterator_entry_cmp_icase(prev_entry, entry) == 0)
			continue;

		if ((error = tree_iterator_compute_path(&iter->entry_path, entry)) < 0)
			break;

		/* if this path is before our start, advance over this entry */
		if (!iterator_has_started(&iter->base, iter->entry_path.ptr, false))
			continue;

		/* if this path is after our end, stop */
		if (iterator_has_ended(&iter->base, iter->entry_path.ptr)) {
			error = GIT_ITEROVER;
			break;
		}

		/* if we have a list of paths we're interested in, examine it */
		if (!iterator_pathlist_next_is(&iter->base, iter->entry_path.ptr))
			continue;

		is_tree = git_tree_entry__is_tree(entry->tree_entry);

		/* if we are *not* including trees then advance over this entry */
		if (is_tree && !iterator__include_trees(iter)) {

			/* if we've found a tree (and are not returning it to the caller)
			 * and we are autoexpanding, then we want to return the first
			 * child.  push the new directory and advance.
			 */
			if (iterator__do_autoexpand(iter)) {
				if ((error = tree_iterator_frame_push(iter, entry)) < 0)
					break;
			}

			continue;
		}

		tree_iterator_set_current(iter, frame, entry);

		/* if we are autoexpanding, then push this as a new frame, so that
		 * the next call to `advance` will dive into this directory.
		 */
		if (is_tree && iterator__do_autoexpand(iter))
			error = tree_iterator_frame_push(iter, entry);

		break;
	}

	if (out)
		*out = (error == 0) ? &iter->entry : NULL;

	return error;
}