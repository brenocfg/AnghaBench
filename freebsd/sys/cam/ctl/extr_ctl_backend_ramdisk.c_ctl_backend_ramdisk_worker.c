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
union ctl_io {int /*<<< orphan*/  io_hdr; } ;
struct ctl_be_ramdisk_lun {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  cont_queue; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 TYPE_1__* ARGS (union ctl_io*) ; 
 int CTL_LLF_COMPARE ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_compare (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_backend_ramdisk_rw (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_io_hdr ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_backend_ramdisk_worker(void *context, int pending)
{
	struct ctl_be_ramdisk_lun *be_lun;
	union ctl_io *io;

	be_lun = (struct ctl_be_ramdisk_lun *)context;
	mtx_lock(&be_lun->queue_lock);
	for (;;) {
		io = (union ctl_io *)STAILQ_FIRST(&be_lun->cont_queue);
		if (io != NULL) {
			STAILQ_REMOVE(&be_lun->cont_queue, &io->io_hdr,
				      ctl_io_hdr, links);
			mtx_unlock(&be_lun->queue_lock);
			if (ARGS(io)->flags & CTL_LLF_COMPARE)
				ctl_backend_ramdisk_compare(io);
			else
				ctl_backend_ramdisk_rw(io);
			mtx_lock(&be_lun->queue_lock);
			continue;
		}

		/*
		 * If we get here, there is no work left in the queues, so
		 * just break out and let the task queue go to sleep.
		 */
		break;
	}
	mtx_unlock(&be_lun->queue_lock);
}