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
typedef  scalar_t__ semid_t ;
typedef  int /*<<< orphan*/ * sem_t ;

/* Variables and functions */
 scalar_t__ SEM_USER ; 
 int /*<<< orphan*/  ksem_destroy (scalar_t__) ; 
 scalar_t__ ksem_init (scalar_t__*,unsigned int) ; 
 int /*<<< orphan*/ * sem_alloc (unsigned int,scalar_t__,int) ; 

int
_libc_sem_init_compat(sem_t *sem, int pshared, unsigned int value)
{
	semid_t semid;

	/*
	 * We always have to create the kernel semaphore if the
	 * threads library isn't present since libc's version of
	 * pthread_cond_wait() is just a stub that doesn't really
	 * wait.
	 */
	semid = (semid_t)SEM_USER;
	if ((pshared != 0) && ksem_init(&semid, value) != 0)
		return (-1);

	*sem = sem_alloc(value, semid, pshared);
	if ((*sem) == NULL) {
		if (pshared != 0)
			ksem_destroy(semid);
		return (-1);
	}
	return (0);
}