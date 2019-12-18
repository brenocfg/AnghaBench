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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (char*) ; 
 int FAILED ; 
 int PASSED ; 
 int /*<<< orphan*/  SIGINT ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  handle_signal ; 
 int pdfork (int*,int /*<<< orphan*/ ) ; 
 int pdgetpid (int,scalar_t__*) ; 
 int pdkill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
test_pdkill(void)
{
	int success = PASSED;
	int pd, error;
	pid_t pid;

	//cap_enter();

	error = pdfork(&pd, 0);
	if (error < 0)
		err(-1, "pdfork");

	else if (error == 0) {
		signal(SIGINT, handle_signal);
		sleep(3600);
		exit(FAILED);
	}

	/* Parent process; find the child's PID (we'll need it later). */
	error = pdgetpid(pd, &pid);
	if (error != 0)
		FAIL("pdgetpid");

	/* Kill the child! */
	usleep(100);
	error = pdkill(pd, SIGINT);
	if (error != 0)
		FAIL("pdkill");

	/* Make sure the child finished properly. */
	int status;
	while (waitpid(pid, &status, 0) != pid) {}
	if ((success == PASSED) && WIFEXITED(status))
		success = WEXITSTATUS(status);
	else
		success = FAILED;

	return (success);
}