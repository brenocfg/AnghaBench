#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int _count; } ;
struct TYPE_5__ {TYPE_2__ _kern; } ;
typedef  TYPE_1__ sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ SEM_VALUE_MAX ; 
 scalar_t__ USEM_COUNT (unsigned int) ; 
 unsigned int USEM_HAS_WAITERS ; 
 int /*<<< orphan*/  atomic_cmpset_rel_int (unsigned int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sem_check_validity (TYPE_1__*) ; 
 int /*<<< orphan*/  usem_wake (TYPE_2__*) ; 

int
_sem_post(sem_t *sem)
{
	unsigned int count;

	if (sem_check_validity(sem) != 0)
		return (-1);

	do {
		count = sem->_kern._count;
		if (USEM_COUNT(count) + 1 > SEM_VALUE_MAX) {
			errno = EOVERFLOW;
			return (-1);
		}
	} while (!atomic_cmpset_rel_int(&sem->_kern._count, count, count + 1));
	if (count & USEM_HAS_WAITERS)
		usem_wake(&sem->_kern);
	return (0);
}