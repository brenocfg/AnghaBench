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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int flags; int /*<<< orphan*/ * data; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1 ; 
 int /*<<< orphan*/  MMC_SET_BLOCKLEN ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_set_blocklen(struct mmc_softc *sc, uint32_t len)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = MMC_SET_BLOCKLEN;
	cmd.arg = len;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
	cmd.data = NULL;
	err = mmc_wait_for_cmd(sc->dev, sc->dev, &cmd, CMD_RETRIES);
	return (err);
}