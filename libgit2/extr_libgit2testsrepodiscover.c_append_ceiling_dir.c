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
struct TYPE_8__ {scalar_t__ size; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 char GIT_PATH_LIST_SEPARATOR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_path_prettify_dir (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void append_ceiling_dir(git_buf *ceiling_dirs, const char *path)
{
	git_buf pretty_path = GIT_BUF_INIT;
	char ceiling_separator[2] = { GIT_PATH_LIST_SEPARATOR, '\0' };

	cl_git_pass(git_path_prettify_dir(&pretty_path, path, NULL));

	if (ceiling_dirs->size > 0)
		git_buf_puts(ceiling_dirs, ceiling_separator);

	git_buf_puts(ceiling_dirs, pretty_path.ptr);

	git_buf_dispose(&pretty_path);
	cl_assert(git_buf_oom(ceiling_dirs) == 0);
}