#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_scsi_io_status_e ;
typedef  int /*<<< orphan*/  ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_scsi_io_complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_target_tmf_cb(ocs_io_t *io, ocs_scsi_io_status_e scsi_status, uint32_t flags,
		void *arg)
{

	/*device_printf(io->ocs->dev, "%s: tag=%x io=%p s=%#x\n",
			 __func__, io->tag, io, scsi_status);*/
	ocs_scsi_io_complete(io);

	return 0;
}