#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t isc_uint32_t ;
struct TYPE_3__ {size_t ntasks; int /*<<< orphan*/ * tasks; } ;
typedef  TYPE_1__ isc_taskpool_t ;
typedef  int /*<<< orphan*/  isc_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_random_get (size_t*) ; 
 int /*<<< orphan*/  isc_task_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

void
isc_taskpool_gettask(isc_taskpool_t *pool, isc_task_t **targetp) {
	isc_uint32_t i;
	isc_random_get(&i);
	isc_task_attach(pool->tasks[i % pool->ntasks], targetp);
}