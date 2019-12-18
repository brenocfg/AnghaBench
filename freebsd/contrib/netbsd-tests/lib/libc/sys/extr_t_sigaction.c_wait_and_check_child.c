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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*,int) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/  const,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wait_and_check_child(const pid_t pid, const char *fail_message)
{
	int status;

	(void)waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		ATF_CHECK_EQ(EXIT_SUCCESS, WEXITSTATUS(status));
	else
		atf_tc_fail("%s; raw exit status was %d", fail_message, status);
}