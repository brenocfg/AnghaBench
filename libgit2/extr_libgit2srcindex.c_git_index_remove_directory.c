#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_14__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_2__ git_index ;
struct TYPE_15__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int GIT_INDEX_ENTRY_STAGE (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_INDEX_STAGE_ANY ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int git_buf_sets (TYPE_3__*,char const*) ; 
 int git_path_to_dir (TYPE_3__*) ; 
 TYPE_1__* git_vector_get (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  index_find (size_t*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int index_remove_entry (TYPE_2__*,size_t) ; 

int git_index_remove_directory(git_index *index, const char *dir, int stage)
{
	git_buf pfx = GIT_BUF_INIT;
	int error = 0;
	size_t pos;
	git_index_entry *entry;

	if (!(error = git_buf_sets(&pfx, dir)) &&
		!(error = git_path_to_dir(&pfx)))
		index_find(&pos, index, pfx.ptr, pfx.size, GIT_INDEX_STAGE_ANY);

	while (!error) {
		entry = git_vector_get(&index->entries, pos);
		if (!entry || git__prefixcmp(entry->path, pfx.ptr) != 0)
			break;

		if (GIT_INDEX_ENTRY_STAGE(entry) != stage) {
			++pos;
			continue;
		}

		error = index_remove_entry(index, pos);

		/* removed entry at 'pos' so we don't need to increment */
	}

	git_buf_dispose(&pfx);

	return error;
}