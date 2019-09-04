#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_11__ {scalar_t__ (* entries_cmp_path ) (char*,char const*) ;int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_STAGE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t git_index_entrycount (TYPE_2__*) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub1 (char*,char const*) ; 

__attribute__((used)) static int index_conflict__get_byindex(
	const git_index_entry **ancestor_out,
	const git_index_entry **our_out,
	const git_index_entry **their_out,
	git_index *index,
	size_t n)
{
	const git_index_entry *conflict_entry;
	const char *path = NULL;
	size_t count;
	int stage, len = 0;

	assert(ancestor_out && our_out && their_out && index);

	*ancestor_out = NULL;
	*our_out = NULL;
	*their_out = NULL;

	for (count = git_index_entrycount(index); n < count; ++n) {
		conflict_entry = git_vector_get(&index->entries, n);

		if (path && index->entries_cmp_path(conflict_entry->path, path) != 0)
			break;

		stage = GIT_INDEX_ENTRY_STAGE(conflict_entry);
		path = conflict_entry->path;

		switch (stage) {
		case 3:
			*their_out = conflict_entry;
			len++;
			break;
		case 2:
			*our_out = conflict_entry;
			len++;
			break;
		case 1:
			*ancestor_out = conflict_entry;
			len++;
			break;
		default:
			break;
		};
	}

	return len;
}