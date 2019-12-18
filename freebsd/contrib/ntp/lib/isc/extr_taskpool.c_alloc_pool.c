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
struct TYPE_4__ {unsigned int ntasks; unsigned int quantum; int /*<<< orphan*/ ** tasks; int /*<<< orphan*/ * tmgr; int /*<<< orphan*/ * mctx; } ;
typedef  TYPE_1__ isc_taskpool_t ;
typedef  int /*<<< orphan*/  isc_taskmgr_t ;
typedef  int /*<<< orphan*/  isc_task_t ;
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 void* isc_mem_get (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static isc_result_t
alloc_pool(isc_taskmgr_t *tmgr, isc_mem_t *mctx, unsigned int ntasks,
	   unsigned int quantum, isc_taskpool_t **poolp)
{
	isc_taskpool_t *pool;
	unsigned int i;

	pool = isc_mem_get(mctx, sizeof(*pool));
	if (pool == NULL)
		return (ISC_R_NOMEMORY);
	pool->mctx = mctx;
	pool->ntasks = ntasks;
	pool->quantum = quantum;
	pool->tmgr = tmgr;
	pool->tasks = isc_mem_get(mctx, ntasks * sizeof(isc_task_t *));
	if (pool->tasks == NULL) {
		isc_mem_put(mctx, pool, sizeof(*pool));
		return (ISC_R_NOMEMORY);
	}
	for (i = 0; i < ntasks; i++)
		pool->tasks[i] = NULL;

	*poolp = pool;
	return (ISC_R_SUCCESS);
}