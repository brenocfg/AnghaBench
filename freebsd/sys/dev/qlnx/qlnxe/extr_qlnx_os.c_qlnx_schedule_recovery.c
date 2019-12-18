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
struct ecore_hwfn {scalar_t__ p_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  err_task; int /*<<< orphan*/  err_taskqueue; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 scalar_t__ qlnx_vf_device (TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qlnx_schedule_recovery(void *p_hwfn)
{
	qlnx_host_t	*ha;

	ha = (qlnx_host_t *)((struct ecore_hwfn *)p_hwfn)->p_dev;

	if (qlnx_vf_device(ha) != 0) {
		taskqueue_enqueue(ha->err_taskqueue, &ha->err_task);
	}

	return;
}