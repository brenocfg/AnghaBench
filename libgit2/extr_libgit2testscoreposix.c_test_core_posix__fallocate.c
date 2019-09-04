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
struct stat {int st_size; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_fallocate (int,int,int) ; 
 int p_fstat (int,struct stat*) ; 
 int p_lseek (int,int,int /*<<< orphan*/ ) ; 
 int p_open (char*,int,int) ; 

void test_core_posix__fallocate(void)
{
	int fd;
	struct stat st;

	/* fallocate a new file succeeds */
	cl_must_pass(fd = p_open("fallocate_test", O_RDWR|O_CREAT, 0666));
	cl_must_pass(p_fallocate(fd, 0, 42));
	cl_must_pass(p_fstat(fd, &st));
	cl_assert_equal_i(42, st.st_size);
	p_close(fd);

	/* fallocate an existing file succeeds */
	cl_must_pass(fd = p_open("fallocate_test", O_RDWR, 0666));
	cl_must_pass(p_fallocate(fd, 90, 9));
	cl_must_pass(p_fstat(fd, &st));
	cl_assert_equal_i(99, st.st_size);
	p_close(fd);

	/* fallocate doesn't shrink */
	cl_must_pass(fd = p_open("fallocate_test", O_RDWR, 0666));
	cl_must_pass(p_fallocate(fd, 0, 14));
	cl_must_pass(p_fstat(fd, &st));
	cl_assert_equal_i(99, st.st_size);
	p_close(fd);

	/* fallocate doesn't move the cursor */
	cl_must_pass(fd = p_open("fallocate_test", O_RDWR, 0666));
	cl_must_pass(p_fallocate(fd, 0, 100));
	cl_assert_equal_i(0, p_lseek(fd, 0, SEEK_CUR));
	cl_must_pass(p_lseek(fd, 42, SEEK_SET));
	cl_must_pass(p_fallocate(fd, 0, 200));
	cl_assert_equal_i(42, p_lseek(fd, 0, SEEK_CUR));
	p_close(fd);
}