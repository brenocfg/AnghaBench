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
typedef  int time_t ;
struct stat {int st_atime; int st_mtime; } ;
struct p_timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int p_close (int) ; 
 int p_futimes (int,struct p_timeval*) ; 
 int p_open (char*,int /*<<< orphan*/ ) ; 
 int p_stat (char*,struct stat*) ; 
 int p_unlink (char*) ; 
 int p_utimes (char*,struct p_timeval*) ; 
 int time (int /*<<< orphan*/ *) ; 

void test_core_posix__utimes(void)
{
	struct p_timeval times[2];
	struct stat st;
	time_t curtime;
	int fd;

	/* test p_utimes */
	times[0].tv_sec = 1234567890;
	times[0].tv_usec = 0;
	times[1].tv_sec = 1234567890;
	times[1].tv_usec = 0;

	cl_git_mkfile("foo", "Dummy file.");
	cl_must_pass(p_utimes("foo", times));

	cl_must_pass(p_stat("foo", &st));
	cl_assert_equal_i(1234567890, st.st_atime);
	cl_assert_equal_i(1234567890, st.st_mtime);


	/* test p_futimes */
	times[0].tv_sec = 1414141414;
	times[0].tv_usec = 0;
	times[1].tv_sec = 1414141414;
	times[1].tv_usec = 0;

	cl_must_pass(fd = p_open("foo", O_RDWR));
	cl_must_pass(p_futimes(fd, times));
	cl_must_pass(p_close(fd));

	cl_must_pass(p_stat("foo", &st));
	cl_assert_equal_i(1414141414, st.st_atime);
	cl_assert_equal_i(1414141414, st.st_mtime);


	/* test p_utimes with current time, assume that
	 * it takes < 5 seconds to get the time...!
	 */
	cl_must_pass(p_utimes("foo", NULL));

	curtime = time(NULL);
	cl_must_pass(p_stat("foo", &st));
	cl_assert((st.st_atime - curtime) < 5);
	cl_assert((st.st_mtime - curtime) < 5);

	cl_must_pass(p_unlink("foo"));
}