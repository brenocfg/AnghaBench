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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tq_name ;
struct qlnx_fastpath {int /*<<< orphan*/ * fp_taskqueue; int /*<<< orphan*/  fp_task; } ;
struct TYPE_4__ {int num_rss; struct qlnx_fastpath* fp_array; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qlnx_fastpath*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qlnx_fp_taskqueue ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
qlnx_create_fp_taskqueues(qlnx_host_t *ha)
{
	int	i;
	uint8_t	tq_name[32];
	struct qlnx_fastpath *fp;

	for (i = 0; i < ha->num_rss; i++) {

                fp = &ha->fp_array[i];

		bzero(tq_name, sizeof (tq_name));
		snprintf(tq_name, sizeof (tq_name), "ql_fp_tq_%d", i);

		TASK_INIT(&fp->fp_task, 0, qlnx_fp_taskqueue, fp);

		fp->fp_taskqueue = taskqueue_create(tq_name, M_NOWAIT,
					taskqueue_thread_enqueue,
					&fp->fp_taskqueue);

		if (fp->fp_taskqueue == NULL) 
			return (-1);

		taskqueue_start_threads(&fp->fp_taskqueue, 1, PI_NET, "%s",
			tq_name);

		QL_DPRINT1(ha, "%p\n",fp->fp_taskqueue);
	}

	return (0);
}