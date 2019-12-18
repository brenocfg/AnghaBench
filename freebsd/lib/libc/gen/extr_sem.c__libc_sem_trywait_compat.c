#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
struct TYPE_4__ {scalar_t__ syssem; int count; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ atomic_cmpset_acq_int (int*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int ksem_trywait (int /*<<< orphan*/ ) ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 

int
_libc_sem_trywait_compat(sem_t *sem)
{
	int val;

	if (sem_check_validity(sem) != 0)
		return (-1);

	if ((*sem)->syssem != 0)
 		return ksem_trywait((*sem)->semid);

	while ((val = (*sem)->count) > 0) {
		if (atomic_cmpset_acq_int(&(*sem)->count, val, val - 1))
			return (0);
	}
	errno = EAGAIN;
	return (-1);
}