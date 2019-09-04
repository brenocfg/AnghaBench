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
struct TYPE_4__ {size_t count; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/ * TEST_URL ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 size_t count_config_entries_match (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_create_detached (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_get_fetch_refspecs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_url (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_remote_create__detached(void)
{
	git_remote *remote;
	git_strarray array;

	size_t section_count = count_config_entries_match(_repo, "remote\\.");

	cl_git_pass(git_remote_create_detached(&remote, TEST_URL));
	cl_assert_equal_s(git_remote_name(remote), NULL);
	cl_assert_equal_s(git_remote_url(remote), TEST_URL);
	cl_assert_equal_p(git_remote_owner(remote), NULL);

	cl_git_pass(git_remote_get_fetch_refspecs(&array, remote));
	cl_assert_equal_i(0, array.count);
	cl_assert_equal_i(section_count, count_config_entries_match(_repo, "remote\\."));

	git_strarray_free(&array);
	git_remote_free(remote);
}