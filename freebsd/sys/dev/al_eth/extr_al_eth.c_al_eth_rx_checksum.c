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
struct TYPE_4__ {int /*<<< orphan*/  csum_flags; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct al_eth_pkt {scalar_t__ l3_proto_idx; int flags; scalar_t__ l4_proto_idx; } ;
struct al_eth_adapter {int /*<<< orphan*/  dev; TYPE_1__* netdev; } ;
struct TYPE_3__ {int if_capenable; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_PROTO_ID_IPv4 ; 
 scalar_t__ AL_ETH_PROTO_ID_IPv6 ; 
 scalar_t__ AL_ETH_PROTO_ID_TCP ; 
 scalar_t__ AL_ETH_PROTO_ID_UDP ; 
 int AL_ETH_RX_FLAGS_L3_CSUM_ERR ; 
 int AL_ETH_RX_FLAGS_L4_CSUM_ERR ; 
 int /*<<< orphan*/  CSUM_IP_CHECKED ; 
 int /*<<< orphan*/  CSUM_IP_VALID ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
al_eth_rx_checksum(struct al_eth_adapter *adapter,
    struct al_eth_pkt *hal_pkt, struct mbuf *mbuf)
{

	/* if IPv4 and error */
	if (unlikely((adapter->netdev->if_capenable & IFCAP_RXCSUM) &&
	    (hal_pkt->l3_proto_idx == AL_ETH_PROTO_ID_IPv4) &&
	    (hal_pkt->flags & AL_ETH_RX_FLAGS_L3_CSUM_ERR))) {
		device_printf(adapter->dev,"rx ipv4 header checksum error\n");
		return;
	}

	/* if IPv6 and error */
	if (unlikely((adapter->netdev->if_capenable & IFCAP_RXCSUM_IPV6) &&
	    (hal_pkt->l3_proto_idx == AL_ETH_PROTO_ID_IPv6) &&
	    (hal_pkt->flags & AL_ETH_RX_FLAGS_L3_CSUM_ERR))) {
		device_printf(adapter->dev,"rx ipv6 header checksum error\n");
		return;
	}

	/* if TCP/UDP */
	if (likely((hal_pkt->l4_proto_idx == AL_ETH_PROTO_ID_TCP) ||
	   (hal_pkt->l4_proto_idx == AL_ETH_PROTO_ID_UDP))) {
		if (unlikely(hal_pkt->flags & AL_ETH_RX_FLAGS_L4_CSUM_ERR)) {
			device_printf_dbg(adapter->dev, "rx L4 checksum error\n");

			/* TCP/UDP checksum error */
			mbuf->m_pkthdr.csum_flags = 0;
		} else {
			device_printf_dbg(adapter->dev, "rx checksum correct\n");

			/* IP Checksum Good */
			mbuf->m_pkthdr.csum_flags = CSUM_IP_CHECKED;
			mbuf->m_pkthdr.csum_flags |= CSUM_IP_VALID;
		}
	}
}