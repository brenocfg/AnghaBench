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
struct sdp_sock {int /*<<< orphan*/  tx_ring; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  ring_tail (int /*<<< orphan*/ ) ; 
 struct mbuf* sdp_send_completion (struct sdp_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tx_ring_posted (struct sdp_sock*) ; 

__attribute__((used)) static
void sdp_tx_ring_purge(struct sdp_sock *ssk)
{
	while (tx_ring_posted(ssk)) {
		struct mbuf *mb;
		mb = sdp_send_completion(ssk, ring_tail(ssk->tx_ring));
		if (!mb)
			break;
		m_freem(mb);
	}
}