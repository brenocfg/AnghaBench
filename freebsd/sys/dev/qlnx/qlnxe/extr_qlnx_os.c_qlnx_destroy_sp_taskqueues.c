#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_hwfns; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** sp_taskqueue; int /*<<< orphan*/ * sp_task; TYPE_1__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_destroy_sp_taskqueues(qlnx_host_t *ha)
{
	int	i;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {
		if (ha->sp_taskqueue[i] != NULL) {
			taskqueue_drain(ha->sp_taskqueue[i], &ha->sp_task[i]);
			taskqueue_free(ha->sp_taskqueue[i]);
		}
	}
	return;
}