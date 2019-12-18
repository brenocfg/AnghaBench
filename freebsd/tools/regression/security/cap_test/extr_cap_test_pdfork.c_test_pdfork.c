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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_birthtime; scalar_t__ st_atime; scalar_t__ st_ctime; scalar_t__ st_mtime; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  FAIL (char*) ; 
 int FAILED ; 
 int /*<<< orphan*/  FAILX (char*) ; 
 int PASSED ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 scalar_t__ pdfork (int*,int /*<<< orphan*/ ) ; 
 int pdgetpid (int,scalar_t__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
test_pdfork(void)
{
	struct stat stat;
	int success = PASSED;
	int pd, error;
	pid_t pid;
	time_t now;

	//cap_enter();

	pid = pdfork(&pd, 0);
	if (pid < 0)
		err(-1, "pdfork");

	else if (pid == 0) {
		/*
		 * Child process.
		 *
		 * pd should not be a valid process descriptor.
		 */
		error = pdgetpid(pd, &pid);
		if (error != -1)
			FAILX("pdgetpid succeeded");
		else if (errno != EBADF)
			FAIL("pdgetpid failed, but errno != EBADF");

		exit(success);
	}

	/* Parent process. Ensure that [acm]times have been set correctly. */
	REQUIRE(fstat(pd, &stat));

	now = time(NULL);
	CHECK(now != (time_t)-1);

	CHECK(now >= stat.st_birthtime);
	CHECK((now - stat.st_birthtime) < 2);
	CHECK(stat.st_birthtime == stat.st_atime);
	CHECK(stat.st_atime == stat.st_ctime);
	CHECK(stat.st_ctime == stat.st_mtime);

	/* Wait for the child to finish. */
	error = pdgetpid(pd, &pid);
	CHECK(error == 0);
	CHECK(pid > 0);

	int status;
	while (waitpid(pid, &status, 0) != pid) {}
	if ((success == PASSED) && WIFEXITED(status))
		success = WEXITSTATUS(status);
	else
		success = FAILED;

	return (success);
}