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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {TYPE_2__ cpl; scalar_t__ is_read; TYPE_1__ cmd; } ;
typedef  int /*<<< orphan*/  pt ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_OPC_FIRMWARE_ACTIVATE ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 scalar_t__ NVME_SCT_COMMAND_SPECIFIC ; 
 scalar_t__ NVME_SC_FIRMWARE_REQUIRES_RESET ; 
 scalar_t__ NVME_STATUS_GET_SC (int /*<<< orphan*/ ) ; 
 scalar_t__ NVME_STATUS_GET_SCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (TYPE_2__*) ; 

__attribute__((used)) static int
activate_firmware(int fd, int slot, int activate_action)
{
	struct nvme_pt_command	pt;
	uint16_t sct, sc;

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_FIRMWARE_ACTIVATE;
	pt.cmd.cdw10 = htole32((activate_action << 3) | slot);
	pt.is_read = 0;

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "firmware activate request failed");

	sct = NVME_STATUS_GET_SCT(pt.cpl.status);
	sc = NVME_STATUS_GET_SC(pt.cpl.status);

	if (sct == NVME_SCT_COMMAND_SPECIFIC &&
	    sc == NVME_SC_FIRMWARE_REQUIRES_RESET)
		return 1;

	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "firmware activate request returned error");

	return 0;
}