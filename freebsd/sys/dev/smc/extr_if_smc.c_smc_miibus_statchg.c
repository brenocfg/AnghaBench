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
typedef  int /*<<< orphan*/  uint16_t ;
struct smc_softc {int /*<<< orphan*/  smc_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TCR_SWFDUP ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_read_2 (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_select_bank (struct smc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_write_2 (struct smc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
smc_miibus_statchg(device_t dev)
{
	struct smc_softc	*sc;
	struct mii_data		*mii;
	uint16_t		tcr;

	sc = device_get_softc(dev);
	mii = device_get_softc(sc->smc_miibus);

	SMC_LOCK(sc);

	smc_select_bank(sc, 0);
	tcr = smc_read_2(sc, TCR);

	if ((IFM_OPTIONS(mii->mii_media_active) & IFM_FDX) != 0)
		tcr |= TCR_SWFDUP;
	else
		tcr &= ~TCR_SWFDUP;

	smc_write_2(sc, TCR, tcr);

	SMC_UNLOCK(sc);
}