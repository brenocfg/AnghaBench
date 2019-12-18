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
struct fxp_softc {int /*<<< orphan*/  mcs_map; int /*<<< orphan*/  mcs_tag; int /*<<< orphan*/  mcs_addr; int /*<<< orphan*/  dev; struct fxp_cb_mcs* mcsp; } ;
struct fxp_cb_mcs {int link_addr; scalar_t__ cb_status; int /*<<< orphan*/  cb_command; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSR_READ_1 (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct fxp_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int FXP_CB_COMMAND_EL ; 
 int FXP_CB_COMMAND_MCAS ; 
 int /*<<< orphan*/  FXP_CSR_SCB_GENERAL ; 
 int /*<<< orphan*/  FXP_CSR_SCB_RUSCUS ; 
 int /*<<< orphan*/  FXP_LOCK_ASSERT (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FXP_SCB_COMMAND_CU_START ; 
 int FXP_SCB_CUS_IDLE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fxp_dma_wait (struct fxp_softc*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_mc_addrs (struct fxp_softc*) ; 
 int /*<<< orphan*/  fxp_scb_cmd (struct fxp_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fxp_scb_wait (struct fxp_softc*) ; 
 int /*<<< orphan*/  htole16 (int) ; 

__attribute__((used)) static void
fxp_mc_setup(struct fxp_softc *sc)
{
	struct fxp_cb_mcs *mcsp;
	int count;

	FXP_LOCK_ASSERT(sc, MA_OWNED);

	mcsp = sc->mcsp;
	mcsp->cb_status = 0;
	mcsp->cb_command = htole16(FXP_CB_COMMAND_MCAS | FXP_CB_COMMAND_EL);
	mcsp->link_addr = 0xffffffff;
	fxp_mc_addrs(sc);

	/*
	 * Wait until command unit is idle. This should never be the
	 * case when nothing is queued, but make sure anyway.
	 */
	count = 100;
	while ((CSR_READ_1(sc, FXP_CSR_SCB_RUSCUS) >> 6) !=
	    FXP_SCB_CUS_IDLE && --count)
		DELAY(10);
	if (count == 0) {
		device_printf(sc->dev, "command queue timeout\n");
		return;
	}

	/*
	 * Start the multicast setup command.
	 */
	fxp_scb_wait(sc);
	bus_dmamap_sync(sc->mcs_tag, sc->mcs_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	CSR_WRITE_4(sc, FXP_CSR_SCB_GENERAL, sc->mcs_addr);
	fxp_scb_cmd(sc, FXP_SCB_COMMAND_CU_START);
	/* ...and wait for it to complete. */
	fxp_dma_wait(sc, &mcsp->cb_status, sc->mcs_tag, sc->mcs_map);
}