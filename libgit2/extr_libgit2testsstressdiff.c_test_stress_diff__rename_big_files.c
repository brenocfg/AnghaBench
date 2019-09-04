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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_with_many (int) ; 

void test_stress_diff__rename_big_files(void)
{
	git_index *index;
	char tmp[64];
	int i, j;
	git_buf b = GIT_BUF_INIT;

	g_repo = cl_git_sandbox_init("renames");

	cl_git_pass(git_repository_index(&index, g_repo));

	for (i = 0; i < 100; i += 1) {
		p_snprintf(tmp, sizeof(tmp), "renames/newfile%03d", i);
		for (j = i * 256; j > 0; --j)
			git_buf_printf(&b, "more content %d\n", i);
		cl_git_mkfile(tmp, b.ptr);
	}

	for (i = 0; i < 100; i += 1) {
		p_snprintf(tmp, sizeof(tmp), "renames/newfile%03d", i);
		cl_git_pass(git_index_add_bypath(index, tmp + strlen("renames/")));
	}

	git_buf_dispose(&b);
	git_index_free(index);

	test_with_many(100);
}