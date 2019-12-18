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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  repo ; 

void test_win32_forbidden__cannot_add_forbidden_filename_from_filesystem(void)
{
	git_index *index;

	/* since our function calls are very low-level, we can create `aux.`,
	 * but we should not be able to add it to the index
	 */
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_write2file("win32-forbidden/aux.", "foo\n", 4, O_RDWR | O_CREAT, 0666);

#ifdef GIT_WIN32
	cl_git_fail(git_index_add_bypath(index, "aux."));
#else
	cl_git_pass(git_index_add_bypath(index, "aux."));
#endif

	cl_must_pass(p_unlink("win32-forbidden/aux."));
	git_index_free(index);
}