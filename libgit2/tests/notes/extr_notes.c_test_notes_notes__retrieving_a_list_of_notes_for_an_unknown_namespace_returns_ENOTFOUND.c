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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int git_note_foreach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  note_list_cb ; 

void test_notes_notes__retrieving_a_list_of_notes_for_an_unknown_namespace_returns_ENOTFOUND(void)
{
	int error;
	unsigned int retrieved_notes = 0;

	error = git_note_foreach(_repo, "refs/notes/i-am-not", note_list_cb, &retrieved_notes);
	cl_git_fail(error);
	cl_assert_equal_i(GIT_ENOTFOUND, error);

	cl_assert_equal_i(0, retrieved_notes);
}