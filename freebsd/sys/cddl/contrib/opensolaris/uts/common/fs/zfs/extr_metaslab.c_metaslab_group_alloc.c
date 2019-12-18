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
typedef  int /*<<< orphan*/  zio_alloc_list_t ;
typedef  unsigned long long uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  mg_lock; int /*<<< orphan*/  mg_allocations; int /*<<< orphan*/  mg_no_free_space; int /*<<< orphan*/  mg_failed_allocations; int /*<<< orphan*/  mg_initialized; } ;
typedef  TYPE_1__ metaslab_group_t ;
typedef  int /*<<< orphan*/  dva_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_TRUE ; 
 unsigned long long SPA_GANGBLOCKSIZE ; 
 int /*<<< orphan*/  TRACE_GROUP_FAILURE ; 
 unsigned long long metaslab_group_alloc_normal (TYPE_1__*,int /*<<< orphan*/ *,unsigned long long,unsigned long long,unsigned long long,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  metaslab_trace_add (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned long long,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
metaslab_group_alloc(metaslab_group_t *mg, zio_alloc_list_t *zal,
    uint64_t asize, uint64_t txg, uint64_t min_distance, dva_t *dva, int d,
    int allocator)
{
	uint64_t offset;
	ASSERT(mg->mg_initialized);

	offset = metaslab_group_alloc_normal(mg, zal, asize, txg,
	    min_distance, dva, d, allocator);

	mutex_enter(&mg->mg_lock);
	if (offset == -1ULL) {
		mg->mg_failed_allocations++;
		metaslab_trace_add(zal, mg, NULL, asize, d,
		    TRACE_GROUP_FAILURE, allocator);
		if (asize == SPA_GANGBLOCKSIZE) {
			/*
			 * This metaslab group was unable to allocate
			 * the minimum gang block size so it must be out of
			 * space. We must notify the allocation throttle
			 * to start skipping allocation attempts to this
			 * metaslab group until more space becomes available.
			 * Note: this failure cannot be caused by the
			 * allocation throttle since the allocation throttle
			 * is only responsible for skipping devices and
			 * not failing block allocations.
			 */
			mg->mg_no_free_space = B_TRUE;
		}
	}
	mg->mg_allocations++;
	mutex_exit(&mg->mg_lock);
	return (offset);
}