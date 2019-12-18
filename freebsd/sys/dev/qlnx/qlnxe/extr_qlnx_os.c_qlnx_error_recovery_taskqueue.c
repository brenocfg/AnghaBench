#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  qlnx_callout; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLNX_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QLNX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  QL_DPRINT2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  qlnx_init (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_rdma_dev_add (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_rdma_dev_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_slowpath_start (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_slowpath_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  qlnx_timer ; 

__attribute__((used)) static void
qlnx_error_recovery_taskqueue(void *context, int pending)
{
        qlnx_host_t *ha;

        ha = context;

        QL_DPRINT2(ha, "enter\n");

        QLNX_LOCK(ha);
        qlnx_stop(ha);
        QLNX_UNLOCK(ha);

#ifdef QLNX_ENABLE_IWARP
	qlnx_rdma_dev_remove(ha);
#endif /* #ifdef QLNX_ENABLE_IWARP */

        qlnx_slowpath_stop(ha);
        qlnx_slowpath_start(ha);

#ifdef QLNX_ENABLE_IWARP
	qlnx_rdma_dev_add(ha);
#endif /* #ifdef QLNX_ENABLE_IWARP */

        qlnx_init(ha);

        callout_reset(&ha->qlnx_callout, hz, qlnx_timer, ha);

        QL_DPRINT2(ha, "exit\n");

        return;
}