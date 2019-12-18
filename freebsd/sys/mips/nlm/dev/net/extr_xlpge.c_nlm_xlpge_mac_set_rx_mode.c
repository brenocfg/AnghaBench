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
struct nlm_xlpge_softc {int if_flags; scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  block; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 scalar_t__ SGMIIC ; 
 int /*<<< orphan*/  nlm_nae_setup_rx_mode_sgmii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_nae_setup_rx_mode_xaui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nlm_xlpge_mac_set_rx_mode(struct nlm_xlpge_softc *sc)
{
	if (sc->if_flags & IFF_PROMISC) {
		if (sc->type == SGMIIC)
			nlm_nae_setup_rx_mode_sgmii(sc->base_addr,
			    sc->block, sc->port, sc->type, 1 /* broadcast */,
			    1/* multicast */, 0 /* pause */, 1 /* promisc */);
		else
			nlm_nae_setup_rx_mode_xaui(sc->base_addr,
			    sc->block, sc->port, sc->type, 1 /* broadcast */,
			    1/* multicast */, 0 /* pause */, 1 /* promisc */);
	} else {
		if (sc->type == SGMIIC)
			nlm_nae_setup_rx_mode_sgmii(sc->base_addr,
			    sc->block, sc->port, sc->type, 1 /* broadcast */,
			    1/* multicast */, 0 /* pause */, 0 /* promisc */);
		else
			nlm_nae_setup_rx_mode_xaui(sc->base_addr,
			    sc->block, sc->port, sc->type, 1 /* broadcast */,
			    1/* multicast */, 0 /* pause */, 0 /* promisc */);
	}
}