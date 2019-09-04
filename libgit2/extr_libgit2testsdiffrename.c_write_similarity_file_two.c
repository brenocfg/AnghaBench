#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  git_futils_writebuffer (int /*<<< orphan*/ *,char const*,int,int) ; 

__attribute__((used)) static void write_similarity_file_two(const char *filename, size_t b_lines)
{
	git_buf contents = GIT_BUF_INIT;
	size_t i;

	for (i = 0; i < b_lines; i++)
		git_buf_printf(&contents, "%02d - bbbbb\r\n", (int)(i+1));

	for (i = b_lines; i < 50; i++)
		git_buf_printf(&contents, "%02d - aaaaa%s", (int)(i+1), (i == 49 ? "" : "\r\n"));

	cl_git_pass(
		git_futils_writebuffer(&contents, filename, O_RDWR|O_CREAT, 0777));

	git_buf_dispose(&contents);
}