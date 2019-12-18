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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tq_name ;
struct TYPE_5__ {int /*<<< orphan*/ * err_taskqueue; int /*<<< orphan*/  err_task; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlnx_error_recovery_taskqueue ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
qlnx_create_error_recovery_taskqueue(qlnx_host_t *ha)
{
        uint8_t tq_name[32];

        bzero(tq_name, sizeof (tq_name));
        snprintf(tq_name, sizeof (tq_name), "ql_err_tq");

        TASK_INIT(&ha->err_task, 0, qlnx_error_recovery_taskqueue, ha);

        ha->err_taskqueue = taskqueue_create(tq_name, M_NOWAIT,
                                taskqueue_thread_enqueue, &ha->err_taskqueue);


        if (ha->err_taskqueue == NULL)
                return (-1);

        taskqueue_start_threads(&ha->err_taskqueue, 1, PI_NET, "%s", tq_name);

        QL_DPRINT1(ha, "%p\n",ha->err_taskqueue);

        return (0);
}