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
typedef  scalar_t__ uint8_t ;
struct nm_vnet_hdr {scalar_t__ gso_type; int flags; } ;

/* Variables and functions */
 int VIRTIO_NET_HDR_F_DATA_VALID ; 
 int VIRTIO_NET_HDR_F_NEEDS_CSUM ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_ECN ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_NONE ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_TCPV4 ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_TCPV6 ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_UDP ; 

__attribute__((used)) static inline int
vnet_hdr_is_bad(struct nm_vnet_hdr *vh)
{
	uint8_t gso_type = vh->gso_type & ~VIRTIO_NET_HDR_GSO_ECN;

	return (
		(gso_type != VIRTIO_NET_HDR_GSO_NONE &&
		 gso_type != VIRTIO_NET_HDR_GSO_TCPV4 &&
		 gso_type != VIRTIO_NET_HDR_GSO_UDP &&
		 gso_type != VIRTIO_NET_HDR_GSO_TCPV6)
		||
		 (vh->flags & ~(VIRTIO_NET_HDR_F_NEEDS_CSUM
			       | VIRTIO_NET_HDR_F_DATA_VALID))
	       );
}