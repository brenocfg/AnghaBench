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
typedef  int /*<<< orphan*/  uint8_t ;
struct rtwn_softc {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 int rtwn_pci_tx_start_beacon (struct rtwn_softc*,struct mbuf*,int /*<<< orphan*/ *,int) ; 
 int rtwn_pci_tx_start_frame (struct rtwn_softc*,struct ieee80211_node*,struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
rtwn_pci_tx_start(struct rtwn_softc *sc, struct ieee80211_node *ni,
    struct mbuf *m, uint8_t *tx_desc, uint8_t type, int id)
{
	int error = 0;

	RTWN_ASSERT_LOCKED(sc);

	if (ni == NULL)		/* beacon frame */
		error = rtwn_pci_tx_start_beacon(sc, m, tx_desc, id);
	else
		error = rtwn_pci_tx_start_frame(sc, ni, m, tx_desc, type);

	return (error);
}