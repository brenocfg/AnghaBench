#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_path_to_dir (TYPE_1__*) ; 

__attribute__((used)) static void
check_path_to_dir(
	const char* path,
    const char* expected)
{
	git_buf tgt = GIT_BUF_INIT;

	git_buf_sets(&tgt, path);
	cl_git_pass(git_path_to_dir(&tgt));
	cl_assert_equal_s(expected, tgt.ptr);

	git_buf_dispose(&tgt);
}