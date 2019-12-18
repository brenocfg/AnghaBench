#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ext_data_filled; int /*<<< orphan*/  tag_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  targ_lun; int /*<<< orphan*/  targ_port; scalar_t__ initid; } ;
struct TYPE_7__ {TYPE_4__ nexus; } ;
union ctl_io {TYPE_2__ scsiio; TYPE_3__ io_hdr; } ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  targ_port; } ;
struct tpcl_softc {int /*<<< orphan*/  cur_tag_num; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int ctl_queue (union ctl_io*) ; 
 struct tpcl_softc tpcl_softc ; 

int
tpcl_queue(union ctl_io *io, uint64_t lun)
{
	struct tpcl_softc *tsoftc = &tpcl_softc;

	io->io_hdr.nexus.initid = 0;
	io->io_hdr.nexus.targ_port = tsoftc->port.targ_port;
	io->io_hdr.nexus.targ_lun = lun;
	io->scsiio.tag_num = atomic_fetchadd_int(&tsoftc->cur_tag_num, 1);
	io->scsiio.ext_data_filled = 0;
	return (ctl_queue(io));
}