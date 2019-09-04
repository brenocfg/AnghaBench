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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_file (char*,int,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_filebuf__2(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	char test[] = "test";
	unsigned char buf[4096 * 4]; /* 2 * WRITE_BUFFER_SIZE */

	memset(buf, 0xfe, sizeof(buf));

	cl_git_pass(git_filebuf_open(&file, test, 0, 0666));
	cl_git_pass(git_filebuf_write(&file, buf, sizeof(buf)));
	cl_git_pass(git_filebuf_commit(&file));

	cl_assert_equal_file((char *)buf, sizeof(buf), test);

	cl_must_pass(p_unlink(test));
}