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

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int /*<<< orphan*/ * SEM_FAILED ; 
 int /*<<< orphan*/  SEM_NAME ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sem_open (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  sem_unlink (int /*<<< orphan*/ ) ; 

int
test_named2(void)
{
	sem_t *s, *s2, *s3;

	printf("testing named process-shared semaphore, O_EXCL cases\n");
	sem_unlink(SEM_NAME);
	s = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0777, 0);
	if (s == SEM_FAILED)
		err(1, "sem_open failed");
	s2 = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0777, 0);
	if (s2 != SEM_FAILED)
		errx(2, "second sem_open call wrongly succeeded");
	if (errno != EEXIST)
		err(3, "second sem_open call failed with wrong errno");

	s3 = sem_open(SEM_NAME, 0);
	if (s3 == SEM_FAILED)
		err(4, "third sem_open call failed");
	if (s != s3)
		errx(5,
"two sem_open calls for same semaphore do not return same address");
	if (sem_close(s3))
		err(6, "sem_close failed");

	if (sem_close(s))
		err(7, "sem_close failed");
	
	printf("OK.\n");
	return (0);
}