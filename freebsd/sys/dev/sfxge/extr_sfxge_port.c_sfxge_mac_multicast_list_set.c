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
struct sfxge_port {scalar_t__ mcast_count; int /*<<< orphan*/  mcast_addrs; int /*<<< orphan*/  lock; } ;
struct sfxge_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; struct sfxge_port port; struct ifnet* ifnet; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFX_MAC_MULTICAST_LIST_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int efx_mac_multicast_list_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_copy_maddr ; 

__attribute__((used)) static int
sfxge_mac_multicast_list_set(struct sfxge_softc *sc)
{
	struct ifnet *ifp = sc->ifnet;
	struct sfxge_port *port = &sc->port;
	int rc = 0;

	mtx_assert(&port->lock, MA_OWNED);

	port->mcast_count = if_foreach_llmaddr(ifp, sfxge_copy_maddr,
	    port->mcast_addrs);
	if (port->mcast_count == EFX_MAC_MULTICAST_LIST_MAX) {
		device_printf(sc->dev, "Too many multicast addresses\n");
		rc = EINVAL;
	}

	if (rc == 0) {
		rc = efx_mac_multicast_list_set(sc->enp, port->mcast_addrs,
						port->mcast_count);
		if (rc != 0)
			device_printf(sc->dev,
			    "Cannot set multicast address list\n");
	}

	return (rc);
}