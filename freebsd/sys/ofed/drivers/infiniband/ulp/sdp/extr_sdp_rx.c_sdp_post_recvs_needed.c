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
struct sdp_sock {int recv_bytes; TYPE_1__* socket; int /*<<< orphan*/  qp_active; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_hiwat; } ;
struct TYPE_3__ {TYPE_2__ so_rcv; } ;

/* Variables and functions */
 int SDP_MIN_TX_CREDITS ; 
 int SDP_RX_SIZE ; 
 unsigned long max (int /*<<< orphan*/ ,int) ; 
 unsigned long rcvbuf_scale ; 
 int rx_ring_posted (struct sdp_sock*) ; 
 scalar_t__ sbused (TYPE_2__*) ; 

__attribute__((used)) static inline int
sdp_post_recvs_needed(struct sdp_sock *ssk)
{
	unsigned long bytes_in_process;
	unsigned long max_bytes;
	int buffer_size;
	int posted;

	if (!ssk->qp_active || !ssk->socket)
		return 0;

	posted = rx_ring_posted(ssk);
	if (posted >= SDP_RX_SIZE)
		return 0;
	if (posted < SDP_MIN_TX_CREDITS)
		return 1;

	buffer_size = ssk->recv_bytes;
	max_bytes = max(ssk->socket->so_rcv.sb_hiwat,
	    (1 + SDP_MIN_TX_CREDITS) * buffer_size);
	max_bytes *= rcvbuf_scale;
	/*
	 * Compute bytes in the receive queue and socket buffer.
	 */
	bytes_in_process = (posted - SDP_MIN_TX_CREDITS) * buffer_size;
	bytes_in_process += sbused(&ssk->socket->so_rcv);

	return bytes_in_process < max_bytes;
}