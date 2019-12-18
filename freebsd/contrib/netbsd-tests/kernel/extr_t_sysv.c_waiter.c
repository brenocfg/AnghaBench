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
struct sembuf {int sem_op; void* sem_flg; scalar_t__ sem_num; } ;

/* Variables and functions */
 void* SEM_UNDO ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int semget (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semkey ; 
 int semop (int,struct sembuf*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

void
waiter(void)
{
	struct sembuf s;
	int semid;

	if ((semid = semget(semkey, 1, 0)) == -1)
		err(1, "waiter: semget");

	/*
	 * Attempt to acquire the semaphore.
	 */
	s.sem_num = 0;
	s.sem_op = -1;
	s.sem_flg = SEM_UNDO;

	if (semop(semid, &s, 1) == -1)
		err(1, "waiter: semop -1");

	printf("WOO!  GOT THE SEMAPHORE!\n");
	sleep(1);

	/*
	 * Release the semaphore and exit.
	 */
	s.sem_num = 0;
	s.sem_op = 1;
	s.sem_flg = SEM_UNDO;

	if (semop(semid, &s, 1) == -1)
		err(1, "waiter: semop +1");

	exit(0);
}