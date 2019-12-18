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
struct TYPE_5__ {int /*<<< orphan*/  _count; } ;
struct TYPE_6__ {TYPE_1__ _kern; } ;
typedef  TYPE_2__ sem_t ;

/* Variables and functions */
 scalar_t__ USEM_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ sem_check_validity (TYPE_2__*) ; 

int
_sem_getvalue(sem_t * __restrict sem, int * __restrict sval)
{

	if (sem_check_validity(sem) != 0)
		return (-1);

	*sval = (int)USEM_COUNT(sem->_kern._count);
	return (0);
}