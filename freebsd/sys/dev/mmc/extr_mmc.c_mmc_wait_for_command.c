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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
struct mmc_command {int opcode; int arg; int flags; int* resp; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int MMC_RSP_136 ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int mmc_wait_for_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mmc_command*,int) ; 

__attribute__((used)) static int
mmc_wait_for_command(struct mmc_softc *sc, uint32_t opcode,
    uint32_t arg, uint32_t flags, uint32_t *resp, int retries)
{
	struct mmc_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = opcode;
	cmd.arg = arg;
	cmd.flags = flags;
	cmd.data = NULL;
	err = mmc_wait_for_cmd(sc->dev, sc->dev, &cmd, retries);
	if (err)
		return (err);
	if (resp) {
		if (flags & MMC_RSP_136)
			memcpy(resp, cmd.resp, 4 * sizeof(uint32_t));
		else
			*resp = cmd.resp[0];
	}
	return (0);
}