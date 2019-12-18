#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  hio; int /*<<< orphan*/  (* hw_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_1__ ocs_io_t ;
typedef  int /*<<< orphan*/  ocs_hw_t ;
typedef  int /*<<< orphan*/  (* ocs_hw_done_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_FC_WCQE_STATUS_DISPATCH_ERROR ; 

__attribute__((used)) static int32_t
ocs_scsi_check_pending_async_cb(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_io_t *io = arg;

	if (io != NULL) {
		if (io->hw_cb != NULL) {
			ocs_hw_done_t cb = io->hw_cb;

			io->hw_cb = NULL;
			cb(io->hio, NULL, 0, SLI4_FC_WCQE_STATUS_DISPATCH_ERROR, 0, io);
		}
	}
	return 0;
}