#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * app; scalar_t__ flags; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {TYPE_2__* ocs; TYPE_1__ tgt_io; } ;
typedef  TYPE_3__ ocs_io_t ;
struct TYPE_7__ {scalar_t__ io_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CAM_IO_FREE ; 
 int /*<<< orphan*/  atomic_subtract_acq_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  ocs_scsi_io_complete (TYPE_3__*) ; 

__attribute__((used)) static inline void ocs_target_io_free(ocs_io_t *io)
{
	io->tgt_io.state = OCS_CAM_IO_FREE;
	io->tgt_io.flags = 0;
	io->tgt_io.app = NULL;
	ocs_scsi_io_complete(io);
	if(io->ocs->io_in_use != 0)
		atomic_subtract_acq_32(&io->ocs->io_in_use, 1);
}