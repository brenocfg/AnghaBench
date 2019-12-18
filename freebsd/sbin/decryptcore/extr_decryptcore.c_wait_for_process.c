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
 int /*<<< orphan*/  LOG_ERR ; 
 int WEXITED ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int WUNTRACED ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
wait_for_process(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, WUNTRACED | WEXITED) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to wait for a child process");
		return (1);
	}

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}