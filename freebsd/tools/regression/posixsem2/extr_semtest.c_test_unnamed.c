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
 int MAP_ANON ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
test_unnamed(void)
{
	sem_t *s;
	pid_t pid;
	int status;

	printf("testing unnamed process-shared semaphore\n");
	s = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED,
		-1, 0);
	if (s == MAP_FAILED)
		err(1, "mmap failed");
	if (sem_init(s, 1, 0))
		err(2, "sem_init failed");
	if ((pid = fork()) == 0) {
		printf("child: sem_wait()\n");
		if (sem_wait(s))
			err(3, "sem_wait failed");
		printf("child: sem_wait() returned\n");
		exit(0);
	} else {
		sleep(1);
		printf("parent: sem_post()\n");
		if (sem_post(s))
			err(4, "sem_post failed");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			printf("OK.\n");
		else
			printf("Failure.");
	}
	return (0);
}