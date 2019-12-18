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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct mmc_command {int arg; int flags; int* resp; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

int
mmc_send_status(device_t busdev, device_t dev, uint16_t rca, uint32_t *status)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = MMC_SEND_STATUS;
	cmd.arg = (uint32_t)rca << 16;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
	err = mmc_wait_for_cmd(busdev, dev, &cmd, CMD_RETRIES);
	*status = cmd.resp[0];
	return (err);
}