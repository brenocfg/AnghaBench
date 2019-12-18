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
struct TYPE_4__ {int /*<<< orphan*/  entry_count; } ;
typedef  TYPE_1__ status_entry_counts ;

/* Variables and functions */
 int /*<<< orphan*/  cb_status__match ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_files ; 
 int /*<<< orphan*/  expected_status ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  setup_fixture_submodules () ; 
 int /*<<< orphan*/  status_counts_init (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_status_submodules__1(void)
{
	status_entry_counts counts;

	g_repo = setup_fixture_submodules();

	cl_assert(git_path_isdir("submodules/.git"));
	cl_assert(git_path_isdir("submodules/testrepo/.git"));
	cl_assert(git_path_isfile("submodules/.gitmodules"));

	status_counts_init(counts, expected_files, expected_status);

	cl_git_pass( git_status_foreach(g_repo, cb_status__match, &counts) );

	cl_assert_equal_i(6, counts.entry_count);
}