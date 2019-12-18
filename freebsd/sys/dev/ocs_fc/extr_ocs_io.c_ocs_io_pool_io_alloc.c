#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;
struct TYPE_11__ {char* display_name; scalar_t__ io_free; int /*<<< orphan*/ * mgmt_functions; scalar_t__ els_req_free; scalar_t__ seq_init; scalar_t__ hw_tag; scalar_t__ init_task_tag; scalar_t__ tgt_task_tag; scalar_t__ sgl_count; scalar_t__ timeout; TYPE_2__* ocs; scalar_t__ transferred; int /*<<< orphan*/ * hio; int /*<<< orphan*/  hio_type; int /*<<< orphan*/  io_type; } ;
typedef  TYPE_3__ ocs_io_t ;
struct TYPE_12__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; TYPE_2__* ocs; } ;
typedef  TYPE_4__ ocs_io_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  io_total_alloc; int /*<<< orphan*/  io_active_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_IO_MAX ; 
 int /*<<< orphan*/  OCS_IO_TYPE_MAX ; 
 int /*<<< orphan*/  io_mgmt_functions ; 
 int /*<<< orphan*/  ocs_assert (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 TYPE_3__* ocs_pool_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

ocs_io_t *
ocs_io_pool_io_alloc(ocs_io_pool_t *io_pool)
{
	ocs_io_t *io = NULL;
	ocs_t *ocs;

	ocs_assert(io_pool, NULL);

	ocs = io_pool->ocs;

	ocs_lock(&io_pool->lock);
	if ((io = ocs_pool_get(io_pool->pool)) != NULL) {
		ocs_unlock(&io_pool->lock);

		io->io_type = OCS_IO_TYPE_MAX;
		io->hio_type = OCS_HW_IO_MAX;
		io->hio = NULL;
		io->transferred = 0;
		io->ocs = ocs;
		io->timeout = 0;
		io->sgl_count = 0;
		io->tgt_task_tag = 0;
		io->init_task_tag = 0;
		io->hw_tag = 0;
		io->display_name = "pending";
		io->seq_init = 0;
		io->els_req_free = 0;
		io->mgmt_functions = &io_mgmt_functions;
		io->io_free = 0;
		ocs_atomic_add_return(&ocs->xport->io_active_count, 1);
		ocs_atomic_add_return(&ocs->xport->io_total_alloc, 1);
	} else {
		ocs_unlock(&io_pool->lock);
	}
	return io;
}