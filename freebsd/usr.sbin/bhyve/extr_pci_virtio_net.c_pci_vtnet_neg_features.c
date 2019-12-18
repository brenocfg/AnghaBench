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
typedef  int uint64_t ;
struct virtio_net_rxhdr {int dummy; } ;
struct pci_vtnet_softc {int vsc_features; int rx_vhdrlen; int /*<<< orphan*/  vsc_be; scalar_t__ rx_merge; } ;

/* Variables and functions */
 int VIRTIO_NET_F_MRG_RXBUF ; 
 int /*<<< orphan*/  netbe_set_cap (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
pci_vtnet_neg_features(void *vsc, uint64_t negotiated_features)
{
	struct pci_vtnet_softc *sc = vsc;

	sc->vsc_features = negotiated_features;

	if (!(negotiated_features & VIRTIO_NET_F_MRG_RXBUF)) {
		sc->rx_merge = 0;
		/* Without mergeable rx buffers, virtio-net header is 2
		 * bytes shorter than sizeof(struct virtio_net_rxhdr). */
		sc->rx_vhdrlen = sizeof(struct virtio_net_rxhdr) - 2;
	}

	/* Tell the backend to enable some capabilities it has advertised. */
	netbe_set_cap(sc->vsc_be, negotiated_features, sc->rx_vhdrlen);
}