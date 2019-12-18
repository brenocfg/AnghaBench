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
struct TYPE_5__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  git_buf_attach (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 char* p_realpath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *sandbox_path(git_buf *buf, const char *suffix)
{
	char *path = p_realpath(clar_sandbox_path(), NULL);
	cl_assert(path);
	cl_git_pass(git_buf_attach(buf, path, 0));
	cl_git_pass(git_buf_joinpath(buf, buf->ptr, suffix));
	return buf->ptr;
}