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
struct TYPE_3__ {int /*<<< orphan*/  bad_csum; } ;
struct ena_ring {TYPE_1__ rx_stats; } ;
struct ena_com_rx_ctx {scalar_t__ l3_proto; scalar_t__ l4_proto; scalar_t__ l4_csum_err; scalar_t__ l3_csum_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSUM_IP_CHECKED ; 
 int /*<<< orphan*/  CSUM_IP_VALID ; 
 int /*<<< orphan*/  ENA_DBG ; 
 scalar_t__ ENA_ETH_IO_L3_PROTO_IPV4 ; 
 scalar_t__ ENA_ETH_IO_L4_PROTO_TCP ; 
 scalar_t__ ENA_ETH_IO_L4_PROTO_UDP ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
ena_rx_checksum(struct ena_ring *rx_ring, struct ena_com_rx_ctx *ena_rx_ctx,
    struct mbuf *mbuf)
{

	/* if IP and error */
	if (unlikely((ena_rx_ctx->l3_proto == ENA_ETH_IO_L3_PROTO_IPV4) &&
	    ena_rx_ctx->l3_csum_err)) {
		/* ipv4 checksum error */
		mbuf->m_pkthdr.csum_flags = 0;
		counter_u64_add(rx_ring->rx_stats.bad_csum, 1);
		ena_trace(ENA_DBG, "RX IPv4 header checksum error\n");
		return;
	}

	/* if TCP/UDP */
	if ((ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_TCP) ||
	    (ena_rx_ctx->l4_proto == ENA_ETH_IO_L4_PROTO_UDP)) {
		if (ena_rx_ctx->l4_csum_err) {
			/* TCP/UDP checksum error */
			mbuf->m_pkthdr.csum_flags = 0;
			counter_u64_add(rx_ring->rx_stats.bad_csum, 1);
			ena_trace(ENA_DBG, "RX L4 checksum error\n");
		} else {
			mbuf->m_pkthdr.csum_flags = CSUM_IP_CHECKED;
			mbuf->m_pkthdr.csum_flags |= CSUM_IP_VALID;
		}
	}
}