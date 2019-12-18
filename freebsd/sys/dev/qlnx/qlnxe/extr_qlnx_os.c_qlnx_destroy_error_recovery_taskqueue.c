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
struct TYPE_3__ {int /*<<< orphan*/ * err_taskqueue; int /*<<< orphan*/  err_task; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_destroy_error_recovery_taskqueue(qlnx_host_t *ha)
{
        if (ha->err_taskqueue != NULL) {
                taskqueue_drain(ha->err_taskqueue, &ha->err_task);
                taskqueue_free(ha->err_taskqueue);
        }

        ha->err_taskqueue = NULL;

        return;
}