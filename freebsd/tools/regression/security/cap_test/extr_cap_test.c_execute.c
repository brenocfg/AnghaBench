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
struct test {char* t_name; int /*<<< orphan*/  (* t_run ) () ;} ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int FAILED ; 
 int PASSED ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  printf (char*,char*,int,char*) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

int
execute(int id, struct test *t) {
	int result;

	pid_t pid = fork();
	if (pid < 0)
		err(-1, "fork");
	if (pid) {
		/* Parent: wait for result from child. */
		int status;
		while (waitpid(pid, &status, 0) != pid) {}
		if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		else
			result = FAILED;
	} else {
		/* Child process: run the test. */
		exit(t->t_run());
	}

	printf("%s %d - %s\n",
		(result == PASSED) ? "ok" : "not ok",
		id, t->t_name);

	return (result);
}