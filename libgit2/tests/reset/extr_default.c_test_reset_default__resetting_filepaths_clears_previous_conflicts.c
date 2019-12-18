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
struct TYPE_6__ {char** strings; int count; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_7__ {char** strings; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _index ; 
 TYPE_2__ _pathspecs ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _target ; 
 int /*<<< orphan*/  assert_content_in_index (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_get (int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reset_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initialize (char*) ; 

void test_reset_default__resetting_filepaths_clears_previous_conflicts(void)
{
	const git_index_entry *conflict_entry[3];
	git_strarray after;

	char *paths[] = { "conflicts-one.txt" };
	char *after_shas[] = { "1f85ca51b8e0aac893a621b61a9c2661d6aa6d81" };

	initialize("mergedrepo");

	_pathspecs.strings = paths;
	_pathspecs.count = 1;
	after.strings = after_shas;
	after.count = 1;

	cl_git_pass(git_index_conflict_get(&conflict_entry[0], &conflict_entry[1],
		&conflict_entry[2], _index, "conflicts-one.txt"));

	cl_git_pass(git_revparse_single(&_target, _repo, "9a05ccb"));
	cl_git_pass(git_reset_default(_repo, _target, &_pathspecs));

	assert_content_in_index(&_pathspecs, true, &after);

	cl_assert_equal_i(GIT_ENOTFOUND, git_index_conflict_get(&conflict_entry[0],
		&conflict_entry[1], &conflict_entry[2], _index, "conflicts-one.txt"));
}