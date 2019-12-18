#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_11__ {char** strings; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  _index ; 
 TYPE_4__ _pathspecs ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _target ; 
 int /*<<< orphan*/  assert_content_in_index (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reset_default (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  initialize (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 

void test_reset_default__staged_rename_reset_delete(void)
{
	git_index_entry entry;
	const git_index_entry *existing;
	char *paths[] = { "new.txt" };

	initialize("testrepo2");

	existing = git_index_get_bypath(_index, "new.txt", 0);
	cl_assert(existing);
	memcpy(&entry, existing, sizeof(entry));

	cl_git_pass(git_index_remove_bypath(_index, "new.txt"));

	entry.path = "renamed.txt";
	cl_git_pass(git_index_add(_index, &entry));

	_pathspecs.strings = paths;
	_pathspecs.count = 1;

	assert_content_in_index(&_pathspecs, false, NULL);

	cl_git_pass(git_revparse_single(&_target, _repo, "HEAD"));
	cl_git_pass(git_reset_default(_repo, _target, &_pathspecs));

	assert_content_in_index(&_pathspecs, true, NULL);
}