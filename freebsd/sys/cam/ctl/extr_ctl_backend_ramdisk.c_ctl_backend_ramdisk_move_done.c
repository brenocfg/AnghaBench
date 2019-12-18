#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kern_sg_entries; scalar_t__ kern_data_resid; scalar_t__ kern_data_len; int /*<<< orphan*/  kern_rel_offset; int /*<<< orphan*/  kern_data_ptr; } ;
struct TYPE_8__ {int flags; scalar_t__ port_status; int status; int /*<<< orphan*/  num_dmas; int /*<<< orphan*/  dma_bt; int /*<<< orphan*/  dma_start_bt; } ;
union ctl_io {TYPE_1__ scsiio; TYPE_4__ io_hdr; } ;
struct ctl_be_ramdisk_lun {int /*<<< orphan*/  io_task; int /*<<< orphan*/  io_taskqueue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  cont_queue; } ;
struct ctl_be_lun {struct ctl_be_ramdisk_lun* be_lun; } ;
struct bintime {int dummy; } ;
struct TYPE_10__ {int flags; scalar_t__ len; } ;
struct TYPE_9__ {scalar_t__ len; } ;

/* Variables and functions */
 TYPE_6__* ARGS (union ctl_io*) ; 
 struct ctl_be_lun* CTL_BACKEND_LUN (union ctl_io*) ; 
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_DATA_MASK ; 
 int CTL_FLAG_DATA_OUT ; 
 int CTL_LLF_COMPARE ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  M_RAMDISK ; 
 TYPE_5__* PRIV (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bintime_add (int /*<<< orphan*/ *,struct bintime*) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 scalar_t__ ctl_backend_ramdisk_cmp (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_data_submit_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_set_internal_failure (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ctl_set_invalid_field_ciu (TYPE_1__*) ; 
 int /*<<< orphan*/  ctl_set_success (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_backend_ramdisk_move_done(union ctl_io *io)
{
	struct ctl_be_lun *cbe_lun = CTL_BACKEND_LUN(io);
	struct ctl_be_ramdisk_lun *be_lun = cbe_lun->be_lun;
#ifdef CTL_TIME_IO
	struct bintime cur_bt;
#endif

	CTL_DEBUG_PRINT(("ctl_backend_ramdisk_move_done\n"));
#ifdef CTL_TIME_IO
	getbinuptime(&cur_bt);
	bintime_sub(&cur_bt, &io->io_hdr.dma_start_bt);
	bintime_add(&io->io_hdr.dma_bt, &cur_bt);
#endif
	io->io_hdr.num_dmas++;
	if (io->scsiio.kern_sg_entries > 0)
		free(io->scsiio.kern_data_ptr, M_RAMDISK);
	io->scsiio.kern_rel_offset += io->scsiio.kern_data_len;
	if (io->io_hdr.flags & CTL_FLAG_ABORT) {
		;
	} else if (io->io_hdr.port_status != 0 &&
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
		if (ARGS(io)->flags & CTL_LLF_COMPARE) {
			/* We have data block ready for comparison. */
			if (ctl_backend_ramdisk_cmp(io))
				goto done;
		}
		if (ARGS(io)->len > PRIV(io)->len) {
			mtx_lock(&be_lun->queue_lock);
			STAILQ_INSERT_TAIL(&be_lun->cont_queue,
			    &io->io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			taskqueue_enqueue(be_lun->io_taskqueue,
			    &be_lun->io_task);
			return (0);
		}
		ctl_set_success(&io->scsiio);
	}
done:
	ctl_data_submit_done(io);
	return(0);
}