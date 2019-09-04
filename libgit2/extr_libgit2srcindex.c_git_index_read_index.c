#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; } ;
typedef  TYPE_2__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_11__ {int /*<<< orphan*/  length; } ;
struct TYPE_13__ {TYPE_1__ entries; } ;
typedef  TYPE_3__ git_index ;

/* Variables and functions */
 int GIT_ITERATOR_DONT_IGNORE_CASE ; 
 int GIT_ITERATOR_INCLUDE_CONFLICTS ; 
 TYPE_2__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  git_index_owner (TYPE_3__ const*) ; 
 int git_index_read_iterator (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_iterator_for_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 

int git_index_read_index(
	git_index *index,
	const git_index *new_index)
{
	git_iterator *new_iterator = NULL;
	git_iterator_options opts = GIT_ITERATOR_OPTIONS_INIT;
	int error;

	opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_INCLUDE_CONFLICTS;

	if ((error = git_iterator_for_index(&new_iterator,
		git_index_owner(new_index), (git_index *)new_index, &opts)) < 0 ||
		(error = git_index_read_iterator(index, new_iterator,
		new_index->entries.length)) < 0)
		goto done;

done:
	git_iterator_free(new_iterator);
	return error;
}