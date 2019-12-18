#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  assert_note_equal (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_note (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_default_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_note_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_notes_notes__inserting_a_note_without_passing_a_namespace_uses_the_default_namespace(void)
{
	git_oid note_oid, target_oid;
	git_note *note, *default_namespace_note;
	git_buf default_ref = GIT_BUF_INIT;

	cl_git_pass(git_oid_fromstr(&target_oid, "08b041783f40edfe12bb406c9c9a8a040177c125"));
	cl_git_pass(git_note_default_ref(&default_ref, _repo));

	create_note(&note_oid, NULL, "08b041783f40edfe12bb406c9c9a8a040177c125", "hello world\n");

	cl_git_pass(git_note_read(&note, _repo, NULL, &target_oid));
	cl_git_pass(git_note_read(&default_namespace_note, _repo, git_buf_cstr(&default_ref), &target_oid));

	assert_note_equal(note, "hello world\n", &note_oid);
	assert_note_equal(default_namespace_note, "hello world\n", &note_oid);

	git_buf_dispose(&default_ref);
	git_note_free(note);
	git_note_free(default_namespace_note);
}