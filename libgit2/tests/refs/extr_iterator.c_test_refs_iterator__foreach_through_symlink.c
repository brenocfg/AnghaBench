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
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert_all_refnames_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_reference_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_symlink (char*,char*) ; 
 int /*<<< orphan*/  refcmp_cb ; 
 int /*<<< orphan*/  refnames_with_symlink ; 
 int /*<<< orphan*/  refs_foreach_cb ; 
 int /*<<< orphan*/  repo ; 

void test_refs_iterator__foreach_through_symlink(void)
{
	git_vector output;

#ifdef GIT_WIN32
	cl_skip();
#endif

	cl_git_pass(git_vector_init(&output, 32, &refcmp_cb));

	cl_git_pass(p_mkdir("refs", 0777));
	cl_git_mkfile("refs/a", "1234567890123456789012345678901234567890");
	cl_git_mkfile("refs/b", "1234567890123456789012345678901234567890");
	cl_git_mkfile("refs/c", "1234567890123456789012345678901234567890");
	cl_git_mkfile("refs/d", "1234567890123456789012345678901234567890");

	cl_git_pass(p_symlink("../../../refs", "testrepo.git/refs/heads/link"));

	cl_git_pass(git_reference_foreach(repo, refs_foreach_cb, &output));
	assert_all_refnames_match(refnames_with_symlink, &output);
}