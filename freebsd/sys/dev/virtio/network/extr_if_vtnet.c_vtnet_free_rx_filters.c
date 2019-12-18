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
struct vtnet_softc {int /*<<< orphan*/ * vtnet_vlan_filter; int /*<<< orphan*/ * vtnet_mac_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtnet_free_rx_filters(struct vtnet_softc *sc)
{

	if (sc->vtnet_mac_filter != NULL) {
		free(sc->vtnet_mac_filter, M_DEVBUF);
		sc->vtnet_mac_filter = NULL;
	}

	if (sc->vtnet_vlan_filter != NULL) {
		free(sc->vtnet_vlan_filter, M_DEVBUF);
		sc->vtnet_vlan_filter = NULL;
	}
}