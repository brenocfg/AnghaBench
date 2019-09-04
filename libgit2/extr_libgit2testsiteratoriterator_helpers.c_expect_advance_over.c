#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_iterator_status_t ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_iterator_advance_over (TYPE_1__ const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_current (TYPE_1__ const**,int /*<<< orphan*/ *) ; 

void expect_advance_over(
	git_iterator *i,
	const char *expected_path,
	git_iterator_status_t expected_status)
{
	const git_index_entry *entry;
	git_iterator_status_t status;
	int error;

	cl_git_pass(git_iterator_current(&entry, i));
	cl_assert_equal_s(expected_path, entry->path);

	error = git_iterator_advance_over(&entry, &status, i);
	cl_assert(!error || error == GIT_ITEROVER);
	cl_assert_equal_i(expected_status, status);
}