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
struct iwm_fw_info {int /*<<< orphan*/ * fw_fp; } ;
struct iwm_softc {int /*<<< orphan*/ * sc_notif_wait; int /*<<< orphan*/  fw_dma; int /*<<< orphan*/  kw_dma; int /*<<< orphan*/  ict_dma; int /*<<< orphan*/  sched_dma; int /*<<< orphan*/ * txq; int /*<<< orphan*/  rxq; int /*<<< orphan*/  nvm_data; int /*<<< orphan*/ * sc_phy_db; int /*<<< orphan*/  sc_watchdog_to; int /*<<< orphan*/  sc_led_blink_to; int /*<<< orphan*/  sc_ic; int /*<<< orphan*/  sc_es_task; scalar_t__ sc_attached; int /*<<< orphan*/  sc_dev; struct iwm_fw_info sc_fw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_LOCK_DESTROY (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_draintask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_dma_contig_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_free_fw_paging (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_free_nvm_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_free_rx_ring (struct iwm_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_free_tx_ring (struct iwm_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_fw_info_free (struct iwm_fw_info*) ; 
 int /*<<< orphan*/  iwm_notification_wait_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_pci_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_phy_db_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_stop_device (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_xmit_queue_drain (struct iwm_softc*) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iwm_detach_local(struct iwm_softc *sc, int do_net80211)
{
	struct iwm_fw_info *fw = &sc->sc_fw;
	device_t dev = sc->sc_dev;
	int i;

	if (!sc->sc_attached)
		return 0;
	sc->sc_attached = 0;
	if (do_net80211) {
		ieee80211_draintask(&sc->sc_ic, &sc->sc_es_task);
	}
	iwm_stop_device(sc);
	if (do_net80211) {
		IWM_LOCK(sc);
		iwm_xmit_queue_drain(sc);
		IWM_UNLOCK(sc);
		ieee80211_ifdetach(&sc->sc_ic);
	}
	callout_drain(&sc->sc_led_blink_to);
	callout_drain(&sc->sc_watchdog_to);

	iwm_phy_db_free(sc->sc_phy_db);
	sc->sc_phy_db = NULL;

	iwm_free_nvm_data(sc->nvm_data);

	/* Free descriptor rings */
	iwm_free_rx_ring(sc, &sc->rxq);
	for (i = 0; i < nitems(sc->txq); i++)
		iwm_free_tx_ring(sc, &sc->txq[i]);

	/* Free firmware */
	if (fw->fw_fp != NULL)
		iwm_fw_info_free(fw);

	/* Free scheduler */
	iwm_dma_contig_free(&sc->sched_dma);
	iwm_dma_contig_free(&sc->ict_dma);
	iwm_dma_contig_free(&sc->kw_dma);
	iwm_dma_contig_free(&sc->fw_dma);

	iwm_free_fw_paging(sc);

	/* Finished with the hardware - detach things */
	iwm_pci_detach(dev);

	if (sc->sc_notif_wait != NULL) {
		iwm_notification_wait_free(sc->sc_notif_wait);
		sc->sc_notif_wait = NULL;
	}

	IWM_LOCK_DESTROY(sc);

	return (0);
}