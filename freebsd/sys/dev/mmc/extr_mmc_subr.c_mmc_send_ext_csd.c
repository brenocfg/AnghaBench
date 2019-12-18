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
struct mmc_data {int flags; int len; struct mmc_data* data; int /*<<< orphan*/  opcode; } ;
typedef  struct mmc_data uint8_t ;
struct mmc_command {int flags; int len; struct mmc_command* data; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_ADTC ; 
 int MMC_DATA_READ ; 
 int MMC_EXTCSD_SIZE ; 
 int MMC_RSP_R1 ; 
 int /*<<< orphan*/  MMC_SEND_EXT_CSD ; 
 int /*<<< orphan*/  memset (struct mmc_data*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_data*,int /*<<< orphan*/ ) ; 

int
mmc_send_ext_csd(device_t busdev, device_t dev, uint8_t *rawextcsd)
{
	struct mmc_command cmd;
	struct mmc_data data;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	memset(&data, 0, sizeof(data));

	memset(rawextcsd, 0, MMC_EXTCSD_SIZE);
	cmd.opcode = MMC_SEND_EXT_CSD;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
	cmd.data = &data;

	data.data = rawextcsd;
	data.len = MMC_EXTCSD_SIZE;
	data.flags = MMC_DATA_READ;

	err = mmc_wait_for_cmd(busdev, dev, &cmd, CMD_RETRIES);
	return (err);
}