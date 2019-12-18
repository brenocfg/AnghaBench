#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_net_hdr {int dummy; } ;
struct vector_private {int header_size; int rx_header_size; TYPE_1__* fds; TYPE_2__* dev; int /*<<< orphan*/ * verify_header; int /*<<< orphan*/ * form_header; } ;
struct TYPE_4__ {int hw_features; int features; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_fd; int /*<<< orphan*/  rx_fd; } ;

/* Variables and functions */
 int NETIF_F_GRO ; 
 int NETIF_F_GSO ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  netdev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  raw_form_header ; 
 int /*<<< orphan*/  raw_verify_header ; 
 scalar_t__ uml_raw_enable_vnet_headers (int /*<<< orphan*/ ) ; 
 scalar_t__ uml_tap_enable_vnet_headers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_hybrid_transport_data(struct vector_private *vp)
{
	if (uml_raw_enable_vnet_headers(vp->fds->rx_fd)) {
		vp->form_header = &raw_form_header;
		vp->verify_header = &raw_verify_header;
		vp->header_size = sizeof(struct virtio_net_hdr);
		vp->rx_header_size = sizeof(struct virtio_net_hdr);
		vp->dev->hw_features |=
			(NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		vp->dev->features |=
			(NETIF_F_RXCSUM | NETIF_F_HW_CSUM |
				NETIF_F_TSO | NETIF_F_GSO | NETIF_F_GRO);
		netdev_info(
			vp->dev,
			"tap/raw hybrid: using vnet headers for tso and tx/rx checksum"
		);
	} else {
		return 0; /* do not try to enable tap too if raw failed */
	}
	if (uml_tap_enable_vnet_headers(vp->fds->tx_fd))
		return 0;
	return -1;
}