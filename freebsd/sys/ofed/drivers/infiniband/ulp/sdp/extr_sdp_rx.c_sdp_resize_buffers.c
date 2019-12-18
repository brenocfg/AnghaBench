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
typedef  scalar_t__ u32 ;
struct sdp_sock {scalar_t__ recv_bytes; } ;

/* Variables and functions */
 scalar_t__ SDP_MAX_PACKET ; 
 scalar_t__ sdp_get_recv_bytes (struct sdp_sock*,scalar_t__) ; 

int
sdp_resize_buffers(struct sdp_sock *ssk, u32 new_size)
{
	u32 curr_size = ssk->recv_bytes;
	u32 max_size = SDP_MAX_PACKET;

	if (new_size > curr_size && new_size <= max_size) {
		ssk->recv_bytes = sdp_get_recv_bytes(ssk, new_size);
		return 0;
	}
	return -1;
}