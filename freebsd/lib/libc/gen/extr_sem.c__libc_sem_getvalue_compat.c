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
struct TYPE_4__ {scalar_t__ syssem; scalar_t__ count; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int ksem_getvalue (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 

int
_libc_sem_getvalue_compat(sem_t * __restrict sem, int * __restrict sval)
{
	int retval;

	if (sem_check_validity(sem) != 0)
		return (-1);

	if ((*sem)->syssem != 0)
		retval = ksem_getvalue((*sem)->semid, sval);
	else {
		*sval = (int)(*sem)->count;
		retval = 0;
	}
	return (retval);
}