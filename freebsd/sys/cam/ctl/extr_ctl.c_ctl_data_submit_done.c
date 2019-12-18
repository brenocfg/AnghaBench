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
struct TYPE_3__ {int /*<<< orphan*/  (* io_cont ) (union ctl_io*) ;} ;
struct TYPE_4__ {int flags; int status; } ;
union ctl_io {TYPE_1__ scsiio; TYPE_2__ io_hdr; } ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_IO_CONT ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  stub1 (union ctl_io*) ; 

void
ctl_data_submit_done(union ctl_io *io)
{
	/*
	 * If the IO_CONT flag is set, we need to call the supplied
	 * function to continue processing the I/O, instead of completing
	 * the I/O just yet.
	 *
	 * If there is an error, though, we don't want to keep processing.
	 * Instead, just send status back to the initiator.
	 */
	if ((io->io_hdr.flags & CTL_FLAG_IO_CONT) &&
	    (io->io_hdr.flags & CTL_FLAG_ABORT) == 0 &&
	    ((io->io_hdr.status & CTL_STATUS_MASK) == CTL_STATUS_NONE ||
	     (io->io_hdr.status & CTL_STATUS_MASK) == CTL_SUCCESS)) {
		io->scsiio.io_cont(io);
		return;
	}
	ctl_done(io);
}