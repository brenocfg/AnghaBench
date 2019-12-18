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
typedef  int uint16_t ;
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/  resp; int /*<<< orphan*/ * data; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_BCR ; 
 int MMC_RSP_R2 ; 
 int /*<<< orphan*/  MMC_SEND_CSD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_send_csd(struct mmc_softc *sc, uint16_t rca, uint32_t *rawcsd)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = MMC_SEND_CSD;
	cmd.arg = rca << 16;
	cmd.flags = MMC_RSP_R2 | MMC_CMD_BCR;
	cmd.data = NULL;
	err = mmc_wait_for_cmd(sc->dev, sc->dev, &cmd, CMD_RETRIES);
	memcpy(rawcsd, cmd.resp, 4 * sizeof(uint32_t));
	return (err);
}