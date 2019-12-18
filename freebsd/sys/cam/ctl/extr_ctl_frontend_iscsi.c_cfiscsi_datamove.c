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
struct TYPE_4__ {scalar_t__ ext_data_filled; } ;
struct TYPE_3__ {int flags; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_1__ io_hdr; } ;

/* Variables and functions */
 int CTL_FLAG_DATA_IN ; 
 int CTL_FLAG_DATA_MASK ; 
 int /*<<< orphan*/  cfiscsi_datamove_in (union ctl_io*) ; 
 int /*<<< orphan*/  cfiscsi_datamove_out (union ctl_io*) ; 

__attribute__((used)) static void
cfiscsi_datamove(union ctl_io *io)
{

	if ((io->io_hdr.flags & CTL_FLAG_DATA_MASK) == CTL_FLAG_DATA_IN)
		cfiscsi_datamove_in(io);
	else {
		/* We hadn't received anything during this datamove yet. */
		io->scsiio.ext_data_filled = 0;
		cfiscsi_datamove_out(io);
	}
}