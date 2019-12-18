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
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct emac_softc {struct ifnet* emac_ifp; int /*<<< orphan*/  emac_rx_process_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_INT_CTL ; 
 int EMAC_INT_EN ; 
 int /*<<< orphan*/  EMAC_INT_STA ; 
 int EMAC_INT_STA_RX ; 
 int EMAC_INT_STA_TX ; 
 int /*<<< orphan*/  EMAC_LOCK (struct emac_softc*) ; 
 int EMAC_READ_REG (struct emac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_UNLOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  EMAC_WRITE_REG (struct emac_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emac_rxeof (struct emac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  emac_txeof (struct emac_softc*,int) ; 

__attribute__((used)) static void
emac_intr(void *arg)
{
	struct emac_softc *sc;
	struct ifnet *ifp;
	uint32_t reg_val;

	sc = (struct emac_softc *)arg;
	EMAC_LOCK(sc);

	/* Disable all interrupts */
	EMAC_WRITE_REG(sc, EMAC_INT_CTL, 0);
	/* Get EMAC interrupt status */
	reg_val = EMAC_READ_REG(sc, EMAC_INT_STA);
	/* Clear ISR status */
	EMAC_WRITE_REG(sc, EMAC_INT_STA, reg_val);

	/* Received incoming packet */
	if (reg_val & EMAC_INT_STA_RX)
		emac_rxeof(sc, sc->emac_rx_process_limit);

	/* Transmit Interrupt check */
	if (reg_val & EMAC_INT_STA_TX) {
		emac_txeof(sc, reg_val);
		ifp = sc->emac_ifp;
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			emac_start_locked(ifp);
	}

	/* Re-enable interrupt mask */
	reg_val = EMAC_READ_REG(sc, EMAC_INT_CTL);
	reg_val |= EMAC_INT_EN;
	EMAC_WRITE_REG(sc, EMAC_INT_CTL, reg_val);
	EMAC_UNLOCK(sc);
}