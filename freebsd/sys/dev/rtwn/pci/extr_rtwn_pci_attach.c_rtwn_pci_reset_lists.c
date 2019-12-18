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
struct rtwn_softc {scalar_t__ qfullmsk; } ;
struct ieee80211vap {int dummy; } ;

/* Variables and functions */
 int RTWN_PCI_NTXQUEUES ; 
 int /*<<< orphan*/  rtwn_pci_reset_rx_list (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_pci_reset_tx_list (struct rtwn_softc*,struct ieee80211vap*,int) ; 

__attribute__((used)) static void
rtwn_pci_reset_lists(struct rtwn_softc *sc, struct ieee80211vap *vap)
{
	int i;

	for (i = 0; i < RTWN_PCI_NTXQUEUES; i++)
		rtwn_pci_reset_tx_list(sc, vap, i);

	if (vap == NULL) {
		sc->qfullmsk = 0;
		rtwn_pci_reset_rx_list(sc);
	}
}