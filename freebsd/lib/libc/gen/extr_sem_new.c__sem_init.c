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
typedef  scalar_t__ u_int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  _flags; scalar_t__ _count; } ;
struct TYPE_6__ {TYPE_1__ _kern; int /*<<< orphan*/  _magic; } ;
typedef  TYPE_2__ sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SEM_MAGIC ; 
 unsigned int SEM_VALUE_MAX ; 
 int /*<<< orphan*/  USYNC_PROCESS_SHARED ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  errno ; 

int
_sem_init(sem_t *sem, int pshared, unsigned int value)
{

	if (value > SEM_VALUE_MAX) {
		errno = EINVAL;
		return (-1);
	}
 
	bzero(sem, sizeof(sem_t));
	sem->_magic = SEM_MAGIC;
	sem->_kern._count = (u_int32_t)value;
	sem->_kern._flags = pshared ? USYNC_PROCESS_SHARED : 0;
	return (0);
}