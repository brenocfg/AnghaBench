#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
struct TYPE_7__ {scalar_t__ syssem; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 scalar_t__ ksem_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  named_sems_mtx ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 
 int /*<<< orphan*/  sem_free (TYPE_1__*) ; 

int
_libc_sem_close_compat(sem_t *sem)
{

	if (sem_check_validity(sem) != 0)
		return (-1);

	if ((*sem)->syssem == 0) {
		errno = EINVAL;
		return (-1);
	}

	_pthread_mutex_lock(&named_sems_mtx);
	if (ksem_close((*sem)->semid) != 0) {
		_pthread_mutex_unlock(&named_sems_mtx);
		return (-1);
	}
	LIST_REMOVE((*sem), entry);
	_pthread_mutex_unlock(&named_sems_mtx);
	sem_free(*sem);
	*sem = NULL;
	free(sem);
	return (0);
}