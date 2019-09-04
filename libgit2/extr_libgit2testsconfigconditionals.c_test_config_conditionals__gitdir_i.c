#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_condition_includes (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char*) ; 
 char* p_realpath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_config_conditionals__gitdir_i(void)
{
	git_buf path = GIT_BUF_INIT;
	char *sandbox_path;

	sandbox_path = p_realpath(clar_sandbox_path(), NULL);

	git_buf_joinpath(&path, sandbox_path, "empty_standard_repo");
	assert_condition_includes("gitdir/i", path.ptr, true);

	git_buf_joinpath(&path, sandbox_path, "EMPTY_STANDARD_REPO");
	assert_condition_includes("gitdir/i", path.ptr, true);

	git__free(sandbox_path);
	git_buf_dispose(&path);
}