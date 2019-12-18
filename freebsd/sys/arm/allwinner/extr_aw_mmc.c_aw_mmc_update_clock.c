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
typedef  int uint32_t ;
struct aw_mmc_softc {TYPE_1__* aw_mmc_conf; int /*<<< orphan*/  aw_dev; } ;
struct TYPE_2__ {scalar_t__ mask_data0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_MMC_CKCR ; 
 int AW_MMC_CKCR_ENB ; 
 int AW_MMC_CKCR_LOW_POWER ; 
 int AW_MMC_CKCR_MASK_DATA0 ; 
 int /*<<< orphan*/  AW_MMC_CMDR ; 
 int AW_MMC_CMDR_LOAD ; 
 int AW_MMC_CMDR_PRG_CLK ; 
 int AW_MMC_CMDR_WAIT_PRE_OVER ; 
 int AW_MMC_READ_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AW_MMC_RISR ; 
 int /*<<< orphan*/  AW_MMC_WRITE_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aw_mmc_update_clock(struct aw_mmc_softc *sc, uint32_t clkon)
{
	uint32_t reg;
	int retry;

	reg = AW_MMC_READ_4(sc, AW_MMC_CKCR);
	reg &= ~(AW_MMC_CKCR_ENB | AW_MMC_CKCR_LOW_POWER |
	    AW_MMC_CKCR_MASK_DATA0);

	if (clkon)
		reg |= AW_MMC_CKCR_ENB;
	if (sc->aw_mmc_conf->mask_data0)
		reg |= AW_MMC_CKCR_MASK_DATA0;

	AW_MMC_WRITE_4(sc, AW_MMC_CKCR, reg);

	reg = AW_MMC_CMDR_LOAD | AW_MMC_CMDR_PRG_CLK |
	    AW_MMC_CMDR_WAIT_PRE_OVER;
	AW_MMC_WRITE_4(sc, AW_MMC_CMDR, reg);
	retry = 0xfffff;

	while (reg & AW_MMC_CMDR_LOAD && --retry > 0) {
		reg = AW_MMC_READ_4(sc, AW_MMC_CMDR);
		DELAY(10);
	}
	AW_MMC_WRITE_4(sc, AW_MMC_RISR, 0xffffffff);

	if (reg & AW_MMC_CMDR_LOAD) {
		device_printf(sc->aw_dev, "timeout updating clock\n");
		return (ETIMEDOUT);
	}

	if (sc->aw_mmc_conf->mask_data0) {
		reg = AW_MMC_READ_4(sc, AW_MMC_CKCR);
		reg &= ~AW_MMC_CKCR_MASK_DATA0;
		AW_MMC_WRITE_4(sc, AW_MMC_CKCR, reg);
	}

	return (0);
}