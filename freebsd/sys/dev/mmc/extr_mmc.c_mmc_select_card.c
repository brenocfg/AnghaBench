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
struct mmc_softc {int /*<<< orphan*/  retune_paused; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RETRIES ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_NONE ; 
 int MMC_RSP_R1B ; 
 int /*<<< orphan*/  MMC_SELECT_CARD ; 
 int mmc_wait_for_command (struct mmc_softc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_select_card(struct mmc_softc *sc, uint16_t rca)
{
	int err, flags;

	flags = (rca ? MMC_RSP_R1B : MMC_RSP_NONE) | MMC_CMD_AC;
	sc->retune_paused++;
	err = mmc_wait_for_command(sc, MMC_SELECT_CARD, (uint32_t)rca << 16,
	    flags, NULL, CMD_RETRIES);
	sc->retune_paused--;
	return (err);
}