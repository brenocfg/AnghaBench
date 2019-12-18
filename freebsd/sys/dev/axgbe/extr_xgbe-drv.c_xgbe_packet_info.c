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
struct xgbe_ring {int dummy; } ;
struct xgbe_prv_data {int dummy; } ;
struct xgbe_packet_data {int tx_packets; scalar_t__ rdesc_count; int /*<<< orphan*/  tx_bytes; struct mbuf* m; } ;
struct mbuf {unsigned int m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 scalar_t__ MIN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGBE_TX_MAX_BUF_SIZE ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_packet_info(struct xgbe_prv_data *pdata,
			     struct xgbe_ring *ring, struct mbuf *m0,
			     struct xgbe_packet_data *packet)
{
	struct mbuf *m;
	unsigned int len;

	packet->m = m0;

	packet->rdesc_count = 0;

	packet->tx_packets = 1;
	packet->tx_bytes = m_length(m0, NULL);

	for (m = m0; m != NULL; m = m->m_next) {
		for (len = m->m_len; len != 0;) {
			packet->rdesc_count++;
			len -= MIN(len, XGBE_TX_MAX_BUF_SIZE);
		}
	}
}