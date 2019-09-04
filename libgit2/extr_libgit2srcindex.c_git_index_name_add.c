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
struct TYPE_8__ {void* theirs; void* ours; void* ancestor; } ;
typedef  TYPE_1__ git_index_name_entry ;
struct TYPE_9__ {int dirty; int /*<<< orphan*/  names; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 
 void* git__strdup (char const*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  index_name_entry_free (TYPE_1__*) ; 

int git_index_name_add(git_index *index,
	const char *ancestor, const char *ours, const char *theirs)
{
	git_index_name_entry *conflict_name;

	assert((ancestor && ours) || (ancestor && theirs) || (ours && theirs));

	conflict_name = git__calloc(1, sizeof(git_index_name_entry));
	GIT_ERROR_CHECK_ALLOC(conflict_name);

	if ((ancestor && !(conflict_name->ancestor = git__strdup(ancestor))) ||
		(ours     && !(conflict_name->ours     = git__strdup(ours))) ||
		(theirs   && !(conflict_name->theirs   = git__strdup(theirs))) ||
		git_vector_insert(&index->names, conflict_name) < 0)
	{
		index_name_entry_free(conflict_name);
		return -1;
	}

	index->dirty = 1;
	return 0;
}