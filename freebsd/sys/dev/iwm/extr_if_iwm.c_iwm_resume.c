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
struct iwm_softc {int sc_flags; int /*<<< orphan*/  sc_ic; int /*<<< orphan*/  sc_attached; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IWM_FLAG_SCANNING ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  PCI_CFG_RETRY_TIMEOUT ; 
 struct iwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_resume_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_init_task (struct iwm_softc*) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
iwm_resume(device_t dev)
{
	struct iwm_softc *sc = device_get_softc(dev);
	int do_reinit = 0;

	/*
	 * We disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state.
	 */
	pci_write_config(dev, PCI_CFG_RETRY_TIMEOUT, 0x00, 1);

	if (!sc->sc_attached)
		return 0;

	iwm_init_task(device_get_softc(dev));

	IWM_LOCK(sc);
	if (sc->sc_flags & IWM_FLAG_SCANNING) {
		sc->sc_flags &= ~IWM_FLAG_SCANNING;
		do_reinit = 1;
	}
	IWM_UNLOCK(sc);

	if (do_reinit)
		ieee80211_resume_all(&sc->sc_ic);

	return 0;
}