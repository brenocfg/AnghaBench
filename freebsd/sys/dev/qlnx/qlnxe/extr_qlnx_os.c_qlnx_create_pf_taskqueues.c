#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tq_name ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_6__ {int num_hwfns; struct ecore_hwfn* hwfns; } ;
struct TYPE_8__ {TYPE_2__* sriov_task; TYPE_1__ cdev; } ;
typedef  TYPE_3__ qlnx_host_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pf_taskqueue; int /*<<< orphan*/  pf_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_hwfn*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlnx_pf_taskqueue ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
qlnx_create_pf_taskqueues(qlnx_host_t *ha)
{
	int	i;
	uint8_t	tq_name[32];

	for (i = 0; i < ha->cdev.num_hwfns; i++) {

                struct ecore_hwfn *p_hwfn = &ha->cdev.hwfns[i];

		bzero(tq_name, sizeof (tq_name));
		snprintf(tq_name, sizeof (tq_name), "ql_pf_tq_%d", i);

		TASK_INIT(&ha->sriov_task[i].pf_task, 0, qlnx_pf_taskqueue, p_hwfn);

		ha->sriov_task[i].pf_taskqueue = taskqueue_create(tq_name, M_NOWAIT,
			 taskqueue_thread_enqueue,
			&ha->sriov_task[i].pf_taskqueue);

		if (ha->sriov_task[i].pf_taskqueue == NULL) 
			return (-1);

		taskqueue_start_threads(&ha->sriov_task[i].pf_taskqueue, 1,
			PI_NET, "%s", tq_name);

		QL_DPRINT1(ha, "%p\n", ha->sriov_task[i].pf_taskqueue);
	}

	return (0);
}