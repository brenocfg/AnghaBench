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
struct qlnx_fastpath {int /*<<< orphan*/  fp_task; int /*<<< orphan*/ * fp_taskqueue; } ;
struct TYPE_5__ {int num_rss; struct qlnx_fastpath* fp_array; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLNX_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QLNX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_drain_fp_taskqueues(qlnx_host_t *ha)
{
	int			i;
	struct qlnx_fastpath	*fp;

	for (i = 0; i < ha->num_rss; i++) {
                fp = &ha->fp_array[i];

		if (fp->fp_taskqueue != NULL) {
			QLNX_UNLOCK(ha);
			taskqueue_drain(fp->fp_taskqueue, &fp->fp_task);
			QLNX_LOCK(ha);
		}
	}
	return;
}