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
struct TYPE_3__ {int /*<<< orphan*/  (* io_cont ) (union ctl_io*) ;int /*<<< orphan*/ * kern_data_ptr; } ;
struct TYPE_4__ {int flags; int status; } ;
union ctl_io {TYPE_1__ scsiio; TYPE_2__ io_hdr; } ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_FLAG_ALLOCATED ; 
 int CTL_FLAG_IO_CONT ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  ctl_datamove (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (union ctl_io*) ; 

void
ctl_config_read_done(union ctl_io *io)
{
	uint8_t *buf;

	/*
	 * If there is some error -- we are done, skip data transfer.
	 */
	if ((io->io_hdr.flags & CTL_FLAG_ABORT) != 0 ||
	    ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	     (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS)) {
		if (io->io_hdr.flags & CTL_FLAG_ALLOCATED)
			buf = io->scsiio.kern_data_ptr;
		else
			buf = NULL;
		ctl_done(io);
		if (buf)
			free(buf, M_CTL);
		return;
	}

	/*
	 * If the IO_CONT flag is set, we need to call the supplied
	 * function to continue processing the I/O, instead of completing
	 * the I/O just yet.
	 */
	if (io->io_hdr.flags & CTL_FLAG_IO_CONT) {
		io->scsiio.io_cont(io);
		return;
	}

	ctl_datamove(io);
}