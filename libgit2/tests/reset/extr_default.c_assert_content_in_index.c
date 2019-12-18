#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t count; int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _index ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_index_find (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* git_index_get_byindex (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_content_in_index(
	git_strarray *pathspecs,
	bool should_exist,
	git_strarray *expected_shas)
{
	size_t i, pos;
	int error;

	for (i = 0; i < pathspecs->count; i++) {
		error = git_index_find(&pos, _index, pathspecs->strings[i]);

		if (should_exist) {
			const git_index_entry *entry;

			cl_assert(error != GIT_ENOTFOUND);

			entry = git_index_get_byindex(_index, pos);
			cl_assert(entry != NULL);

			if (!expected_shas)
				continue;

			cl_git_pass(git_oid_streq(&entry->id, expected_shas->strings[i]));
		} else
			cl_assert_equal_i(should_exist, error != GIT_ENOTFOUND);
	}
}