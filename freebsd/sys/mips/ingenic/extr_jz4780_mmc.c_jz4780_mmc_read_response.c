#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct mmc_command {int flags; int* resp; } ;
struct jz4780_mmc_softc {TYPE_1__* sc_req; } ;
struct TYPE_2__ {struct mmc_command* cmd; } ;

/* Variables and functions */
 int JZ_MMC_READ_2 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MSC_RES ; 
 int MMC_RSP_136 ; 
 int MMC_RSP_PRESENT ; 

__attribute__((used)) static void
jz4780_mmc_read_response(struct jz4780_mmc_softc *sc)
{
	struct mmc_command *cmd;
	int i;

	cmd = sc->sc_req->cmd;
	if (cmd->flags & MMC_RSP_PRESENT) {
		if (cmd->flags & MMC_RSP_136) {
			uint16_t val;

			val = JZ_MMC_READ_2(sc, JZ_MSC_RES);
			for (i = 0; i < 4; i++) {
				cmd->resp[i] = val << 24;
				val = JZ_MMC_READ_2(sc, JZ_MSC_RES);
				cmd->resp[i] |= val << 8;
				val = JZ_MMC_READ_2(sc, JZ_MSC_RES);
				cmd->resp[i] |= val >> 8;
			}
		} else {
			cmd->resp[0] = JZ_MMC_READ_2(sc, JZ_MSC_RES) << 24;
			cmd->resp[0] |= JZ_MMC_READ_2(sc, JZ_MSC_RES) << 8;
			cmd->resp[0] |= JZ_MMC_READ_2(sc, JZ_MSC_RES) & 0xff;
		}
	}
}