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
struct TYPE_5__ {int /*<<< orphan*/ * tasks; } ;
typedef  TYPE_1__ isc_taskpool_t ;
typedef  int /*<<< orphan*/  isc_taskmgr_t ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ alloc_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,TYPE_1__**) ; 
 scalar_t__ isc_task_create (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_task_setname (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_taskpool_destroy (TYPE_1__**) ; 

isc_result_t
isc_taskpool_create(isc_taskmgr_t *tmgr, isc_mem_t *mctx,
		    unsigned int ntasks, unsigned int quantum,
		    isc_taskpool_t **poolp)
{
	unsigned int i;
	isc_taskpool_t *pool = NULL;
	isc_result_t result;

	INSIST(ntasks > 0);

	/* Allocate the pool structure */
	result = alloc_pool(tmgr, mctx, ntasks, quantum, &pool);
	if (result != ISC_R_SUCCESS)
		return (result);

	/* Create the tasks */
	for (i = 0; i < ntasks; i++) {
		result = isc_task_create(tmgr, quantum, &pool->tasks[i]);
		if (result != ISC_R_SUCCESS) {
			isc_taskpool_destroy(&pool);
			return (result);
		}
		isc_task_setname(pool->tasks[i], "taskpool", NULL);
	}

	*poolp = pool;
	return (ISC_R_SUCCESS);
}