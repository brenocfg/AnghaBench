#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_7__ {scalar_t__ ftpc_pid; scalar_t__ ftpc_acount; scalar_t__ ftpc_rcount; struct TYPE_7__* ftpc_next; int /*<<< orphan*/  ftpc_mtx; } ;
typedef  TYPE_1__ fasttrap_proc_t ;
struct TYPE_8__ {int /*<<< orphan*/  ftb_mtx; TYPE_1__* ftb_data; } ;
typedef  TYPE_2__ fasttrap_bucket_t ;
struct TYPE_9__ {TYPE_2__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t FASTTRAP_PROCS_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  atomic_inc_64 (scalar_t__*) ; 
 TYPE_5__ fasttrap_procs ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fasttrap_proc_t *
fasttrap_proc_lookup(pid_t pid)
{
	fasttrap_bucket_t *bucket;
	fasttrap_proc_t *fprc, *new_fprc;


	bucket = &fasttrap_procs.fth_table[FASTTRAP_PROCS_INDEX(pid)];
	mutex_enter(&bucket->ftb_mtx);

	for (fprc = bucket->ftb_data; fprc != NULL; fprc = fprc->ftpc_next) {
		if (fprc->ftpc_pid == pid && fprc->ftpc_acount != 0) {
			mutex_enter(&fprc->ftpc_mtx);
			mutex_exit(&bucket->ftb_mtx);
			fprc->ftpc_rcount++;
			atomic_inc_64(&fprc->ftpc_acount);
			ASSERT(fprc->ftpc_acount <= fprc->ftpc_rcount);
			mutex_exit(&fprc->ftpc_mtx);

			return (fprc);
		}
	}

	/*
	 * Drop the bucket lock so we don't try to perform a sleeping
	 * allocation under it.
	 */
	mutex_exit(&bucket->ftb_mtx);

	new_fprc = kmem_zalloc(sizeof (fasttrap_proc_t), KM_SLEEP);
	new_fprc->ftpc_pid = pid;
	new_fprc->ftpc_rcount = 1;
	new_fprc->ftpc_acount = 1;
#ifndef illumos
	mutex_init(&new_fprc->ftpc_mtx, "fasttrap proc mtx", MUTEX_DEFAULT,
	    NULL);
#endif

	mutex_enter(&bucket->ftb_mtx);

	/*
	 * Take another lap through the list to make sure a proc hasn't
	 * been created for this pid while we weren't under the bucket lock.
	 */
	for (fprc = bucket->ftb_data; fprc != NULL; fprc = fprc->ftpc_next) {
		if (fprc->ftpc_pid == pid && fprc->ftpc_acount != 0) {
			mutex_enter(&fprc->ftpc_mtx);
			mutex_exit(&bucket->ftb_mtx);
			fprc->ftpc_rcount++;
			atomic_inc_64(&fprc->ftpc_acount);
			ASSERT(fprc->ftpc_acount <= fprc->ftpc_rcount);
			mutex_exit(&fprc->ftpc_mtx);

			kmem_free(new_fprc, sizeof (fasttrap_proc_t));

			return (fprc);
		}
	}

	new_fprc->ftpc_next = bucket->ftb_data;
	bucket->ftb_data = new_fprc;

	mutex_exit(&bucket->ftb_mtx);

	return (new_fprc);
}