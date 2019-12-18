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
struct ieee80211com {int dummy; } ;
struct iwi_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_unr; int /*<<< orphan*/  mem; int /*<<< orphan*/  irq; int /*<<< orphan*/  rxq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  sc_monitortask; int /*<<< orphan*/  sc_disassoctask; int /*<<< orphan*/  sc_restarttask; int /*<<< orphan*/  sc_radiofftask; int /*<<< orphan*/  sc_radiontask; int /*<<< orphan*/  sc_ih; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWI_LOCK_DESTROY (struct iwi_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 
 struct iwi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_draintask (struct ieee80211com*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  iwi_free_cmd_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_free_rx_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_free_tx_ring (struct iwi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwi_put_firmware (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_release_fw_dma (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_stop (struct iwi_softc*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwi_detach(device_t dev)
{
	struct iwi_softc *sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;

	bus_teardown_intr(dev, sc->irq, sc->sc_ih);

	/* NB: do early to drain any pending tasks */
	ieee80211_draintask(ic, &sc->sc_radiontask);
	ieee80211_draintask(ic, &sc->sc_radiofftask);
	ieee80211_draintask(ic, &sc->sc_restarttask);
	ieee80211_draintask(ic, &sc->sc_disassoctask);
	ieee80211_draintask(ic, &sc->sc_monitortask);

	iwi_stop(sc);

	ieee80211_ifdetach(ic);

	iwi_put_firmware(sc);
	iwi_release_fw_dma(sc);

	iwi_free_cmd_ring(sc, &sc->cmdq);
	iwi_free_tx_ring(sc, &sc->txq[0]);
	iwi_free_tx_ring(sc, &sc->txq[1]);
	iwi_free_tx_ring(sc, &sc->txq[2]);
	iwi_free_tx_ring(sc, &sc->txq[3]);
	iwi_free_rx_ring(sc, &sc->rxq);

	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(sc->irq), sc->irq);

	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(sc->mem),
	    sc->mem);

	delete_unrhdr(sc->sc_unr);
	mbufq_drain(&sc->sc_snd);

	IWI_LOCK_DESTROY(sc);

	return 0;
}