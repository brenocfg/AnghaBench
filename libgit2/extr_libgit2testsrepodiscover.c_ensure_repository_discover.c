#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_path_to_dir (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_discover (TYPE_1__*,char const*,int,char const*) ; 
 int /*<<< orphan*/  p_realpath (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ensure_repository_discover(const char *start_path,
				       const char *ceiling_dirs,
				       const char *expected_path)
{
	git_buf found_path = GIT_BUF_INIT, resolved = GIT_BUF_INIT;

	git_buf_attach(&resolved, p_realpath(expected_path, NULL), 0);
	cl_assert(resolved.size > 0);
	cl_git_pass(git_path_to_dir(&resolved));
	cl_git_pass(git_repository_discover(&found_path, start_path, 1, ceiling_dirs));

	cl_assert_equal_s(found_path.ptr, resolved.ptr);

	git_buf_dispose(&resolved);
	git_buf_dispose(&found_path);
}