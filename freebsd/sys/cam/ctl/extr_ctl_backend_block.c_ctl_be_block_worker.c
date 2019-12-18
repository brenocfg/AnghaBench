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
union ctl_io {int /*<<< orphan*/  scsiio; int /*<<< orphan*/  io_hdr; } ;
struct ctl_be_lun {int flags; } ;
struct ctl_be_block_lun {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  input_queue; int /*<<< orphan*/  config_read_queue; int /*<<< orphan*/  config_write_queue; int /*<<< orphan*/  (* dispatch ) (struct ctl_be_block_lun*,struct ctl_be_block_io*) ;int /*<<< orphan*/  datamove_queue; struct ctl_be_lun cbe_lun; } ;
struct ctl_be_block_io {int dummy; } ;
struct TYPE_2__ {scalar_t__ ptr; } ;

/* Variables and functions */
 int CTL_LUN_FLAG_NO_MEDIA ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 TYPE_1__* PRIV (union ctl_io*) ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_be_block_cr_dispatch (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_be_block_cw_dispatch (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_be_block_dispatch (struct ctl_be_block_lun*,union ctl_io*) ; 
 int /*<<< orphan*/  ctl_complete_beio (struct ctl_be_block_io*) ; 
 int /*<<< orphan*/  ctl_config_read_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_data_submit_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_io_hdr ; 
 int /*<<< orphan*/  ctl_set_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ctl_be_block_lun*,struct ctl_be_block_io*) ; 

__attribute__((used)) static void
ctl_be_block_worker(void *context, int pending)
{
	struct ctl_be_block_lun *be_lun = (struct ctl_be_block_lun *)context;
	struct ctl_be_lun *cbe_lun = &be_lun->cbe_lun;
	union ctl_io *io;
	struct ctl_be_block_io *beio;

	DPRINTF("entered\n");
	/*
	 * Fetch and process I/Os from all queues.  If we detect LUN
	 * CTL_LUN_FLAG_NO_MEDIA status here -- it is result of a race,
	 * so make response maximally opaque to not confuse initiator.
	 */
	for (;;) {
		mtx_lock(&be_lun->queue_lock);
		io = (union ctl_io *)STAILQ_FIRST(&be_lun->datamove_queue);
		if (io != NULL) {
			DPRINTF("datamove queue\n");
			STAILQ_REMOVE(&be_lun->datamove_queue, &io->io_hdr,
				      ctl_io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			beio = (struct ctl_be_block_io *)PRIV(io)->ptr;
			if (cbe_lun->flags & CTL_LUN_FLAG_NO_MEDIA) {
				ctl_set_busy(&io->scsiio);
				ctl_complete_beio(beio);
				return;
			}
			be_lun->dispatch(be_lun, beio);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&be_lun->config_write_queue);
		if (io != NULL) {
			DPRINTF("config write queue\n");
			STAILQ_REMOVE(&be_lun->config_write_queue, &io->io_hdr,
				      ctl_io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			if (cbe_lun->flags & CTL_LUN_FLAG_NO_MEDIA) {
				ctl_set_busy(&io->scsiio);
				ctl_config_write_done(io);
				return;
			}
			ctl_be_block_cw_dispatch(be_lun, io);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&be_lun->config_read_queue);
		if (io != NULL) {
			DPRINTF("config read queue\n");
			STAILQ_REMOVE(&be_lun->config_read_queue, &io->io_hdr,
				      ctl_io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			if (cbe_lun->flags & CTL_LUN_FLAG_NO_MEDIA) {
				ctl_set_busy(&io->scsiio);
				ctl_config_read_done(io);
				return;
			}
			ctl_be_block_cr_dispatch(be_lun, io);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&be_lun->input_queue);
		if (io != NULL) {
			DPRINTF("input queue\n");
			STAILQ_REMOVE(&be_lun->input_queue, &io->io_hdr,
				      ctl_io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			if (cbe_lun->flags & CTL_LUN_FLAG_NO_MEDIA) {
				ctl_set_busy(&io->scsiio);
				ctl_data_submit_done(io);
				return;
			}
			ctl_be_block_dispatch(be_lun, io);
			continue;
		}

		/*
		 * If we get here, there is no work left in the queues, so
		 * just break out and let the task queue go to sleep.
		 */
		mtx_unlock(&be_lun->queue_lock);
		break;
	}
}