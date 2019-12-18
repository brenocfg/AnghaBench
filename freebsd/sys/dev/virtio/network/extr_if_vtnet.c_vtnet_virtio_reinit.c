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
typedef  int /*<<< orphan*/  uint64_t ;
struct vtnet_softc {int /*<<< orphan*/  vtnet_features; struct ifnet* vtnet_ifp; int /*<<< orphan*/  vtnet_dev; } ;
struct ifnet {int if_capabilities; int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWFILTER ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CTRL_VLAN ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_CSUM ; 
 int /*<<< orphan*/  VTNET_LRO_FEATURES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int virtio_reinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtnet_virtio_reinit(struct vtnet_softc *sc)
{
	device_t dev;
	struct ifnet *ifp;
	uint64_t features;
	int mask, error;

	dev = sc->vtnet_dev;
	ifp = sc->vtnet_ifp;
	features = sc->vtnet_features;

	mask = 0;
#if defined(INET)
	mask |= IFCAP_RXCSUM;
#endif
#if defined (INET6)
	mask |= IFCAP_RXCSUM_IPV6;
#endif

	/*
	 * Re-negotiate with the host, removing any disabled receive
	 * features. Transmit features are disabled only on our side
	 * via if_capenable and if_hwassist.
	 */

	if (ifp->if_capabilities & mask) {
		/*
		 * We require both IPv4 and IPv6 offloading to be enabled
		 * in order to negotiated it: VirtIO does not distinguish
		 * between the two.
		 */
		if ((ifp->if_capenable & mask) != mask)
			features &= ~VIRTIO_NET_F_GUEST_CSUM;
	}

	if (ifp->if_capabilities & IFCAP_LRO) {
		if ((ifp->if_capenable & IFCAP_LRO) == 0)
			features &= ~VTNET_LRO_FEATURES;
	}

	if (ifp->if_capabilities & IFCAP_VLAN_HWFILTER) {
		if ((ifp->if_capenable & IFCAP_VLAN_HWFILTER) == 0)
			features &= ~VIRTIO_NET_F_CTRL_VLAN;
	}

	error = virtio_reinit(dev, features);
	if (error)
		device_printf(dev, "virtio reinit error %d\n", error);

	return (error);
}