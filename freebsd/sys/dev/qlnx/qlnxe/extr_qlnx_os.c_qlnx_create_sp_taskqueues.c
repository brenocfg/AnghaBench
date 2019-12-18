#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tq_name ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_5__ {int num_hwfns; struct ecore_hwfn* hwfns; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** sp_taskqueue; int /*<<< orphan*/ * sp_task; TYPE_1__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_hwfn*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlnx_sp_taskqueue ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
qlnx_create_sp_taskqueues(qlnx_host_t *ha)
{
	int	i;
	uint8_t	tq_name[32];

	for (i = 0; i < ha->cdev.num_hwfns; i++) {

                struct ecore_hwfn *p_hwfn = &ha->cdev.hwfns[i];

		bzero(tq_name, sizeof (tq_name));
		snprintf(tq_name, sizeof (tq_name), "ql_sp_tq_%d", i);

		TASK_INIT(&ha->sp_task[i], 0, qlnx_sp_taskqueue, p_hwfn);

		ha->sp_taskqueue[i] = taskqueue_create(tq_name, M_NOWAIT,
			 taskqueue_thread_enqueue, &ha->sp_taskqueue[i]);

		if (ha->sp_taskqueue[i] == NULL) 
			return (-1);

		taskqueue_start_threads(&ha->sp_taskqueue[i], 1, PI_NET, "%s",
			tq_name);

		QL_DPRINT1(ha, "%p\n", ha->sp_taskqueue[i]);
	}

	return (0);
}