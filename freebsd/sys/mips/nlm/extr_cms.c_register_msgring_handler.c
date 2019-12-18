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
typedef  int /*<<< orphan*/ * msgring_handler ;
struct TYPE_2__ {void* arg; int /*<<< orphan*/ * action; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MSGRNG_NSTATIONS ; 
 scalar_t__ bootverbose ; 
 TYPE_1__* msgmap ; 
 int /*<<< orphan*/  msgmap_lock ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ *,void*) ; 

int
register_msgring_handler(int startb, int endb, msgring_handler action,
    void *arg)
{
	int	i;

	if (bootverbose)
		printf("Register handler %d-%d %p(%p)\n",
		    startb, endb, action, arg);
	KASSERT(startb >= 0 && startb <= endb && endb < MSGRNG_NSTATIONS,
	    ("Invalid value for bucket range %d,%d", startb, endb));

	mtx_lock_spin(&msgmap_lock);
	for (i = startb; i <= endb; i++) {
		KASSERT(msgmap[i].action == NULL,
		   ("Bucket %d already used [action %p]", i, msgmap[i].action));
		msgmap[i].action = action;
		msgmap[i].arg = arg;
	}
	mtx_unlock_spin(&msgmap_lock);
	return (0);
}