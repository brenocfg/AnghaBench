#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_timed_wqe; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_10__ {int /*<<< orphan*/  rnode; int /*<<< orphan*/  (* abort_done ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;void* abort_arg; int /*<<< orphan*/  (* done ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;void* arg; TYPE_1__* wq; int /*<<< orphan*/  wqe_link; } ;
typedef  TYPE_3__ ocs_hw_io_t ;
typedef  int /*<<< orphan*/  (* ocs_hw_done_t ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_8__ {int /*<<< orphan*/  pending_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_FC_WCQE_STATUS_SHUTDOWN ; 
 scalar_t__ ocs_list_on_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_io_cancel_cleanup(ocs_hw_t *hw, ocs_hw_io_t *io)
{
	ocs_hw_done_t  done = io->done;
	ocs_hw_done_t  abort_done = io->abort_done;

	/* first check active_wqe list and remove if there */
	if (ocs_list_on_list(&io->wqe_link)) {
		ocs_list_remove(&hw->io_timed_wqe, io);
	}

	/* Remove from WQ pending list */
	if ((io->wq != NULL) && ocs_list_on_list(&io->wq->pending_list)) {
		ocs_list_remove(&io->wq->pending_list, io);
	}

	if (io->done) {
		void		*arg = io->arg;

		io->done = NULL;
		ocs_unlock(&hw->io_lock);
		done(io, io->rnode, 0, SLI4_FC_WCQE_STATUS_SHUTDOWN, 0, arg);
		ocs_lock(&hw->io_lock);
	}

	if (io->abort_done != NULL) {
		void		*abort_arg = io->abort_arg;

		io->abort_done = NULL;
		ocs_unlock(&hw->io_lock);
		abort_done(io, io->rnode, 0, SLI4_FC_WCQE_STATUS_SHUTDOWN, 0, abort_arg);
		ocs_lock(&hw->io_lock);
	}
}