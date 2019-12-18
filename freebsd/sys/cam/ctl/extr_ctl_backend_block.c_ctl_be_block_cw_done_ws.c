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
struct ctl_be_block_io {union ctl_io* io; } ;

/* Variables and functions */
 int CTL_FLAG_ABORT ; 
 int CTL_STATUS_MASK ; 
 int CTL_STATUS_NONE ; 
 int CTL_SUCCESS ; 
 int /*<<< orphan*/  ctl_be_block_config_write (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_config_write_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_free_beio (struct ctl_be_block_io*) ; 

__attribute__((used)) static void
ctl_be_block_cw_done_ws(struct ctl_be_block_io *beio)
{
	union ctl_io *io;

	io = beio->io;
	ctl_free_beio(beio);
	if ((io->io_hdr.flags & CTL_FLAG_ABORT) ||
	    ((io->io_hdr.status & CTL_STATUS_MASK) != CTL_STATUS_NONE &&
	     (io->io_hdr.status & CTL_STATUS_MASK) != CTL_SUCCESS)) {
		ctl_config_write_done(io);
		return;
	}

	ctl_be_block_config_write(io);
}