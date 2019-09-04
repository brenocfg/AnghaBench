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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool test_file_contents(const char *filename, const char *expected)
{
	git_buf file_path_buf = GIT_BUF_INIT, file_buf = GIT_BUF_INIT;
	bool equals;
	
	git_buf_printf(&file_path_buf, "%s/%s", git_repository_path(repo), filename);
	
	cl_git_pass(git_futils_readbuffer(&file_buf, file_path_buf.ptr));
	equals = (strcmp(file_buf.ptr, expected) == 0);

	git_buf_dispose(&file_path_buf);
	git_buf_dispose(&file_buf);
	
	return equals;
}