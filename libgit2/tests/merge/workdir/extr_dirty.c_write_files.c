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
 int /*<<< orphan*/  TEST_REPO_PATH ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char*,...) ; 

__attribute__((used)) static void write_files(char *files[])
{
	char *filename;
	git_buf path = GIT_BUF_INIT, content = GIT_BUF_INIT;
	size_t i;

	for (i = 0, filename = files[i]; filename; filename = files[++i]) {
		git_buf_clear(&path);
		git_buf_clear(&content);

		git_buf_printf(&path, "%s/%s", TEST_REPO_PATH, filename);
		git_buf_printf(&content, "This is a dirty file in the working directory!\n\n"
			"It will not be staged!  Its filename is %s.\n", filename);

		cl_git_mkfile(path.ptr, content.ptr);
	}

	git_buf_dispose(&path);
	git_buf_dispose(&content);
}