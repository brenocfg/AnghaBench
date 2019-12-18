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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ FSTYPE_SYSVBFS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 int /*<<< orphan*/  func1 ; 
 int /*<<< orphan*/  func2 ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rump_sys_chdir (char const*) ; 
 int rump_sys_fchdir (int) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void
race(const atf_tc_t *tc, const char *path)
{
	int res, fd, quit;
	pthread_t th1, th2;

	if (FSTYPE_SYSVBFS(tc))
		atf_tc_skip("directories not supported by file system");

	fd = rump_sys_open(".", O_RDONLY, 0666);
	if (fd == -1)
		atf_tc_fail("open failed");
	res = rump_sys_chdir(path);
	if (res == -1)
		atf_tc_fail("chdir failed");

	quit = 0;

	res = pthread_create(&th1, NULL, func1, &quit);
	if (res != 0)
		atf_tc_fail("pthread_create1 failed");
	res = pthread_create(&th2, NULL, func2, &quit);
	if (res != 0)
		atf_tc_fail("pthread_create2 failed");

	sleep(10);

	quit = 1;

	res = pthread_join(th2, NULL);
	if (res != 0)
		atf_tc_fail("pthread_join2 failed");
	res = pthread_join(th1, NULL);
	if (res != 0)
		atf_tc_fail("pthread_join1 failed");

	res = rump_sys_fchdir(fd);
	if (res == -1)
		atf_tc_fail("fchdir failed");
}