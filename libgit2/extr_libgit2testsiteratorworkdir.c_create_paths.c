#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

__attribute__((used)) static void create_paths(const char *root, int depth)
{
	git_buf fullpath = GIT_BUF_INIT;
	size_t root_len;
	int i;

	cl_git_pass(git_buf_puts(&fullpath, root));
	cl_git_pass(git_buf_putc(&fullpath, '/'));

	root_len = fullpath.size;

	for (i = 0; i < 8; i++) {
		bool file = (depth == 0 || (i % 2) == 0);
		git_buf_truncate(&fullpath, root_len);
		cl_git_pass(git_buf_printf(&fullpath, "item%d", i));

		if (file) {
			cl_git_rewritefile(fullpath.ptr, "This is a file!\n");
		} else {
			cl_must_pass(p_mkdir(fullpath.ptr, 0777));

			if (depth > 0)
				create_paths(fullpath.ptr, (depth - 1));
		}
	}

	git_buf_dispose(&fullpath);
}