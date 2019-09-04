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
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_write2file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_1__*,char*,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_rename (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rand () ; 

__attribute__((used)) static void replace_file_with_mode(
	const char *filename, const char *backup, unsigned int create_mode)
{
	git_buf path = GIT_BUF_INIT, content = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&path, "filemodes", filename));
	cl_git_pass(git_buf_printf(&content, "%s as %08u (%d)",
		filename, create_mode, rand()));

	cl_git_pass(p_rename(path.ptr, backup));
	cl_git_write2file(
		path.ptr, content.ptr, content.size,
		O_WRONLY|O_CREAT|O_TRUNC, create_mode);

	git_buf_dispose(&path);
	git_buf_dispose(&content);
}