#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ port_status; int status; int /*<<< orphan*/  num_dmas; int /*<<< orphan*/  dma_bt; int /*<<< orphan*/  dma_start_bt; } ;
struct TYPE_6__ {scalar_t__ kern_data_resid; scalar_t__ kern_data_len; int /*<<< orphan*/  kern_rel_offset; } ;
union ctl_io {TYPE_4__ io_hdr; TYPE_1__ scsiio; } ;
struct ctl_lba_len_flags {int flags; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  datamove_queue; } ;
struct ctl_be_block_io {scalar_t__ bio_cmd; int /*<<< orphan*/  io; struct ctl_be_block_lun* lun; } ;
struct bintime {int dummy; } ;
struct TYPE_8__ {scalar_t__ ptr; } ;

/* Variables and functions */
 struct ctl_lba_len_flags* ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_READ ; 
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_DATA_MASK ; 
 int CTL_FLAG_DATA_OUT ; 
 int CTL_LLF_COMPARE ; 
 int CTL_LLF_READ ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 TYPE_5__* PRIV (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bintime_add (int /*<<< orphan*/ *,struct bintime*) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_be_block_compare (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_complete_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  ctl_set_internal_failure (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ctl_set_invalid_field_ciu (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_set_success (TYPE_1__*) ; 
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_be_block_move_done(union ctl_io *io)
{
	struct ctl_be_block_io *beio;
	struct ctl_be_block_lun *be_lun;
	struct ctl_lba_len_flags *lbalen;
#ifdef CTL_TIME_IO
	struct bintime cur_bt;
#endif

	beio = (struct ctl_be_block_io *)PRIV(io)->ptr;
	be_lun = beio->lun;

	DPRINTF("entered\n");

#ifdef CTL_TIME_IO
	getbinuptime(&cur_bt);
	bintime_sub(&cur_bt, &io->io_hdr.dma_start_bt);
	bintime_add(&io->io_hdr.dma_bt, &cur_bt);
#endif
	io->io_hdr.num_dmas++;
	io->scsiio.kern_rel_offset += io->scsiio.kern_data_len;

	/*
	 * We set status at this point for read commands, and write
	 * commands with errors.
	 */
	if (io->io_hdr.flags & CTL_FLAG_ABORT) {
		;
	} else if ((io->io_hdr.port_status != 0) &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE ||
	     (io->io_hdr.status & CTL_STATUS_MASK) == CTL_SUCCESS)) {
		ctl_set_internal_failure(&io->scsiio, /*sks_valid*/ 1,
		    /*retry_count*/ io->io_hdr.port_status);
	} else if (io->scsiio.kern_data_resid != 0 &&
	    (io->io_hdr.flags & CTL_FLAG_DATA_MASK) == CTL_FLAG_DATA_OUT &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE ||
	     (io->io_hdr.status & CTL_STATUS_MASK) == CTL_SUCCESS)) {
		ctl_set_invalid_field_ciu(&io->scsiio);
	} else if ((io->io_hdr.port_status == 0) &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE)) {
		lbalen = ARGS(beio->io);
		if (lbalen->flags & CTL_LLF_READ) {
			ctl_set_success(&io->scsiio);
		} else if (lbalen->flags & CTL_LLF_COMPARE) {
			/* We have two data blocks ready for comparison. */
			ctl_be_block_compare(io);
		}
	}

	/*
	 * If this is a read, or a write with errors, it is done.
	 */
	if ((beio->bio_cmd == BIO_READ)
	 || ((io->io_hdr.flags & CTL_FLAG_ABORT) != 0)
	 || ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE)) {
		ctl_complete_beio(beio);
		return (0);
	}

	/*
	 * At this point, we have a write and the DMA completed
	 * successfully.  We now have to queue it to the task queue to
	 * execute the backend I/O.  That is because we do blocking
	 * memory allocations, and in the file backing case, blocking I/O.
	 * This move done routine is generally called in the SIM's
	 * interrupt context, and therefore we cannot block.
	 */
	mtx_lock(&be_lun->queue_lock);
	STAILQ_INSERT_TAIL(&be_lun->datamove_queue, &io->io_hdr, links);
	mtx_unlock(&be_lun->queue_lock);
	taskqueue_enqueue(be_lun->io_taskqueue, &be_lun->io_task);

	return (0);
}