#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {TYPE_1__* fcfi; TYPE_5__ io_pending_lock; int /*<<< orphan*/  io_pool; int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_2__ ocs_xport_t ;
typedef  int /*<<< orphan*/  ocs_t ;
struct TYPE_7__ {TYPE_5__ pend_frames_lock; } ;

/* Variables and functions */
 size_t SLI4_MAX_FCFI ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_io_pool_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_lock_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_node_free_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_xport_rq_threads_teardown (TYPE_2__*) ; 

void
ocs_xport_free(ocs_xport_t *xport)
{
	ocs_t *ocs;
	uint32_t i;

	if (xport) {
		ocs = xport->ocs;
		ocs_io_pool_free(xport->io_pool);
		ocs_node_free_pool(ocs);
		if(mtx_initialized(&xport->io_pending_lock.lock))
			ocs_lock_free(&xport->io_pending_lock);

		for (i = 0; i < SLI4_MAX_FCFI; i++) {
			ocs_lock_free(&xport->fcfi[i].pend_frames_lock);
		}

		ocs_xport_rq_threads_teardown(xport);

		ocs_free(ocs, xport, sizeof(*xport));
	}
}