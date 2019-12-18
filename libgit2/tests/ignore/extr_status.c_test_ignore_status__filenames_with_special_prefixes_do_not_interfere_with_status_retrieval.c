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
struct TYPE_4__ {int count; scalar_t__ status; } ;
typedef  TYPE_1__ status_entry_single ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 scalar_t__ GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cb_status__single ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_status_file (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_status_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_ignore_status__filenames_with_special_prefixes_do_not_interfere_with_status_retrieval(void)
{
	status_entry_single st;
	char *test_cases[] = {
		"!file",
		"#blah",
		"[blah]",
		"[attr]",
		"[attr]blah",
		NULL
	};
	int i;

	for (i = 0; *(test_cases + i) != NULL; i++) {
		git_buf file = GIT_BUF_INIT;
		char *file_name = *(test_cases + i);
		git_repository *repo = cl_git_sandbox_init("empty_standard_repo");

		cl_git_pass(git_buf_joinpath(&file, "empty_standard_repo", file_name));
		cl_git_mkfile(git_buf_cstr(&file), "Please don't ignore me!");

		memset(&st, 0, sizeof(st));
		cl_git_pass(git_status_foreach(repo, cb_status__single, &st));
		cl_assert(st.count == 1);
		cl_assert(st.status == GIT_STATUS_WT_NEW);

		cl_git_pass(git_status_file(&st.status, repo, file_name));
		cl_assert(st.status == GIT_STATUS_WT_NEW);

		cl_git_sandbox_cleanup();
		git_buf_dispose(&file);
	}
}