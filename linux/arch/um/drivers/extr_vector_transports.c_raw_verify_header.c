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
struct virtio_net_hdr {scalar_t__ gso_type; int flags; } ;
struct vector_private {int req_size; int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSO_ERROR ; 
 int VIRTIO_NET_HDR_F_DATA_VALID ; 
 scalar_t__ VIRTIO_NET_HDR_GSO_NONE ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_legacy_is_little_endian () ; 
 int /*<<< orphan*/  virtio_net_hdr_to_skb (struct sk_buff*,struct virtio_net_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw_verify_header(
	uint8_t *header, struct sk_buff *skb, struct vector_private *vp)
{
	struct virtio_net_hdr *vheader = (struct virtio_net_hdr *) header;

	if ((vheader->gso_type != VIRTIO_NET_HDR_GSO_NONE) &&
		(vp->req_size != 65536)) {
		if (net_ratelimit())
			netdev_err(
				vp->dev,
				GSO_ERROR
		);
	}
	if ((vheader->flags & VIRTIO_NET_HDR_F_DATA_VALID) > 0)
		return 1;

	virtio_net_hdr_to_skb(skb, vheader, virtio_legacy_is_little_endian());
	return 0;
}