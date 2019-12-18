#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
struct TYPE_5__ {scalar_t__ syssem; scalar_t__ nwaiters; scalar_t__ magic; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  errno ; 
 int ksem_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 
 int /*<<< orphan*/  sem_free (TYPE_1__*) ; 

int
_libc_sem_destroy_compat(sem_t *sem)
{
	int retval;

	if (sem_check_validity(sem) != 0)
		return (-1);

	/*
	 * If this is a system semaphore let the kernel track it otherwise
	 * make sure there are no waiters.
	 */
	if ((*sem)->syssem != 0)
		retval = ksem_destroy((*sem)->semid);
	else if ((*sem)->nwaiters > 0) {
		errno = EBUSY;
		retval = -1;
	}
	else {
		retval = 0;
		(*sem)->magic = 0;
	}

	if (retval == 0)
		sem_free(*sem);
	return (retval);
}