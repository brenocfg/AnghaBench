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
typedef  int uint16_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/ * data; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_BCR ; 
 int MMC_RSP_R6 ; 
 int /*<<< orphan*/  MMC_SET_RELATIVE_ADDR ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_set_relative_addr(struct mmc_softc *sc, uint16_t resp)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = MMC_SET_RELATIVE_ADDR;
	cmd.arg = resp << 16;
	cmd.flags = MMC_RSP_R6 | MMC_CMD_BCR;
	cmd.data = NULL;
	err = mmc_wait_for_cmd(sc->dev, sc->dev, &cmd, CMD_RETRIES);
	return (err);
}