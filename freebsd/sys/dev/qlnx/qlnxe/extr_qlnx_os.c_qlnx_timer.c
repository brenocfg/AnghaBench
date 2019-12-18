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
struct TYPE_4__ {int /*<<< orphan*/  qlnx_callout; scalar_t__ storm_stats_gather; int /*<<< orphan*/  hw_stats; int /*<<< orphan*/  cdev; int /*<<< orphan*/  err_task; int /*<<< orphan*/  err_taskqueue; scalar_t__ error_recovery; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*) ; 
 int /*<<< orphan*/  ecore_get_vport_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  qlnx_sample_storm_stats (TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_timer(void *arg)
{
	qlnx_host_t	*ha;

	ha = (qlnx_host_t *)arg;

	if (ha->error_recovery) {
		ha->error_recovery = 0;
		taskqueue_enqueue(ha->err_taskqueue, &ha->err_task);
		return;
	}

       	ecore_get_vport_stats(&ha->cdev, &ha->hw_stats);

	if (ha->storm_stats_gather)
		qlnx_sample_storm_stats(ha);

	callout_reset(&ha->qlnx_callout, hz, qlnx_timer, ha);

	return;
}