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
struct TYPE_4__ {scalar_t__ syssem; int /*<<< orphan*/  count; scalar_t__ nwaiters; int /*<<< orphan*/  semid; } ;

/* Variables and functions */
 int _umtx_wake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_rel_int (int /*<<< orphan*/ *,int) ; 
 int ksem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 
 scalar_t__ sem_check_validity (TYPE_1__**) ; 

int
_libc_sem_post_compat(sem_t *sem)
{

	if (sem_check_validity(sem) != 0)
		return (-1);

	if ((*sem)->syssem != 0)
		return ksem_post((*sem)->semid);

	atomic_add_rel_int(&(*sem)->count, 1);
	rmb();
	if ((*sem)->nwaiters)
		return _umtx_wake(&(*sem)->count);
	return (0);
}