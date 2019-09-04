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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 char* clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_set (TYPE_1__*,char const*,int) ; 
 int git_path_root (char const*) ; 
 int /*<<< orphan*/  p_stat (int /*<<< orphan*/ ,struct stat*) ; 

void test_core_stat__root(void)
{
	const char *sandbox = clar_sandbox_path();
	git_buf root = GIT_BUF_INIT;
	int root_len;
	struct stat st;

	root_len = git_path_root(sandbox);
	cl_assert(root_len >= 0);

	git_buf_set(&root, sandbox, root_len+1);

	cl_must_pass(p_stat(root.ptr, &st));
	cl_assert(S_ISDIR(st.st_mode));

	git_buf_dispose(&root);
}