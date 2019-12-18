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
typedef  int /*<<< orphan*/  sem_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_CREAT ; 
 int /*<<< orphan*/ * SEM_FAILED ; 
 int /*<<< orphan*/  SEM_NAME ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sem_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
test_named(void)
{
	sem_t *s, *s2;
	pid_t pid;
	int status;

	printf("testing named process-shared semaphore\n");
	sem_unlink(SEM_NAME);
	s = sem_open(SEM_NAME, O_CREAT, 0777, 0);
	if (s == SEM_FAILED)
		err(1, "sem_open failed");
	s2 = sem_open(SEM_NAME, O_CREAT, 0777, 0);
	if (s2 == SEM_FAILED)
		err(2, "second sem_open call failed");
	if (s != s2)
		errx(3,
"two sem_open calls for same semaphore do not return same address");
	if (sem_close(s2))
		err(4, "sem_close failed");
	if ((pid = fork()) == 0) {
		printf("child: sem_wait()\n");
		if (sem_wait(s))
			err(5, "sem_wait failed");
		printf("child: sem_wait() returned\n");
		exit(0);
	} else {
		sleep(1);
		printf("parent: sem_post()\n");
		if (sem_post(s))
			err(6, "sem_post failed");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			printf("OK.\n");
		else
			printf("Failure.");
	}

	if (sem_close(s))
		err(7, "sem_close failed");
	
	return (0);
}