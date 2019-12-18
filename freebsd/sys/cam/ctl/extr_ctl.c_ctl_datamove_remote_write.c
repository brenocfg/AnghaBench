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
struct TYPE_3__ {int /*<<< orphan*/  be_move_done; int /*<<< orphan*/ * kern_data_ptr; } ;
union ctl_io {TYPE_1__ scsiio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {void (* fe_datamove ) (union ctl_io*) ;} ;

/* Variables and functions */
 scalar_t__ CTL_LSGL (union ctl_io*) ; 
 TYPE_2__* CTL_PORT (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_datamove_remote_dm_write_cb ; 
 int ctl_datamove_remote_sgl_setup (union ctl_io*) ; 

__attribute__((used)) static void
ctl_datamove_remote_write(union ctl_io *io)
{
	int retval;
	void (*fe_datamove)(union ctl_io *io);

	/*
	 * - Get the data from the host/HBA into local memory.
	 * - DMA memory from the local controller to the remote controller.
	 * - Send status back to the remote controller.
	 */

	retval = ctl_datamove_remote_sgl_setup(io);
	if (retval != 0)
		return;

	/* Switch the pointer over so the FETD knows what to do */
	io->scsiio.kern_data_ptr = (uint8_t *)CTL_LSGL(io);

	/*
	 * Use a custom move done callback, since we need to send completion
	 * back to the other controller, not to the backend on this side.
	 */
	io->scsiio.be_move_done = ctl_datamove_remote_dm_write_cb;

	fe_datamove = CTL_PORT(io)->fe_datamove;
	fe_datamove(io);
}