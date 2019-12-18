#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ io_type; } ;
union ctl_io {TYPE_1__ io_hdr; } ;
struct ctl_be_lun {scalar_t__ be_lun; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  input_queue; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 struct ctl_be_lun* CTL_BACKEND_LUN (union ctl_io*) ; 
 scalar_t__ CTL_IO_SCSI ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_2__* PRIV (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_be_block_submit(union ctl_io *io)
{
	struct ctl_be_block_lun *be_lun;
	struct ctl_be_lun *cbe_lun;

	DPRINTF("entered\n");

	cbe_lun = CTL_BACKEND_LUN(io);
	be_lun = (struct ctl_be_block_lun *)cbe_lun->be_lun;

	/*
	 * Make sure we only get SCSI I/O.
	 */
	KASSERT(io->io_hdr.io_type == CTL_IO_SCSI, ("Non-SCSI I/O (type "
		"%#x) encountered", io->io_hdr.io_type));

	PRIV(io)->len = 0;

	mtx_lock(&be_lun->queue_lock);
	STAILQ_INSERT_TAIL(&be_lun->input_queue, &io->io_hdr, links);
	mtx_unlock(&be_lun->queue_lock);
	taskqueue_enqueue(be_lun->io_taskqueue, &be_lun->io_task);

	return (CTL_RETVAL_COMPLETE);
}