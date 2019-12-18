#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ena_ring {int /*<<< orphan*/  qid; struct ena_adapter* adapter; } ;
struct ena_com_rx_ctx {int l3_proto; int /*<<< orphan*/  l4_proto; scalar_t__ frag; int /*<<< orphan*/  hash; } ;
struct ena_adapter {int dummy; } ;

/* Variables and functions */
#define  ENA_ETH_IO_L3_PROTO_IPV4 132 
#define  ENA_ETH_IO_L3_PROTO_IPV6 131 
#define  ENA_ETH_IO_L3_PROTO_UNKNOWN 130 
#define  ENA_ETH_IO_L4_PROTO_TCP 129 
#define  ENA_ETH_IO_L4_PROTO_UDP 128 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_RSS_ACTIVE ; 
 int /*<<< orphan*/  M_HASHTYPE_NONE ; 
 int /*<<< orphan*/  M_HASHTYPE_OPAQUE_HASH ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_IPV6 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_TCP_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_TCP_IPV6 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_UDP_IPV4 ; 
 int /*<<< orphan*/  M_HASHTYPE_RSS_UDP_IPV6 ; 
 int /*<<< orphan*/  M_HASHTYPE_SET (struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ena_rx_hash_mbuf(struct ena_ring *rx_ring, struct ena_com_rx_ctx *ena_rx_ctx,
    struct mbuf *mbuf)
{
	struct ena_adapter *adapter = rx_ring->adapter;

	if (likely(ENA_FLAG_ISSET(ENA_FLAG_RSS_ACTIVE, adapter))) {
		mbuf->m_pkthdr.flowid = ena_rx_ctx->hash;

		if (ena_rx_ctx->frag &&
		    (ena_rx_ctx->l3_proto != ENA_ETH_IO_L3_PROTO_UNKNOWN)) {
			M_HASHTYPE_SET(mbuf, M_HASHTYPE_OPAQUE_HASH);
			return;
		}

		switch (ena_rx_ctx->l3_proto) {
		case ENA_ETH_IO_L3_PROTO_IPV4:
			switch (ena_rx_ctx->l4_proto) {
			case ENA_ETH_IO_L4_PROTO_TCP:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_TCP_IPV4);
				break;
			case ENA_ETH_IO_L4_PROTO_UDP:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_UDP_IPV4);
				break;
			default:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_IPV4);
			}
			break;
		case ENA_ETH_IO_L3_PROTO_IPV6:
			switch (ena_rx_ctx->l4_proto) {
			case ENA_ETH_IO_L4_PROTO_TCP:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_TCP_IPV6);
				break;
			case ENA_ETH_IO_L4_PROTO_UDP:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_UDP_IPV6);
				break;
			default:
				M_HASHTYPE_SET(mbuf, M_HASHTYPE_RSS_IPV6);
			}
			break;
		case ENA_ETH_IO_L3_PROTO_UNKNOWN:
			M_HASHTYPE_SET(mbuf, M_HASHTYPE_NONE);
			break;
		default:
			M_HASHTYPE_SET(mbuf, M_HASHTYPE_OPAQUE_HASH);
		}
	} else {
		mbuf->m_pkthdr.flowid = rx_ring->qid;
		M_HASHTYPE_SET(mbuf, M_HASHTYPE_NONE);
	}
}