#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int status; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  input_queue; } ;
struct ctl_be_block_io {struct ctl_be_block_lun* lun; union ctl_io* io; } ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_data_submit_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_free_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_be_block_next(struct ctl_be_block_io *beio)
{
	struct ctl_be_block_lun *be_lun;
	union ctl_io *io;

	io = beio->io;
	be_lun = beio->lun;
	ctl_free_beio(beio);
	if ((io->io_hdr.flags & CTL_FLAG_ABORT) ||
	    ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	     (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS)) {
		ctl_data_submit_done(io);
		return;
	}

	io->io_hdr.status &= ~CTL_STATUS_MASK;
	io->io_hdr.status |= CTL_STATUS_NONE;

	mtx_lock(&be_lun->queue_lock);
	STAILQ_INSERT_TAIL(&be_lun->input_queue, &io->io_hdr, links);
	mtx_unlock(&be_lun->queue_lock);
	taskqueue_enqueue(be_lun->io_taskqueue, &be_lun->io_task);
}