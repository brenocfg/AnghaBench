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
struct sdp_sock {int recv_request; int /*<<< orphan*/  rx_ring; scalar_t__ recv_request_head; } ;
struct sdp_chrecvbuf {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_head (int /*<<< orphan*/ ) ; 
 scalar_t__ ring_tail (int /*<<< orphan*/ ) ; 
 scalar_t__ sdp_resize_buffers (struct sdp_sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdp_handle_resize_request(struct sdp_sock *ssk, struct sdp_chrecvbuf *buf)
{
	if (sdp_resize_buffers(ssk, ntohl(buf->size)) == 0)
		ssk->recv_request_head = ring_head(ssk->rx_ring) + 1;
	else
		ssk->recv_request_head = ring_tail(ssk->rx_ring);
	ssk->recv_request = 1;
}