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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 scalar_t__ EXIT_SUCCESS ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int fork () ; 
 int in_child ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_child(void (*child)(const char *), const char *cookie)
{
	pid_t pid;

	pid = fork();
	ATF_REQUIRE(pid != -1);
	if (pid == 0) {
		in_child = true;
		child(cookie);
		assert(false);
		/* UNREACHABLE */
	} else {
		int status;

		ATF_REQUIRE(waitpid(pid, &status, 0) != -1);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != EXIT_SUCCESS)
			atf_tc_fail("See stderr for details");
	}
}