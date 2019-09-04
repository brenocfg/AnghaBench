#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct merge_reuc_entry {scalar_t__ ancestor_mode; scalar_t__ our_mode; scalar_t__ their_mode; int /*<<< orphan*/  their_oid_str; int /*<<< orphan*/  our_oid_str; int /*<<< orphan*/  ancestor_oid_str; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {scalar_t__* mode; int /*<<< orphan*/ * oid; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_reuc_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 size_t git_index_reuc_entrycount (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_reuc_get_byindex (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int merge_test_reuc(git_index *index, const struct merge_reuc_entry expected[], size_t expected_len)
{
	size_t i;
	const git_index_reuc_entry *reuc_entry;
	git_oid expected_oid;

	/*
	dump_reuc(index);
	*/

	if (git_index_reuc_entrycount(index) != expected_len)
		return 0;

	for (i = 0; i < expected_len; i++) {
		if ((reuc_entry = git_index_reuc_get_byindex(index, i)) == NULL)
			return 0;

		if (strcmp(reuc_entry->path, expected[i].path) != 0 ||
			reuc_entry->mode[0] != expected[i].ancestor_mode ||
			reuc_entry->mode[1] != expected[i].our_mode ||
			reuc_entry->mode[2] != expected[i].their_mode)
			return 0;

		if (expected[i].ancestor_mode > 0) {
			cl_git_pass(git_oid_fromstr(&expected_oid, expected[i].ancestor_oid_str));

			if (git_oid_cmp(&reuc_entry->oid[0], &expected_oid) != 0)
				return 0;
		}

		if (expected[i].our_mode > 0) {
			cl_git_pass(git_oid_fromstr(&expected_oid, expected[i].our_oid_str));

			if (git_oid_cmp(&reuc_entry->oid[1], &expected_oid) != 0)
				return 0;
		}

		if (expected[i].their_mode > 0) {
			cl_git_pass(git_oid_fromstr(&expected_oid, expected[i].their_oid_str));

			if (git_oid_cmp(&reuc_entry->oid[2], &expected_oid) != 0)
				return 0;
		}
	}

	return 1;
}