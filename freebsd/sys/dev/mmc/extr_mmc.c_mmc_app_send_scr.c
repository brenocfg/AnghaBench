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
struct mmc_data {int flags; int len; struct mmc_data* data; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
typedef  struct mmc_data uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int flags; int len; struct mmc_command* data; scalar_t__ arg; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ACMD_SEND_SCR ; 
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_ADTC ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_R1 ; 
 struct mmc_data be32toh (struct mmc_data) ; 
 int /*<<< orphan*/  memset (struct mmc_data*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_app_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_app_send_scr(struct mmc_softc *sc, uint16_t rca, uint32_t *rawscr)
{
	int err;
	struct mmc_command cmd;
	struct mmc_data data;

	memset(&cmd, 0, sizeof(cmd));
	memset(&data, 0, sizeof(data));

	memset(rawscr, 0, 8);
	cmd.opcode = ACMD_SEND_SCR;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
	cmd.arg = 0;
	cmd.data = &data;

	data.data = rawscr;
	data.len = 8;
	data.flags = MMC_DATA_READ;

	err = mmc_wait_for_app_cmd(sc->dev, sc->dev, rca, &cmd, CMD_RETRIES);
	rawscr[0] = be32toh(rawscr[0]);
	rawscr[1] = be32toh(rawscr[1]);
	return (err);
}