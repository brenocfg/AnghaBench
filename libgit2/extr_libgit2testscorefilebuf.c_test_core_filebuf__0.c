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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int p_close (int) ; 
 int p_creat (char*,int) ; 
 int p_unlink (char*) ; 

void test_core_filebuf__0(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	int fd;
	char test[] = "test", testlock[] = "test.lock";

	fd = p_creat(testlock, 0744); /* -V536 */

	cl_must_pass(fd);
	cl_must_pass(p_close(fd));

	cl_git_fail(git_filebuf_open(&file, test, 0, 0666));
	cl_assert(git_path_exists(testlock));

	cl_must_pass(p_unlink(testlock));
}