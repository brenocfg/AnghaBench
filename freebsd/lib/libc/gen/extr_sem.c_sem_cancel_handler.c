#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sem_t ;
struct TYPE_2__ {scalar_t__ count; scalar_t__ nwaiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  _umtx_wake (scalar_t__*) ; 
 int /*<<< orphan*/  atomic_add_int (scalar_t__*,int) ; 

__attribute__((used)) static void
sem_cancel_handler(void *arg)
{
	sem_t *sem = arg;

	atomic_add_int(&(*sem)->nwaiters, -1);
	if ((*sem)->nwaiters && (*sem)->count)
		_umtx_wake(&(*sem)->count);
}