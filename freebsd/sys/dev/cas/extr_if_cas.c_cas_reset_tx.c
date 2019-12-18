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
struct cas_softc {int sc_flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CAS_BARRIER (struct cas_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CAS_RESET ; 
 int CAS_RESET_PCS_DIS ; 
 int CAS_RESET_TX ; 
 int CAS_SERDES ; 
 int /*<<< orphan*/  CAS_TX_CONF ; 
 int CAS_TX_CONF_TXDMA_EN ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cas_bitwait (struct cas_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cas_disable_tx (struct cas_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cas_reset_tx(struct cas_softc *sc)
{

	/*
	 * Resetting while DMA is in progress can cause a bus hang, so we
	 * disable DMA first.
	 */
	(void)cas_disable_tx(sc);
	CAS_WRITE_4(sc, CAS_TX_CONF, 0);
	CAS_BARRIER(sc, CAS_TX_CONF, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!cas_bitwait(sc, CAS_TX_CONF, CAS_TX_CONF_TXDMA_EN, 0))
		device_printf(sc->sc_dev, "cannot disable TX DMA\n");

	/* Finally, reset the ETX. */
	CAS_WRITE_4(sc, CAS_RESET, CAS_RESET_TX |
	    ((sc->sc_flags & CAS_SERDES) != 0 ? CAS_RESET_PCS_DIS : 0));
	CAS_BARRIER(sc, CAS_RESET, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (!cas_bitwait(sc, CAS_RESET, CAS_RESET_TX, 0)) {
		device_printf(sc->sc_dev, "cannot reset transmitter\n");
		return (1);
	}
	return (0);
}