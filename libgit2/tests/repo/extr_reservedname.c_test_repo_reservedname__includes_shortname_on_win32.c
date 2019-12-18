#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository__reserved_names (TYPE_1__**,size_t*,int /*<<< orphan*/ *,int) ; 

void test_repo_reservedname__includes_shortname_on_win32(void)
{
	git_repository *repo;
	git_buf *reserved;
	size_t reserved_len;

	repo = cl_git_sandbox_init("nasty");
	cl_assert(git_repository__reserved_names(&reserved, &reserved_len, repo, false));

#ifdef GIT_WIN32
	cl_assert_equal_i(2, reserved_len);
	cl_assert_equal_s(".git", reserved[0].ptr);
	cl_assert_equal_s("GIT~1", reserved[1].ptr);
#else
	cl_assert_equal_i(1, reserved_len);
	cl_assert_equal_s(".git", reserved[0].ptr);
#endif
}